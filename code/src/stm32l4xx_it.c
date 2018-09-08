#include "stm32l4xx.h"

#include "stm32l4xx_ll_adc.h"
#include "stm32l4xx_ll_dma.h"

#include "adc.h"


/**
 * @brief   This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles PendSVC exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
}

/**
  * @brief  This function handles ADC1 interrupt request.
  * @param  None
  * @retval None
  */
void ADC1_2_IRQHandler(void)
{
    // Check if the interupt is end of conversion
    if(LL_ADC_IsActiveFlag_EOS(ADC1) != 0)
    {
        // Clear the end of conversion flag
        LL_ADC_ClearFlag_EOS(ADC1);

        // Call the ADC conversion complete callback
        ADC_ConvComplete_Callback();
    }

    // Check if the interupt is overrun
    if(LL_ADC_IsActiveFlag_OVR(ADC1) != 0)
    {
        // Clear the ADC overrun flag
        LL_ADC_ClearFlag_OVR(ADC1);

        // Call the ADC conversion complete callback
        ADC_OverrunError_Callback();
    }
}

/**
  * @brief  This function handles DMA1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void)
{
    // Check if the DMA transfer is complete
    if(LL_DMA_IsActiveFlag_TC1(DMA1) == 1)
    {
        // Clear the DMA interupt flag
        LL_DMA_ClearFlag_GI1(DMA1);

        // Call the DMA transfer complete callback
        ADC_DMA_TransferComplete_Callback();
    }

    // Check if the DMA transfer casused an error
    if(LL_DMA_IsActiveFlag_TE1(DMA1) == 1)
    {
        // Clear the DMA error flag
        LL_DMA_ClearFlag_TE1(DMA1);

        // Call the DMA transfer error callback
        ADC_DMA_TransferError_Callback();
    }
}
