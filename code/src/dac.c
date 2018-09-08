/**
 * @file dac.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 29
 *
 * @brief Provides basic DAC functionality
 *
 */


#include "stm32l4xx.h"

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_dac.h"

#include "dac.h"


/* Initialize the DAC interface */
int Init_DAC(void)
{
    volatile uint32_t i = 0;

    // Enable the clock for the DAC
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1);

    // Set the DAC trigger source to software
    LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_2, LL_DAC_TRIG_SOFTWARE);

    // Configure the DAC output for channel 2
    LL_DAC_ConfigOutput(DAC1, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_MODE_NORMAL, LL_DAC_OUTPUT_BUFFER_ENABLE, LL_DAC_OUTPUT_CONNECT_GPIO);

    // Enable the DMA underrun interrupt for channel 2
    LL_DAC_EnableIT_DMAUDR2(DAC1);

    // Enable the DAC for channel 2
    LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_2);

    // Delay to allow the DAC voltage to settle
    i = ((LL_DAC_DELAY_STARTUP_VOLTAGE_SETTLING_US * (SystemCoreClock / (100000 * 2))) / 10);
    while(i != 0)
    {
        i--;
    }

    // Enable the DAC
    LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_2);

    return 0;
}

/* Adjust the DAC output value */
void DAC_SetValue(uint32_t value)
{
    // Set the DAC value
    LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, 0xFFF & value);
    // Tigger a DAC conversion
    LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_2);
}
