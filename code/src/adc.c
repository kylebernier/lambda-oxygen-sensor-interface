#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

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

void Init_ADC(
    ADC_TypeDef * inst,
    uint32_t channels,
    uint32_t * values,
    int numValues
)
{
    int i, j;
    ADC_HandleTypeDef hadc;
    ADC_ChannelConfTypeDef sConfig;

    hadc.Instance = inst;
    hadc.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc.Init.ContinuousConvMode = ENABLE;
    hadc.Init.DiscontinuousConvMode = DISABLE;
    hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc.Init.NbrOfDiscConversion = 0;
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc.Init.NbrOfConversion = 2;

    sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;

    for (i = 0; i < 12; i++) {
        if (channels & (1 << i)) {
            sConfig.Channel = ADC_CHANNELS[i];
            sConfig.Rank = ADC_RANKS[j];
            HAL_ADC_ConfigChannel(&hadc, &sConfig);
            j++;
        }
        if (j == numValues) break;
    }

    HAL_ADC_Start_DMA(&hadc, values, numValues);
}
