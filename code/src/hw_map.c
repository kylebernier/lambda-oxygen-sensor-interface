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

    /************************/
    /* ADC Setup */
    /************************/
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

    /************************/
    /* DAC Setup */
    /************************/
    // Configure the GPIO pin as a DAC input
    LL_GPIO_SetPinMode(DAC_LMD_GPIO_PORT, DAC_LMD_GPIO_PIN,
        LL_GPIO_MODE_ANALOG);

    /*************************/
    /* PWM Setup */
    /*************************/
    /* Enable the peripheral clock of GPIOs */
    PWMx_GPIO_CLK_ENABLE();
  
    /* GPIO TIM2_CH1 configuration */
    LL_GPIO_SetPinMode(PWMx_GPIO_PORT, PWMx_GPIO_PIN, LL_GPIO_MODE_ALTERNATE);
    PWMx_SET_GPIO_AF();
    LL_GPIO_SetPinSpeed(PWMx_GPIO_PORT, PWMx_GPIO_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(PWMx_GPIO_PORT, PWMx_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(PWMx_GPIO_PORT, PWMx_GPIO_PIN, LL_GPIO_PULL_NO);

    /* Enable the timer peripheral clock */
    PWMx_CLK_ENABLE();

    /*************************/
    /* USART Setup */
    /*************************/
    /* Enable the peripheral clock of GPIO Port */
    USARTx_GPIO_CLK_ENABLE();

    /* Configure Tx Pin */
    LL_GPIO_SetPinMode(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_MODE_ALTERNATE);
    USARTx_SET_TX_GPIO_AF();
    LL_GPIO_SetPinSpeed(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_PULL_UP);

    /* Configure Rx Pin */
    LL_GPIO_SetPinMode(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_MODE_ALTERNATE);
    USARTx_SET_RX_GPIO_AF();
    LL_GPIO_SetPinSpeed(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_PULL_UP);

    /* Enable USART peripheral clock and clock source */
    USARTx_CLK_ENABLE();

    /* Set clock source */
    USARTx_CLK_SOURCE();
}
