#ifndef __STM32L4XX_IT_H
#define __STM32L4XX_IT_H


#include "stm32l4xx_ll_adc.h"
#include "stm32l4xx_ll_dma.h"


void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void ADC1_2_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);


#endif // __STM32L4XX_IT_H
