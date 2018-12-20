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
 * @brief Initializes the USART.
 * 
 * The USART initialization sets the UART to a TX/RX transmisson.
 * The UART has the typical 8 data, 1 start, and 1 stop bits with no parity.
 * The baudrate for the UART is set to 115200.
 * 
 * @retval None 
 */
void Init_USART();

/**
 * @brief Transfers data over the transmit line.
 *  
 * The UART is set up to handle both transmit and receive, however, 
 * nothing is done with the received data. The receive line is 
 * available for future changes. 
 * 
 * @param send Array of desired send data
 * @param size Size of data array
 * @retval None
 */
void USART_Transmit(uint8_t *send, uint8_t size);

#endif /* __USART_H */
