/**
 * @file spi.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Provides basic SPI functionality
 *
 */

#include "spi.h"

/* Inialize the SPI interface */
void Init_SPI(void)
{
    // Enable the clock for the SPI
    SPIx_CLK_ENABLE();

    // Configure the SPI interface
    LL_SPI_SetBaudRatePrescaler(SPI_CJ125_BASE, LL_SPI_BAUDRATEPRESCALER_DIV256);
    LL_SPI_SetTransferDirection(SPI_CJ125_BASE,LL_SPI_FULL_DUPLEX);
    LL_SPI_SetClockPhase(SPI_CJ125_BASE, LL_SPI_PHASE_2EDGE);
    LL_SPI_SetClockPolarity(SPI_CJ125_BASE, LL_SPI_POLARITY_LOW);
    LL_SPI_SetDataWidth(SPI_CJ125_BASE, LL_SPI_DATAWIDTH_8BIT);
    LL_SPI_SetNSSMode(SPI_CJ125_BASE, LL_SPI_NSS_SOFT);
    LL_SPI_SetRxFIFOThreshold(SPI_CJ125_BASE, LL_SPI_RX_FIFO_TH_QUARTER);
    LL_SPI_SetMode(SPI_CJ125_BASE, LL_SPI_MODE_MASTER);

    // Enable the SPI interface
    LL_SPI_Enable(SPI_CJ125_BASE);

    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE12, GPIO_MODER_MODE12_0);
}

/* Complete an SPI transfer */
void SPI_Transfer(uint16_t send, uint16_t recv, int send_size, int recv_size)
{
    int i;

    // Set SPI select line low
    CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD12_Msk);

    for (i = 0; i < send_size; i++) {
        // Wait for TX buffer to be empty
        while(!LL_SPI_IsActiveFlag_TXE(SPI_CJ125_BASE));
        // Reverse byte order
        send = ((send << 8) & 0xff00) | ((send >> 8) & 0x00ff);
        // Transmit a byte
        LL_SPI_TransmitData16(SPI_CJ125_BASE, send);
        // Wait for transmit to finish
        while (SPI_CJ125_BASE->SR & SPI_SR_BSY);
    }

    for (i = 0; i < recv_size; i++) {
        // Wait for TX buffer to be empty
        while(!LL_SPI_IsActiveFlag_TXE(SPI_CJ125_BASE));
        // Receive a byte
        recv = LL_SPI_ReceiveData16(SPI_CJ125_BASE);
        // Reverse byte order
        recv = ((recv << 8) & 0xff00) | ((recv >> 8) & 0x00ff);
        // Wait for transmit to finish
        while (SPI_CJ125_BASE->SR & SPI_SR_BSY);
    }
    
    // Set SPI select line high
    SET_BIT(GPIOB->ODR, GPIO_ODR_OD12_Msk);

    return recv;
}
