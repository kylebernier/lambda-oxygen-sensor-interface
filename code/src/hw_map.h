/**
 * @file hw_map.h
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Maps hardware peripherals to board specific features
 * 
 * Sets up definitions required for hardware peripherals. 
 * 
 * Includes: ADC, DAC, DMA, PWM, UART, SPI
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

/**
 * @defgroup ADC ADC definitions
 */

/**
 * @def ADCx_BASE General ADC used
 * @ingroup ADC
 * @brief ADC channel used for all.
 */
#define ADCx_BASE ADC1

/**
 * @defgroup ADC_BAT ADC Battery Voltage Monitor
 * @ingroup ADC
 * @brief ADC channel used to monitor battery voltage
 * 
 * These definitions are for the ADC that reads the current battery voltage.
 * 
 * @{
 */
/** @brief STM ADC */
#define ADC_BAT_BASE ADC1
/** @brief STM ADC GPIO Pin*/
#define ADC_BAT_GPIO_PIN LL_GPIO_PIN_3
/** @brief STM ADC GPIO Port*/
#define ADC_BAT_GPIO_PORT GPIOA
/** @brief STM ADC Channel*/
#define ADC_BAT_CHANNEL LL_ADC_CHANNEL_8
/** @brief ADC sample rate*/
#define ADC_BAT_SAMPLETIME LL_ADC_SAMPLINGTIME_12CYCLES_5
/** @brief STM ADC interrupt */
#define ADC_BAT_IRQ ADC1_2_IRQn
/** @} */

/**
 * @defgroup ADC_LMD ADC Lambda Value Monitor
 * @ingroup ADC
 * @brief ADC channel used to read lambda value
 * 
 * These definitions are for the ADC that reads the lambda value from the CJ125.
 * 
 * @{
 */ 
/** @brief STM ADC*/
#define ADC_LMD_BASE ADC1
/** @brief STM ADC GPIO Pin*/
#define ADC_LMD_GPIO_PIN LL_GPIO_PIN_6
/** @brief STM ADC GPIO Port*/
#define ADC_LMD_GPIO_PORT GPIOA
/** @brief STM ADC Channel*/
#define ADC_LMD_CHANNEL LL_ADC_CHANNEL_11
/** @brief STM ADC sample rate*/
#define ADC_LMD_SAMPLETIME LL_ADC_SAMPLINGTIME_12CYCLES_5
/** @} */

/**
 * @defgroup ADC_RES ADC Resistance Monitor
 * @ingroup ADC
 * @brief ADC channel used to read sensor resitance
 * 
 * These definitions are for the ADC that reads the oxygen sensor resistance
 * from the CJ125.
 * 
 * @{
 */
/** @brief STM ADC */
#define ADC_RES_BASE ADC1
/** @brief STM ADC GPIO Pin */
#define ADC_RES_GPIO_PIN LL_GPIO_PIN_7
/** @brief STM ADC GPIO Port */
#define ADC_RES_GPIO_PORT GPIOA
/** @brief STM ADC Channel */
#define ADC_RES_CHANNEL LL_ADC_CHANNEL_12
/** @brief STM ADC sample rate */
#define ADC_RES_SAMPLETIME LL_ADC_SAMPLINGTIME_12CYCLES_5
/** @} */

/**
 * @defgroup ADC_CRNT ADC PWM Current Sense
 * @ingroup ADC
 * @brief ADC channel used to sense current
 * 
 * @{
 */
/** @brief STM ADC */
#define ADC_CRNT_BASE ADC1
/** @brief STM ADC GPIO Pin */
#define ADC_CRNT_GPIO_PIN LL_GPIO_PIN_1
/** @brief STM ADC GPIO Port */
#define ADC_CRNT_GPIO_PORT GPIOB
/** @brief STM ADC Channel */
#define ADC_CRNT_CHANNEL LL_ADC_CHANNEL_16
/** @brief STM ADC sample rate */
#define ADC_CRNT_SAMPLETIME LL_ADC_SAMPLINGTIME_12CYCLES_5
/** @} */

/**
 * @def ADCx_CLK_ENABLE()
 * @ingroup ADC
 * @brief ADC definition for enabling peripheral clock.
 */
#define ADCx_CLK_ENABLE() LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC)

/**
 * @defgroup DMA DMA Definitions
 */

/**
 * @defgroup DMA_ADC ADC DMA 
 * @ingroup DMA
 * @{
 */
/** @brief STM DMA */
#define DMA_BASE DMA1
/** @brief STM DMA Channel */
#define DMA_CHANNEL LL_DMA_CHANNEL_1
/** @brief DMA Interrupt */
#define DMA_IRQ DMA1_Channel1_IRQn
/** @} */

