/**
 * @file adc.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Provides basic ADC functionality
 *
 */

#include "stm32l4xx_ll_dma.h"

#include "adc.h"


/* Delay between ADC end of calibration and ADC enable */
#define ADC_DELAY_CALIB_ENABLE_CPU_CYCLES (LL_ADC_DELAY_CALIB_ENABLE_ADC_CYCLES * 32)


/* Initialize DMA for the ADC */
static void ADC_Init_DMA(
    uint16_t * values,
    int numValues
);

#define ADC_NUM_CHANNELS 23

#define ADC_SAMPLE_RATE LL_ADC_SAMPLINGTIME_640CYCLES_5

/* Array of ADC channels */
uint32_t ADC_CHANNELS[ADC_NUM_CHANNELS] = {
    LL_ADC_CHANNEL_0,
    LL_ADC_CHANNEL_1,
    LL_ADC_CHANNEL_2,
    LL_ADC_CHANNEL_3,
    LL_ADC_CHANNEL_4,
    LL_ADC_CHANNEL_5,
    LL_ADC_CHANNEL_6,
    LL_ADC_CHANNEL_7,
    LL_ADC_CHANNEL_8,
    LL_ADC_CHANNEL_9,
    LL_ADC_CHANNEL_10,
    LL_ADC_CHANNEL_11,
    LL_ADC_CHANNEL_12,
    LL_ADC_CHANNEL_13,
    LL_ADC_CHANNEL_14,
    LL_ADC_CHANNEL_15,
    LL_ADC_CHANNEL_VREFINT, // ADC_BAT_BASE Only, Uses Channel 0
    LL_ADC_CHANNEL_TEMPSENSOR, // ADC_BAT_BASE or ADC3
    LL_ADC_CHANNEL_VBAT, // ADC_BAT_BASE or ADC3
    LL_ADC_CHANNEL_DAC1CH1_ADC2, // ADC2 Only
    LL_ADC_CHANNEL_DAC1CH2_ADC2, // ADC2 Only
    LL_ADC_CHANNEL_DAC1CH1_ADC3, // ADC3 Only, Uses Channel 14
    LL_ADC_CHANNEL_DAC1CH2_ADC3 // ADC3 Only, Uses Channel 15
};

/* Array of ADC channel ranks */
uint32_t ADC_RANKS[16] = {
    LL_ADC_REG_RANK_1,
    LL_ADC_REG_RANK_2,
    LL_ADC_REG_RANK_3,
    LL_ADC_REG_RANK_4,
    LL_ADC_REG_RANK_5,
    LL_ADC_REG_RANK_6,
    LL_ADC_REG_RANK_7,
    LL_ADC_REG_RANK_8,
    LL_ADC_REG_RANK_9,
    LL_ADC_REG_RANK_10,
    LL_ADC_REG_RANK_11,
    LL_ADC_REG_RANK_12,
    LL_ADC_REG_RANK_13,
    LL_ADC_REG_RANK_14,
    LL_ADC_REG_RANK_15,
    LL_ADC_REG_RANK_16
};

/* 0: DMA transfer is not completed */
/* 1: DMA transfer is completed */
/* 2: DMA transfer has not been started yet (initial state) */
volatile uint8_t dmaTransferStatus = 2;

/* 0: ADC group regular sequence conversions are not completed */
/* 1: ADC group regular sequence conversions are completed */
volatile uint8_t adcConversionStatus = 0;


