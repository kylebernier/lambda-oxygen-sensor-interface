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

    // Enable the clock for GPIO port B
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

    // Enable the clock for GPIO port E
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);


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


    // Configure the SPI SCK pin
    LL_GPIO_SetPinMode(SPI_CJ125_SCK_PORT, SPI_CJ125_SCK_PIN,
        LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_8_15(SPI_CJ125_SCK_PORT, SPI_CJ125_SCK_PIN, LL_GPIO_AF_5);
    LL_GPIO_SetPinSpeed(SPI_CJ125_SCK_PORT, SPI_CJ125_SCK_PIN,
        LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinPull(SPI_CJ125_SCK_PORT, SPI_CJ125_SCK_PIN,
        LL_GPIO_PULL_DOWN);

    // Configure the SPI MISO pin
    LL_GPIO_SetPinMode(SPI_CJ125_MISO_PORT, SPI_CJ125_MISO_PIN,
        LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_8_15(SPI_CJ125_MISO_PORT, SPI_CJ125_MISO_PIN, LL_GPIO_AF_5);
    LL_GPIO_SetPinSpeed(SPI_CJ125_MISO_PORT, SPI_CJ125_MISO_PIN,
        LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinPull(SPI_CJ125_MISO_PORT, SPI_CJ125_MISO_PIN,
        LL_GPIO_PULL_DOWN);

    // Configure the SPI MOSI pin
    LL_GPIO_SetPinMode(SPI_CJ125_MOSI_PORT, SPI_CJ125_MOSI_PIN,
        LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_8_15(SPI_CJ125_MOSI_PORT, SPI_CJ125_MOSI_PIN, LL_GPIO_AF_5);
    LL_GPIO_SetPinSpeed(SPI_CJ125_MOSI_PORT, SPI_CJ125_MOSI_PIN,
        LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinPull(SPI_CJ125_MOSI_PORT, SPI_CJ125_MOSI_PIN,
        LL_GPIO_PULL_DOWN);
}
