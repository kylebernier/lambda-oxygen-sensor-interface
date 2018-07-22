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


#include "stm32l4xx_hal.h"


// ADC Battery Monitor
#define ADC_BAT_BASE ADC1
#define ADC_BAT_GPIO_PIN GPIO_PIN_0
#define ADC_BAT_GPIO_PORT GPIOA
#define ADC_BAT_CHANNEL ADC_CHANNEL_5
#define ADC_BAT_SAMPLETIME ADC_SAMPLETIME_640CYCLES_5

// ADC Current Monitor
#define ADC_CRT_BASE ADC1
#define ADC_CRT_GPIO_PIN GPIO_PIN_1
#define ADC_CRT_GPIO_PORT GPIOA
#define ADC_CRT_CHANNEL ADC_CHANNEL_6
#define ADC_CRT_SAMPLETIME ADC_SAMPLETIME_640CYCLES_5

// ADC Voltage Monitor
#define ADC_VTG_BASE ADC1
#define ADC_VTG_GPIO_PIN GPIO_PIN_2
#define ADC_VTG_GPIO_PORT GPIOA
#define ADC_VTG_CHANNEL ADC_CHANNEL_7
#define ADC_VTG_SAMPLETIME ADC_SAMPLETIME_640CYCLES_5


#endif // __HW_MAP_H
