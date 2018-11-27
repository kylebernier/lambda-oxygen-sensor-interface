/**
 * @file usart.h
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 September 12
 *
 * @brief Provides basic USART functionality.
 *
 */

#ifndef __USART_H
#define __USART_H

#include "hw_map.h"

/**
 * @brief Initializes the USART 
 * @retval None 
 */
void Init_USART();

/**
 * @brief Transfers data 
 * @param send Array of desired send data
 * @param size Size of data array
 * @retval None
 */
void USART_Transmit(uint8_t *send, uint8_t size);

#endif /* __USART_H */
