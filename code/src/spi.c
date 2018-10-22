/**
 * @file spi.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Provides basic SPI functionality
 *
 * @todo Add select line
 */

#include "spi.h"

/* Inialize the SPI interface */
void Init_SPI(uint8_t * send_buf, uint8_t * recv_buf, int max_transfer_size)
{
    // Enable the clock for the SPI
    SPIx_CLK_ENABLE();

    // Configure the SPI interface
    LL_SPI_SetBaudRatePrescaler(SPI_CJ125_BASE, LL_SPI_BAUDRATEPRESCALER_DIV256);
    LL_SPI_SetTransferDirection(SPI_CJ125_BASE,LL_SPI_FULL_DUPLEX);
    LL_SPI_SetClockPhase(SPI_CJ125_BASE, LL_SPI_PHASE_2EDGE);
    LL_SPI_SetClockPolarity(SPI_CJ125_BASE, LL_SPI_POLARITY_HIGH);
    LL_SPI_SetDataWidth(SPI_CJ125_BASE, LL_SPI_DATAWIDTH_8BIT);
    LL_SPI_SetNSSMode(SPI_CJ125_BASE, LL_SPI_NSS_SOFT);
    LL_SPI_SetRxFIFOThreshold(SPI_CJ125_BASE, LL_SPI_RX_FIFO_TH_QUARTER);
    LL_SPI_SetMode(SPI_CJ125_BASE, LL_SPI_MODE_MASTER);

    // Enable the SPI interface
    LL_SPI_Enable(SPI_CJ125_BASE);
}

/* Complete an SPI transfer */
void SPI_Transfer(uint8_t * send, uint8_t * recv, int send_size, int recv_size)
{
    int i;

    // Send the send buffer
    for (i = 0; i < send_size; i++) {
        // Wait for TX buffer to be empty
        while(!LL_SPI_IsActiveFlag_TXE(SPI_CJ125_BASE));
        // Transmit a byte
        LL_SPI_TransmitData8(SPI_CJ125_BASE, send[i]);
    }

    // Receive to the recv buffer
    for (i = 0; i < recv_size; i++) {
        // Wait for TX buffer to be empty
        while(!LL_SPI_IsActiveFlag_TXE(SPI_CJ125_BASE));
        // Receive a byte
        recv[i] = LL_SPI_ReceiveData8(SPI_CJ125_BASE);
    }
}
