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
#include "stm32l4xx_ll_tim.h"

/*****************************/
/* ADC Definitions */
/*****************************/
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

/*****************************/
/* DAC Definitions */
/*****************************/
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

/*****************************/
/* PWM Definitions */
/*****************************/
#define PWMx_BASE TIM1
#define PWMx_CHANNEL LL_TIM_CHANNEL_CH2
#define PWMx_CLK_ENABLE() LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1)

#define PWMx_GPIO_CLK_ENABLE() LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE)
#define PWMx_GPIO_PIN LL_GPIO_PIN_11
#define PWMx_GPIO_PORT GPIOE
#define PWMx_SET_GPIO_AF() LL_GPIO_SetAFPin_8_15(GPIOE, LL_GPIO_PIN_11, LL_GPIO_AF_1)

/* Initialize GPIO pins */
void HW_Init_GPIO(void);

#endif // __HW_MAP_H
