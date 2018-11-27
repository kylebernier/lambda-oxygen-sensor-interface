/**
 * @file stm32l4xx_it.c
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @brief Interrupt setup for STM32L4xx
 * @date 2018-11-27
 */
#include "stm32l4xx.h"

#include "stm32l4xx_ll_adc.h"
#include "stm32l4xx_ll_dma.h"
#include "stm32l4xx_ll_spi.h"

#include "adc.h"
#include "spi.h"

/* This function handles NMI exceptions */
void NMI_Handler(void)
{
}

/* THis function handles Hard Fault exceptions */
void HardFault_Handler(void)
{
    // Enter an infinite loop
    while (1);
}

/* This function handles Memory Manage exceptions */
void MemManage_Handler(void)
{
    // Enter an infinite loop
    while (1);
}

/* This function handles Bus Fault exceptions */
void BusFault_Handler(void)
{
    // Enter an infinite loop
    while (1);
}

/* This function handles Fault exceptions */
void UsageFault_Handler(void)
{
    // Enter an infinite loop
    while (1);
}

/* This function handles SVCall exceptions */
void SVC_Handler(void)
{
}

/* This function handles Debug Monitor exceptions */
void DebugMon_Handler(void)
{
}

/* This function handles PendSVC exceptions */
void PendSV_Handler(void)
{
}

/* This function handles SysTick Handlers */
void SysTick_Handler(void)
{
}

/* This function handles ADC1 interrupt requests */
void ADC1_2_IRQHandler(void)
{
    // Check if the interupt is end of conversion
    if (LL_ADC_IsActiveFlag_EOS(ADC1) != 0) {
        // Clear the end of conversion flag
        LL_ADC_ClearFlag_EOS(ADC1);

        // Call the ADC conversion complete callback
        ADC_ConvComplete_Callback();
    }

    // Check if the interupt is overrun
    if (LL_ADC_IsActiveFlag_OVR(ADC1) != 0) {
        // Clear the ADC overrun flag
        LL_ADC_ClearFlag_OVR(ADC1);

        // Call the ADC conversion complete callback
        ADC_OverrunError_Callback();
    }
}

/* This function handles DMA1 interrupts requests */
void DMA1_Channel1_IRQHandler(void)
{
    // Check if the DMA transfer is complete
    if (LL_DMA_IsActiveFlag_TC1(DMA1) == 1) {
        // Clear the DMA interupt flag
        LL_DMA_ClearFlag_GI1(DMA1);

        // Call the DMA transfer complete callback
        ADC_DMA_TransferComplete_Callback();
    }

    // Check if the DMA transfer casused an error
    if (LL_DMA_IsActiveFlag_TE1(DMA1) == 1) {
        // Clear the DMA error flag
        LL_DMA_ClearFlag_TE1(DMA1);

        // Call the DMA transfer error callback
        ADC_DMA_TransferError_Callback();
    }
}
