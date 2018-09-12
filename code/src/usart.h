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

#include "stm32l4xx_ll_usart.h"

#define USARTx_INSTANCE USART1

/* Initializes the USART */
void Init_USART();

/* Transfers data */
void USART_Transfer();

#endif /* __USART_H */
