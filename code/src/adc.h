/**
 * @file adc.h
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Provides basic ADC functionality
 */

#ifndef __ADC_H
#define __ADC_H

#include "hw_map.h"

/**
 * @brief Initialize the ADC with DMA 
 * 
 * @param channels ADC channels to read from
 * @param values Array to store ADC values
 * @param numValues Number of values in values array
 * 
 * @retval None
 */
void Init_ADC(
    uint32_t channels,
    uint16_t * values,
    int numValues
);

/**
 * @brief Initialize DMA for the ADC 
 * 
 * @param values Array to store ADC values
 * @param numValues Number of values in values array
 * 
 * @retval None
 */
static void ADC_Init_DMA(
    uint16_t * values,
    int numValues
);

/**
 * @brief DMA transfer complete callback
 * 
 * @note This function is executed when the transfer complete interrupt
 *         is generated
 * 
 * @retval None
 */
void ADC_DMA_TransferComplete_Callback(void);

/**
  * @brief  DMA transfer error callback
  * 
  * @note   This function is executed when the transfer error interrupt
  *         is generated during DMA transfer
  * 
  * @retval None
  */
void ADC_DMA_TransferError_Callback(void);

/**
 * @brief ADC group regular end of sequence conversions interruption callback
 * 
 * @note This function is executed when the ADC group regular
 *         sequencer has converted all ranks of the sequence.
 * 
 * @retval None
 */
void ADC_ConvComplete_Callback(void);

/**
  * @brief ADC group regular overrun interruption callback
  * 
  * @note This function is executed when ADC group regular
  *         overrun error occurs.
  * 
  * @retval None
  */
void ADC_OverrunError_Callback(void);

#endif // __ADC_H
