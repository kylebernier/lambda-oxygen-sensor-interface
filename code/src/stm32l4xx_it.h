/**
 * @file stm32l4xx_it.h
 * 
 */
#ifndef __STM32L4XX_IT_H
#define __STM32L4XX_IT_H


/**
 * @brief   This function handles NMI exception.
 * @retval None
 */
void NMI_Handler(void);

/**
 * @brief  This function handles Hard Fault exception.
 * @retval None
 */
void HardFault_Handler(void);

/**
 * @brief  This function handles Memory Manage exception.
 * @retval None
 */
void MemManage_Handler(void);

/**
 * @brief  This function handles Bus Fault exception.
 * @retval None
 */
void BusFault_Handler(void);

/**
 * @brief  This function handles Usage Fault exception.
 * @retval None
 */
void UsageFault_Handler(void);

/**
 * @brief  This function handles SVCall exception.
 * @retval None
 */
void SVC_Handler(void);

/**
 * @brief  This function handles Debug Monitor exception.
 * @retval None
 */
void DebugMon_Handler(void);

/**
 * @brief  This function handles PendSVC exception.
 * @retval None
 */
void PendSV_Handler(void);

/**
 * @brief  This function handles SysTick Handler.
 * @retval None
 */
void SysTick_Handler(void);

/**
  * @brief  This function handles ADC1 interrupt request.
  * @retval None
  */
void ADC1_2_IRQHandler(void);

/**
  * @brief  This function handles DMA1 interrupt request.
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void);

#endif // __STM32L4XX_IT_H
