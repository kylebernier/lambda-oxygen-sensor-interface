/**
 * @file usart.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 September 12
 *
 * @brief Provides basic USART functionality.
 *
 */
#include "usart.h"

uint8_t ubSend = 0;
const uint8_t aStringToSend[] = "Hello";

/* Initialize the USART */
void Init_USART(void) {
    /* Set transfer direction (Tx/Rx) */
    LL_USART_SetTransferDirection(USARTx_INSTANCE, LL_USART_DIRECTION_TX_RX);

    /* Set 8 data bits, 1 start bit, 1 stop bit, and no parity */
    LL_USART_ConfigCharacter(USARTx_INSTANCE, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

    /* Set baud rate */
    LL_USART_SetBaudRate(USARTx_INSTANCE, SystemCoreClock, LL_USART_OVERSAMPLING_16, 115200); 

    /* Enable USART */
    LL_USART_Enable(USARTx_INSTANCE);

    /* Polling USART initialisation */
    while((!(LL_USART_IsActiveFlag_TEACK(USARTx_INSTANCE))) || (!(LL_USART_IsActiveFlag_REACK(USARTx_INSTANCE))));
}

/* Transmit data */
void USART_Transfer() {
    /* Send characters one per one, until last char to be sent */
    while (ubSend < sizeof(aStringToSend)) {
      /* Wait for TXE flag to be raised */
      while (!LL_USART_IsActiveFlag_TXE(USARTx_INSTANCE));

      /* If last char to be sent, clear TC flag */
      if (ubSend == (sizeof(aStringToSend) - 1)) {
        LL_USART_ClearFlag_TC(USARTx_INSTANCE); 
      }

      /* Write character in Transmit Data register. TXE flag is cleared by writing data in TDR register */
      LL_USART_TransmitData8(USARTx_INSTANCE, aStringToSend[ubSend++]);
    }

    /* Wait for TC flag to be raised for last char */
    while (!LL_USART_IsActiveFlag_TC(USARTx_INSTANCE));

    /* Transmission is over, reset send amount */
    ubSend = 0;
}
