/**
 * @file spi.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Provides basic SPI functionality
 *
 */


#include "stm32l4xx.h"

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_spi.h"
#include "stm32l4xx_ll_dma.h"

#include "spi.h"


static void SPI_Init_DMA(
    uint8_t * send_buf,
    uint8_t * recv_buf,
    int max_transfer_size
);


volatile static uint8_t spiTransmitComplete = 0;
volatile static uint8_t spiReceiveComplete = 0;

void Init_SPI(uint8_t * send_buf, uint8_t * recv_buf, int max_transfer_size)
{
    // Initialize DMA for SPI
    SPI_Init_DMA(send_buf, recv_buf, max_transfer_size);

    // Enable the clock for SPI1
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

    // Configure the SPI1 interface
    LL_SPI_SetBaudRatePrescaler(SPI1, LL_SPI_BAUDRATEPRESCALER_DIV256);
    LL_SPI_SetTransferDirection(SPI1,LL_SPI_FULL_DUPLEX);
    LL_SPI_SetClockPhase(SPI1, LL_SPI_PHASE_2EDGE);
    LL_SPI_SetClockPolarity(SPI1, LL_SPI_POLARITY_HIGH);
    LL_SPI_SetDataWidth(SPI1, LL_SPI_DATAWIDTH_8BIT);
    LL_SPI_SetNSSMode(SPI1, LL_SPI_NSS_SOFT);
    LL_SPI_SetRxFIFOThreshold(SPI1, LL_SPI_RX_FIFO_TH_QUARTER);
    LL_SPI_SetMode(SPI1, LL_SPI_MODE_MASTER);

    // Enable the DMA rx interupt
    LL_SPI_EnableDMAReq_RX(SPI1);
    // Enable the DMA tx interupt
    LL_SPI_EnableDMAReq_TX(SPI1);

    // Enable the SPI interface
    LL_SPI_Enable(SPI1);
}

static void SPI_Init_DMA(
    uint8_t * send_buf,
    uint8_t * recv_buf,
    int max_transfer_size
)
{
    // Enable the clock for DMA1
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

    // Configure the DMA interupts
    NVIC_SetPriority(DMA1_Channel2_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    NVIC_SetPriority(DMA1_Channel3_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Channel3_IRQn);

    // Configure the DMA1 Channel2 for SPI rx
    LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_2,
        LL_DMA_DIRECTION_PERIPH_TO_MEMORY | LL_DMA_PRIORITY_HIGH |
        LL_DMA_MODE_NORMAL | LL_DMA_PERIPH_NOINCREMENT |
        LL_DMA_MEMORY_INCREMENT | LL_DMA_PDATAALIGN_BYTE |
        LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2,
        LL_SPI_DMA_GetRegAddr(SPI1), (uint32_t)recv_buf,
        LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2));
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, max_transfer_size);
    LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMA_REQUEST_1);

    // Configure the DMA1 Channel2 for SPI tx
    LL_DMA_ConfigTransfer(DMA1, LL_DMA_CHANNEL_3,
        LL_DMA_DIRECTION_MEMORY_TO_PERIPH | LL_DMA_PRIORITY_HIGH |
        LL_DMA_MODE_NORMAL | LL_DMA_PERIPH_NOINCREMENT |
        LL_DMA_MEMORY_INCREMENT | LL_DMA_PDATAALIGN_BYTE |
        LL_DMA_MDATAALIGN_BYTE);
    LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_3,
        (uint32_t)send_buf, LL_SPI_DMA_GetRegAddr(SPI1),
        LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3));
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, max_transfer_size);
    LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_3, LL_DMA_REQUEST_1);

    // Enable DMA interupts for transfer complete and error
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_3);
    LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_3);
}

void SPI_Transfer(void)
{
    spiTransmitComplete = 0;
    spiReceiveComplete = 0;

    // Enable the transmit and receive DMA channels
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

    // Wait for the SPI transmission to finish
    while (spiTransmitComplete != 1);

    // Disable the transmit DMA channel
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);

    // Wait for the SPI receive to finish
    while (spiReceiveComplete != 1);

    // Disable the receive DMA channel
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
}

/**
 * @brief  Function called from DMA1 IRQ Handler when Rx transfer is completed
 * @param  None
 * @retval None
 */
void SPI_DMA_ReceiveComplete_Callback(void)
{
    /* DMA Rx transfer completed */
    spiReceiveComplete = 1;
}

/**
  * @brief  Function called from DMA1 IRQ Handler when Tx transfer is completed
  * @param  None
  * @retval None
  */
void SPI_DMA_TransmitComplete_Callback(void)
{
    /* DMA Tx transfer completed */
    spiTransmitComplete = 1;
}

/**
  * @brief  Function called in case of error detected in SPI IT Handler
  * @param  None
  * @retval None
  */
void SPI_TransferError_Callback(void)
{
    // Disable the receive DMA channel
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);

    // Disable the transmit DMA channel
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
}
