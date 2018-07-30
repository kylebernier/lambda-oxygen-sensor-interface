/**
 * @file dac.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 29
 * 
 * @brief Provides basic DAC functionality
 *
 */


#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"


DAC_HandleTypeDef DacHandle;
static DAC_ChannelConfTypeDef sConfig;


int dac_init(void)
{
    HAL_StatusTypeDef hal_ret;

    hal_ret = HAL_DAC_DeInit(&DacHandle);
    if (hal_ret != HAL_OK) {
        while(1);
    }

    hal_ret = HAL_DAC_Init(&DacHandle);
    if (hal_ret != HAL_OK) {
        while(1);
    }

    sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
    sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
    sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
    sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;

    hal_ret = HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DAC_CHANNEL_1);
    if (hal_ret != HAL_OK) {
        while(1);
    }

    hal_ret = HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DAC_CHANNEL_2);
    if (hal_ret != HAL_OK) {
        while(1);
    }

    hal_ret = HAL_DACEx_DualSetValue(&DacHandle, DAC_ALIGN_12B_R, 0xFF, 0xFF);
    if (hal_ret != HAL_OK) {
        while(1);
    }

    hal_ret = HAL_DAC_Start(&DacHandle, DAC_CHANNEL_1);
    if (hal_ret != HAL_OK) {
        while(1);
    }

    hal_ret = HAL_DAC_Start(&DacHandle, DAC_CHANNEL_2);
    if (hal_ret != HAL_OK) {
        while(1);
    }

    while (1);
}
