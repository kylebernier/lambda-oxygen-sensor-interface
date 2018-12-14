/**
 * @file adc.h
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Provides ADC functionality
 */

#ifndef __ADC_H
#define __ADC_H

#include "hw_map.h"

/**
 * @brief Initialize the ADC with DMA 
 * 
 * Initialization of the desired channels is done by taking the reverse of
 * the binary expansion of the channels.
 * ie. Enabling channels 3, 8, 11, & 12 the representation would be:
 * - - - 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 * 0 0 0  0| 0  0  0  1| 1  0 0 1|0 0 0 0|1 0 0 0
 * 
 * Which results in a hexidecimal number of 0x01908
 * 
 * @param channels ADC channels to read from
 * @param values Array to store ADC values
 * @param numValues Number of values in values array
 * 
 * @retval None
 */
void Init_ADC(uint32_t channels, uint16_t * values, int numValues);

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


uint8_t ADC_GetPWMValid(void);

#endif // __ADC_H
