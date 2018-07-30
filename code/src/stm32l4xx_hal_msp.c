#include "hw_map.h"

/**
 * @brief  ADC MSP Init
 * @param  hadc : ADC handle
 * @retval None
 */
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    static DMA_HandleTypeDef DmaHandle;

    // Configure clocks
    __HAL_RCC_ADC_CLK_ENABLE();
    __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_SYSCLK);
    __HAL_RCC_DMA1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // ADC Battery Monitor GPIO Pin Configuration
    GPIO_InitStruct.Pin = ADC_BAT_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ADC_BAT_GPIO_PORT, &GPIO_InitStruct);

    // ADC Current Monitor GPIO Pin Configuration
    GPIO_InitStruct.Pin = ADC_CRT_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ADC_CRT_GPIO_PORT, &GPIO_InitStruct);

    // ADC Voltage Monitor GPIO Pin Configuration
    GPIO_InitStruct.Pin = ADC_VTG_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG_ADC_CONTROL;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(ADC_VTG_GPIO_PORT, &GPIO_InitStruct);

    // Initialize DMA for ADC
    DmaHandle.Instance = DMA1_Channel1;
    DmaHandle.Init.Request = DMA_REQUEST_0;
    DmaHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;
    DmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;
    DmaHandle.Init.MemInc = DMA_MINC_ENABLE;
    DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    DmaHandle.Init.Mode = DMA_CIRCULAR;
    DmaHandle.Init.Priority = DMA_PRIORITY_MEDIUM;

    // Deinitialize  & Initialize the DMA for new transfer
    HAL_DMA_DeInit(&DmaHandle);
    HAL_DMA_Init(&DmaHandle);

    // Associate the DMA handle
    __HAL_LINKDMA(hadc, DMA_Handle, DmaHandle);

    // NVIC configuration for DMA Input data interrupt
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/**
 * @brief ADC MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO to their default state
 * @param hadc: ADC handle pointer
 * @retval None
 */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
    __HAL_RCC_ADC_FORCE_RESET();
    __HAL_RCC_ADC_RELEASE_RESET();
    __HAL_RCC_ADC_CLK_DISABLE();

    HAL_GPIO_DeInit(ADC_BAT_GPIO_PORT, ADC_BAT_GPIO_PIN);
    HAL_GPIO_DeInit(ADC_CRT_GPIO_PORT, ADC_CRT_GPIO_PIN);
    HAL_GPIO_DeInit(ADC_VTG_GPIO_PORT, ADC_VTG_GPIO_PIN);
}

/**
 * @brief DAC MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 * @param hdac: DAC handle pointer
 * @retval None
 */
void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_DAC1_CLK_ENABLE();

    GPIO_InitStruct.Pin = DAC_LMD_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DAC_LMD_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DAC_FUN_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DAC_FUN_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * @brief  DeInitializes the DAC MSP.
 * @param  hdac: pointer to a DAC_HandleTypeDef structure that contains
 *         the configuration information for the specified DAC.
 * @retval None
 */
void HAL_DAC_MspDeInit(DAC_HandleTypeDef *hdac)
{
    __HAL_RCC_DAC1_FORCE_RESET();
    __HAL_RCC_DAC1_RELEASE_RESET();
    __HAL_RCC_DAC1_CLK_DISABLE();

    HAL_GPIO_DeInit(DAC_LMD_GPIO_PORT, DAC_LMD_GPIO_PIN);
    HAL_GPIO_DeInit(DAC_FUN_GPIO_PORT, DAC_FUN_GPIO_PIN);
}

/**
 * @brief  Initializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspInit(void)
{
}

/**
 * @brief  DeInitializes the Global MSP.
 * @param  None
 * @retval None
 */
void HAL_MspDeInit(void)
{
}