/* Initialize the ADC with DMA */
void Init_ADC(
    uint32_t channels,
    uint16_t * values,
    int numValues
)
{
    int i, j;

    // Check if the ADC is already enabled
    if (LL_ADC_IsEnabled(ADC_BAT_BASE)) {
        return;
    }

    // Initialize DMA for the ADC
    ADC_Init_DMA(values, numValues);

    // Enable ADC interrupts
    // Set the ADC IRQ to a greater priority than the DMA IRQ
    NVIC_SetPriority(ADC_BAT_IRQ, 0);
    NVIC_EnableIRQ(ADC_BAT_IRQ);

    // Enable the ADC clock
    ADCx_CLK_ENABLE();

    // Set the ADC clock
    LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC_BAT_BASE), LL_ADC_CLOCK_SYNC_PCLK_DIV2);

    // Enable the internal ADC channels
    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC_BAT_BASE), (LL_ADC_PATH_INTERNAL_VREFINT | LL_ADC_PATH_INTERNAL_TEMPSENSOR | LL_ADC_PATH_INTERNAL_VBAT));

    // Delay for the internal ADC channels to stablize
    // The temperature sensor takes the longest time to stabalize
    i = ((LL_ADC_DELAY_TEMPSENSOR_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
    while (i != 0) {
        i--;
    }

    // Set the ADC to have a software trigger source
    LL_ADC_REG_SetTriggerSource(ADC_BAT_BASE, LL_ADC_REG_TRIG_SOFTWARE);

    // Set the ADC to convert continuously
    LL_ADC_REG_SetContinuousMode(ADC_BAT_BASE, LL_ADC_REG_CONV_CONTINUOUS);

    // Set the ADC conversion data transfer
    LL_ADC_REG_SetDMATransfer(ADC_BAT_BASE, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);

    // Set the ADC overrun behavior
    LL_ADC_REG_SetOverrun(ADC_BAT_BASE, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

    // Set the ADC sequencer length
    LL_ADC_REG_SetSequencerLength(ADC_BAT_BASE, numValues - 1);

    // Enable specified ADC channels
    for (i = 0, j = 0; i < ADC_NUM_CHANNELS; i++) {
        if (channels & (1 << i)) {
            LL_ADC_REG_SetSequencerRanks(ADC_BAT_BASE, ADC_RANKS[j], ADC_CHANNELS[i]);
            LL_ADC_SetChannelSamplingTime(ADC_BAT_BASE, ADC_CHANNELS[i], ADC_SAMPLE_RATE);
            j++;
        }
        if (j >= numValues || j >= 16) break;
    }

    // Enable ADC interupts for conversion completion
    LL_ADC_EnableIT_EOS(ADC_BAT_BASE);

    // Enable ADC interupts for overrun
    LL_ADC_EnableIT_OVR(ADC_BAT_BASE);

    // Disable the ADC deep power down mode
    LL_ADC_DisableDeepPowerDown(ADC_BAT_BASE);

    // Enable the ADC internal voltage regulator
    LL_ADC_EnableInternalRegulator(ADC_BAT_BASE);

    // Delay for the ADC internal voltage regulator to stabilize
    i = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
    while (i != 0) {
        i--;
    }

    // Start the ADC calibration
    LL_ADC_StartCalibration(ADC_BAT_BASE, LL_ADC_SINGLE_ENDED);

    // Wait for the ADC calibration to finish
    while (LL_ADC_IsCalibrationOnGoing(ADC_BAT_BASE) != 0);

    // Delay to allow ADC calibration to enable
    i = (ADC_DELAY_CALIB_ENABLE_CPU_CYCLES >> 1);
    while (i != 0) {
        i--;
    }

    // Enable the ADC
    LL_ADC_Enable(ADC_BAT_BASE);

    // Wait for the ADC to be ready
    while (LL_ADC_IsActiveFlag_ADRDY(ADC_BAT_BASE) == 0);

    // Start the continous ADC conversion
    LL_ADC_REG_StartConversion(ADC_BAT_BASE);
}

/**
 * @brief  This function configures DMA for transfer of data from ADC
 * @param  None
 * @retval None
 */
static void ADC_Init_DMA(
    uint16_t * values,
    int numValues
)
{
    // Enable DMA interrupts
    // Set the DMA IRQ to a lower priority than the ADC IRQ
    NVIC_SetPriority(DMA_IRQ, 1);
    NVIC_EnableIRQ(DMA_IRQ);

    // Enable the DMA clock
    DMAx_CLK_ENABLE();

    // Configure the DMA transfer
    LL_DMA_ConfigTransfer(DMA_BASE, DMA_CHANNEL,
        LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
        LL_DMA_MODE_CIRCULAR |
        LL_DMA_PERIPH_NOINCREMENT |
        LL_DMA_MEMORY_INCREMENT |
        LL_DMA_PDATAALIGN_HALFWORD |
        LL_DMA_MDATAALIGN_HALFWORD |
        LL_DMA_PRIORITY_HIGH );

    // Select ADC_BAT_BASE as the DMA transfer request
    LL_DMA_SetPeriphRequest(DMA_BASE, DMA_CHANNEL, LL_DMA_REQUEST_0);

    // Set the DMA transfer address source and destination
    LL_DMA_ConfigAddresses(DMA_BASE, DMA_CHANNEL,
        LL_ADC_DMA_GetRegAddr(ADC_BAT_BASE, LL_ADC_DMA_REG_REGULAR_DATA),
        (uint32_t)values, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

    // Set the DMA transfer size
    LL_DMA_SetDataLength(DMA_BASE, DMA_CHANNEL, numValues);

    // Enable DMA transfer complete interrupts
    LL_DMA_EnableIT_TC(DMA_BASE, DMA_CHANNEL);

    // Enable DMA transfer error interrupts
    LL_DMA_EnableIT_TE(DMA_BASE, DMA_CHANNEL);

    // Enable the DMA channel
    LL_DMA_EnableChannel(DMA_BASE, DMA_CHANNEL);
}


/**
 * @brief  DMA transfer complete callback
 * @note   This function is executed when the transfer complete interrupt
 *         is generated
 * @retval None
 */
void ADC_DMA_TransferComplete_Callback(void)
{
    // Update the DMA transfer status
    dmaTransferStatus = 1;

    // Verify the ADC conversion was completed
    if (adcConversionStatus != 1) {
        ADC_DMA_TransferError_Callback();
    }

    // Reset the ADC conversion status
    adcConversionStatus = 0;
}

/**
  * @brief  DMA transfer error callback
  * @note   This function is executed when the transfer error interrupt
  *         is generated during DMA transfer
  * @retval None
  */
void ADC_DMA_TransferError_Callback(void)
{
    // Handle the error
    while(1);
}

/**
 * @brief  ADC group regular end of sequence conversions interruption callback
 * @note   This function is executed when the ADC group regular
 *         sequencer has converted all ranks of the sequence.
 * @retval None
 */
void ADC_ConvComplete_Callback(void)
{
    // Update the ADC conversion status
    adcConversionStatus = 1;
}

/**
  * @brief  ADC group regular overrun interruption callback
  * @note   This function is executed when ADC group regular
  *         overrun error occurs.
  * @retval None
  */
void ADC_OverrunError_Callback(void)
{
    // Disable ADC overrun interrupts
    LL_ADC_DisableIT_OVR(ADC_BAT_BASE);
}
