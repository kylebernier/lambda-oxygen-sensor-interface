/**
 * @file hw_map.h
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Maps hardware peripherals to board specific features
 *
 */


#ifndef __HW_MAP_H
#define __HW_MAP_H


#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_adc.h"


/* ADC Battery Monitor */
#define ADC_BAT_BASE ADC1
#define ADC_BAT_GPIO_PIN LL_GPIO_PIN_0
#define ADC_BAT_GPIO_PORT GPIOA
#define ADC_BAT_CHANNEL LL_ADC_CHANNEL_5
#define ADC_BAT_SAMPLETIME LL_ADC_SAMPLINGTIME_640CYCLES_5

/* ADC Current Monitor */
#define ADC_CRT_BASE ADC1
#define ADC_CRT_GPIO_PIN LL_GPIO_PIN_1
#define ADC_CRT_GPIO_PORT GPIOA
#define ADC_CRT_CHANNEL LL_ADC_CHANNEL_6
#define ADC_CRT_SAMPLETIME LL_ADC_SAMPLINGTIME_640CYCLES_5

/* ADC Voltage Monitor */
#define ADC_VTG_BASE ADC1
#define ADC_VTG_GPIO_PIN LL_GPIO_PIN_2
#define ADC_VTG_GPIO_PORT GPIOA
#define ADC_VTG_CHANNEL LL_ADC_CHANNEL_7
#define ADC_VTG_SAMPLETIME LL_ADC_SAMPLINGTIME_640CYCLES_5

/* DAC Lambda Output */
#define DAC_LMD_BASE DAC1
#define DAC_LMD_GPIO_PIN LL_GPIO_PIN_4
#define DAC_LMD_GPIO_PORT GPIOA
#define DAC_LMD_CHANNEL LL_DAC_CHANNEL_1

/* DAC Fun */
#define DAC_FUN_BASE DAC1
#define DAC_FUN_GPIO_PIN LL_GPIO_PIN_5
#define DAC_FUN_GPIO_PORT GPIOA
#define DAC_FUN_CHANNEL LL_DAC_CHANNEL_2

/* SPI CJ125 */
#define SPI_CJ125_BASE SPI1
#define SPI_CJ125_SCK_PIN LL_GPIO_PIN_3
#define SPI_CJ125_SCK_PORT GPIOB
#define SPI_CJ125_MISO_PIN LL_GPIO_PIN_4
#define SPI_CJ125_MISO_PORT GPIOB
#define SPI_CJ125_MOSI_PIN LL_GPIO_PIN_5
#define SPI_CJ125_MOSI_PORT GPIOB


/* Initialize GPIO pins */
void HW_Init_GPIO(void);


#endif // __HW_MAP_H
