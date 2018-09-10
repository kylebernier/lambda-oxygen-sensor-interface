/**
 * @file hw_map.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 September 8
 *
 * @brief Maps hardware peripherals to board specific features
 *
 */


#include "hw_map.h"

#include "stm32l4xx_ll_bus.h"


/* Initialize GPIO pins */
void HW_Init_GPIO(void)
{
    // Enable the clock for GPIO port A
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);


    // Configure the GPIO pin as a ADC input
    LL_GPIO_SetPinMode(ADC_BAT_GPIO_PORT, ADC_BAT_GPIO_PIN,
        LL_GPIO_MODE_ANALOG);
    // Map GPIO pin to the ADC
    LL_GPIO_EnablePinAnalogControl(ADC_BAT_GPIO_PORT, ADC_BAT_GPIO_PIN);

    // Configure the GPIO pin as a ADC input
    LL_GPIO_SetPinMode(ADC_CRT_GPIO_PORT, ADC_CRT_GPIO_PIN,
        LL_GPIO_MODE_ANALOG);
    // Map GPIO pin to the ADC
    LL_GPIO_EnablePinAnalogControl(ADC_CRT_GPIO_PORT, ADC_CRT_GPIO_PIN);

    // Configure the GPIO pin as a ADC input
    LL_GPIO_SetPinMode(ADC_VTG_GPIO_PORT, ADC_VTG_GPIO_PIN,
        LL_GPIO_MODE_ANALOG);
    // Map GPIO pin to the ADC
    LL_GPIO_EnablePinAnalogControl(ADC_VTG_GPIO_PORT, ADC_VTG_GPIO_PIN);

    // Configure the GPIO pin as a DAC input
    LL_GPIO_SetPinMode(DAC_LMD_GPIO_PORT, DAC_LMD_GPIO_PIN,
        LL_GPIO_MODE_ANALOG);

    /*************************/
    /* GPIO AF configuration */
    /*************************/
    /* Enable the peripheral clock of GPIOs */
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);

    /* GPIO TIM1_CH1 configuration */
    LL_GPIO_SetPinMode(GPIOE, LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinPull(GPIOE, LL_GPIO_PIN_11, LL_GPIO_PULL_DOWN);
    LL_GPIO_SetPinSpeed(GPIOE, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetAFPin_0_7(GPIOE, LL_GPIO_PIN_11, LL_GPIO_AF_1);

    /******************************/
    /* Peripheral clocks enabling */
    /******************************/
    /* Enable the timer peripheral clock */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1); 
}
