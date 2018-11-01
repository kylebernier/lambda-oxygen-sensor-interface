/**
 * @file usart.h
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 September 12
 *
 * @brief Provides basic USART functionality.
 *
 */

#ifndef __USART_H
#define __USART_H

#include "hw_map.h"

/* Initializes the USART */
void Init_USART();

/* Transfers data */
void USART_Transmit(uint8_t *send, uint8_t size);

#endif /* __USART_H */
