/**
 * @file dac.c
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 July 29
 *
 * @brief Provides basic DAC functionality
 *
 */

#include "dac.h"

/* Initialize the DAC interface */
int Init_DAC(void)
{
    volatile uint32_t i = 0;

    // Enable the clock for the DAC
    DACx_CLK_ENABLE();

    // Set the DAC trigger source to software
    LL_DAC_SetTriggerSource(DAC_FUN_BASE, DAC_FUN_CHANNEL, LL_DAC_TRIG_SOFTWARE);

    // Configure the DAC output for channel 2
    LL_DAC_ConfigOutput(DAC_FUN_BASE, DAC_FUN_CHANNEL, LL_DAC_OUTPUT_MODE_NORMAL, LL_DAC_OUTPUT_BUFFER_ENABLE, LL_DAC_OUTPUT_CONNECT_GPIO);

    // Enable the DMA underrun interrupt for channel 2
    LL_DAC_EnableIT_DMAUDR2(DAC_FUN_BASE);

    // Enable the DAC for channel 2
    LL_DAC_Enable(DAC_FUN_BASE, DAC_FUN_CHANNEL);

    // Delay to allow the DAC voltage to settle
    i = ((LL_DAC_DELAY_STARTUP_VOLTAGE_SETTLING_US * (SystemCoreClock / (100000 * 2))) / 10);
    while (i != 0)
    {
        i--;
    }

    // Enable the DAC
    LL_DAC_EnableTrigger(DAC_FUN_BASE, DAC_FUN_CHANNEL);

    return 0;
}

/* Adjust the DAC output value */
void DAC_SetValue(uint32_t value)
{
    // Set the DAC value
    LL_DAC_ConvertData12RightAligned(DAC_FUN_BASE, DAC_FUN_CHANNEL, 0xFFF & value);
    // Tigger a DAC conversion
    LL_DAC_TrigSWConversion(DAC_FUN_BASE, DAC_FUN_CHANNEL);
}
