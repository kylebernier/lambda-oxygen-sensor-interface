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
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_dac.h"
#include "stm32l4xx_ll_tim.h"
#include "stm32l4xx_ll_usart.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_bus.h"

/*****************************/
/* ADC Definitions */
/*****************************/
/* ADC Battery Voltage Monitor */
#define ADC_BAT_BASE ADC1
#define ADC_BAT_GPIO_PIN LL_GPIO_PIN_3
#define ADC_BAT_GPIO_PORT GPIOA
#define ADC_BAT_CHANNEL LL_ADC_CHANNEL_8
#define ADC_BAT_SAMPLETIME LL_ADC_SAMPLINGTIME_640CYCLES_5
#define ADC_BAT_IRQ ADC1_2_IRQn

/* ADC Lambda Value Monitor */
#define ADC_CRT_BASE ADC1
#define ADC_CRT_GPIO_PIN LL_GPIO_PIN_6
#define ADC_CRT_GPIO_PORT GPIOA
#define ADC_CRT_CHANNEL LL_ADC_CHANNEL_11
#define ADC_CRT_SAMPLETIME LL_ADC_SAMPLINGTIME_640CYCLES_5

/* ADC Resistance Monitor */
#define ADC_VTG_BASE ADC1
#define ADC_VTG_GPIO_PIN LL_GPIO_PIN_7
#define ADC_VTG_GPIO_PORT GPIOA
#define ADC_VTG_CHANNEL LL_ADC_CHANNEL_12
#define ADC_VTG_SAMPLETIME LL_ADC_SAMPLINGTIME_640CYCLES_5

/* ADC Clock */
#define ADCx_CLK_ENABLE() LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC)

/*****************************/
/* DMA Definitions */
/*****************************/
/* ADC DMA */
#define DMA_BASE DMA1
#define DMA_CHANNEL LL_DMA_CHANNEL_1
#define DMA_IRQ DMA1_Channel1_IRQn

/* DMA Clock */
#define DMAx_CLK_ENABLE() LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);


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

/* DAC clock setup */
#define DACx_CLK_ENABLE() LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1)

/*****************************/
/* PWM Definitions */
/*****************************/
#define PWMx_BASE TIM8
#define PWMx_CHANNEL LL_TIM_CHANNEL_CH1
#define PWMx_CLK_ENABLE() LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8)

#define PWMx_GPIO_CLK_ENABLE() LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC)
#define PWMx_GPIO_PIN LL_GPIO_PIN_6
#define PWMx_GPIO_PORT GPIOC
#define PWMx_SET_GPIO_AF() LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_6, LL_GPIO_AF_3)

/*****************************/
/* USART Definitions */
/*****************************/
#define USARTx_CLK_ENABLE() LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#define USARTx_CLK_SOURCE() LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2)

#define USARTx_GPIO_CLK_ENABLE() LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA)   
#define USARTx_TX_PIN LL_GPIO_PIN_9
#define USARTx_TX_GPIO_PORT GPIOA
#define USARTx_SET_TX_GPIO_AF() LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7)
#define USARTx_RX_PIN LL_GPIO_PIN_10
#define USARTx_RX_GPIO_PORT GPIOA
#define USARTx_SET_RX_GPIO_AF() LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7)

/*****************************/
/* SPI CJ125 */
/*****************************/
#define SPIx_GPIO_CLK_ENABLE() LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB)
#define SPIx_CLK_ENABLE() LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
#define SPI_CJ125_BASE SPI2
#define SPI_CJ125_SCK_PIN LL_GPIO_PIN_13
#define SPI_CJ125_SCK_PORT GPIOB
#define SPI_CJ125_MISO_PIN LL_GPIO_PIN_14
#define SPI_CJ125_MISO_PORT GPIOB
#define SPI_CJ125_MOSI_PIN LL_GPIO_PIN_15
#define SPI_CJ125_MOSI_PORT GPIOB
#define SPI_CJ125_SEL_PIN LL_GPIO_PIN_12
#define SPI_CJ125_SEL_PORT GPIOB

/* Initialize GPIO pins */
void HW_Init_GPIO(void);

#endif // __HW_MAP_H
