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


int Init_DAC(void)
{
    volatile uint32_t i = 0;

    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_ANALOG);

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);

    LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_2, LL_DAC_TRIG_SOFTWARE);

    LL_DAC_ConfigOutput(DAC1, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_MODE_NORMAL, LL_DAC_OUTPUT_BUFFER_ENABLE, LL_DAC_OUTPUT_CONNECT_GPIO);

    LL_DAC_EnableIT_DMAUDR1(DAC1);

    LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_2);

    i = ((LL_DAC_DELAY_STARTUP_VOLTAGE_SETTLING_US * (SystemCoreClock / (100000 * 2))) / 10);
    while(i != 0)
    {
        i--;
    }

    LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_2);

    return 0;
}

void DAC_SetValue(uint32_t value)
{
    LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, 0xFFF & value);

    LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_2);
}