/**
 * @def DMAx_CLK_ENABLE()
 * @ingroup DMA
 * @brief Enable DMA peripheral clock
 */
#define DMAx_CLK_ENABLE() LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);


/**
 * @defgroup DAC DAC Definitions
 */

/**
 * @defgroup DAC_LMD DAC Lambda Output 
 * @ingroup DAC
 * @{
 */
/** @brief STM DAC */
#define DAC_LMD_BASE DAC1
/** @brief STM DAC GPIO Pin */
#define DAC_LMD_GPIO_PIN LL_GPIO_PIN_5
/** @brief STM DAC GPIO Port */
#define DAC_LMD_GPIO_PORT GPIOA
/** @brief STM DAC Channel */
#define DAC_LMD_CHANNEL LL_DAC_CHANNEL_2
/** @} */

/**
 * @defgroup DAC_CLK DAC Clock 
 * @ingroup DAC
 * @{
 */
/** @brief Enable DAC peripheral clock */
#define DACx_CLK_ENABLE() LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_DAC1)
/** @} */


/**
 * @defgroup PWM PWM Definitions
 * @{
 */
/** @brief STM PWM timer */
#define PWMx_BASE TIM8
/** @brief STM PWM Timer channel */
#define PWMx_CHANNEL LL_TIM_CHANNEL_CH2
/** @brief STM PWM Timer Interrupt */
#define PWMx_IRQ TIM8_CC_IRQn
/** @brief STM PWM Interrupt channel */
#define PWMx_IRQ_CHANNEL LL_TIM_CHANNEL_CH1
/** @brief Enable PWM peripheral clock */
#define PWMx_CLK_ENABLE() LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8)

/** @brief Enable GPIO clock */
#define PWMx_GPIO_CLK_ENABLE() LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC)
/** @brief STM PWM GPIO Pin */
#define PWMx_GPIO_PIN LL_GPIO_PIN_7
/** @brief STM PWM GPIO Port */
#define PWMx_GPIO_PORT GPIOC
/** @brief Set PWM alternative function */
#define PWMx_SET_GPIO_AF() LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_7, LL_GPIO_AF_3)
/** @} */

/**
 * @defgroup USART USART Definitions
 * @{
 */
/** @brief STM USART */
#define USARTx_BASE USART1
/** @brief Enable peripheral clock */
#define USARTx_CLK_ENABLE() LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
/** @brief Set USART clock source */
#define USARTx_CLK_SOURCE() LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2)

/** @brief Enable GPIO clock */
#define USARTx_GPIO_CLK_ENABLE() LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA)   
/** @brief STM USART Transmit GPIO Pin */
#define USARTx_TX_PIN LL_GPIO_PIN_9
/** @brief STM USART Transmit GPIO Port */
#define USARTx_TX_GPIO_PORT GPIOA
/** @brief Set Transmit alternative function */
#define USARTx_SET_TX_GPIO_AF() LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_7)
/** @brief STM USART Receive GPIO Pin */
#define USARTx_RX_PIN LL_GPIO_PIN_10
/** @brief STM USART Receive GPIO Port */
#define USARTx_RX_GPIO_PORT GPIOA
/** @brief Set Receive alternative function */
#define USARTx_SET_RX_GPIO_AF() LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_7)
/** @} */

/**
 * @defgroup SPI SPI Definitions
 * @{
 */
/** @brief Enable GPIO clock */
#define SPIx_GPIO_CLK_ENABLE() LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB)
/** @brief Enable peripheral clock */
#define SPIx_CLK_ENABLE() LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
/** @brief STM SPI */
#define SPI_CJ125_BASE SPI2
/** @brief STM SPI Clock GPIO Pin */
#define SPI_CJ125_SCK_PIN LL_GPIO_PIN_13
/** @brief STM SPI Clock GPIO Port */
#define SPI_CJ125_SCK_PORT GPIOB
/** @brief STM SPI MISO GPIO Pin */
#define SPI_CJ125_MISO_PIN LL_GPIO_PIN_14
/** @brief STM SPI MISO GPIO Port */
#define SPI_CJ125_MISO_PORT GPIOB
/** @brief STM SPI MOSI GPIO Pin */
#define SPI_CJ125_MOSI_PIN LL_GPIO_PIN_15
/** @brief STM SPI MOSI GPIO Port */
#define SPI_CJ125_MOSI_PORT GPIOB
/** @brief STM SPI Select GPIO Pin */
#define SPI_CJ125_SEL_PIN LL_GPIO_PIN_12
/** @brief STM SPI Select GPIO Port */
#define SPI_CJ125_SEL_PORT GPIOB
/** @} */

/**
 * @brief Initializes hardware required by peripherals
 * @retval None
 */
void HW_Init_GPIO(void);

#endif // __HW_MAP_H
