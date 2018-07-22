/**
 * @file adc.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 15
 * 
 * @brief Provides basic ADC functionality
 *
 */


#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"


/* Array of ADC channels */
uint32_t ADC_CHANNELS[16] = {
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12,
    ADC_CHANNEL_13,
    ADC_CHANNEL_14,
    ADC_CHANNEL_15
};

/* Array of ADC channel ranks */
uint32_t ADC_RANKS[16] = {
    ADC_REGULAR_RANK_1,
    ADC_REGULAR_RANK_2,
    ADC_REGULAR_RANK_3,
    ADC_REGULAR_RANK_4,
    ADC_REGULAR_RANK_5,
    ADC_REGULAR_RANK_6,
    ADC_REGULAR_RANK_7,
    ADC_REGULAR_RANK_8,
    ADC_REGULAR_RANK_9,
    ADC_REGULAR_RANK_10,
    ADC_REGULAR_RANK_11,
    ADC_REGULAR_RANK_12,
    ADC_REGULAR_RANK_13,
    ADC_REGULAR_RANK_14,
    ADC_REGULAR_RANK_15,
    ADC_REGULAR_RANK_16
};

/* Global ADC configuration variables */
ADC_HandleTypeDef AdcHandle;
ADC_ChannelConfTypeDef sConfig;


/* Initialize the ADC with DMA */
void Init_ADC(
    uint32_t channels,
    uint32_t * values,
    int numValues
)
{
    int i, j;

    // Use ADC1
    AdcHandle.Instance = ADC1;
    if (HAL_ADC_DeInit(&AdcHandle) != HAL_OK) {
        while (1);
    }

    // Set the ADC configuration
    AdcHandle.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
    AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
    AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    AdcHandle.Init.ScanConvMode = ENABLE;
    AdcHandle.Init.EOCSelection = ADC_EOC_SEQ_CONV;
    AdcHandle.Init.LowPowerAutoWait = DISABLE;
    AdcHandle.Init.ContinuousConvMode = ENABLE;
    AdcHandle.Init.NbrOfConversion = numValues;
    AdcHandle.Init.DiscontinuousConvMode = DISABLE;
    AdcHandle.Init.NbrOfDiscConversion = numValues;
    AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    AdcHandle.Init.DMAContinuousRequests = ENABLE;
    AdcHandle.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
    AdcHandle.Init.OversamplingMode = DISABLE;

    // Initialize ADC with the above configurations
    if (HAL_ADC_Init(&AdcHandle) != HAL_OK) {
        while (1);
    }

    // Start the ADC calibrartion
    if (HAL_ADCEx_Calibration_Start(&AdcHandle, ADC_SINGLE_ENDED) !=  HAL_OK) {
        while (1);
    }

    // Configure individual ADC channels
    sConfig.SamplingTime = ADC_SAMPLETIME_640CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    for (i = 0, j = 0; i < 12; i++) {
        if (channels & (1 << i)) {
            sConfig.Channel = ADC_CHANNELS[i];
            sConfig.Rank = ADC_RANKS[j];
            if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK) {
                while (1);
            }
            j++;
        }
        if (j == numValues) break;
    }

    // Start DMA for the ADC
    if (HAL_ADC_Start_DMA(&AdcHandle, values, 3) != HAL_OK) {
        while (1);
    }
}
