/**
 * @file spi.h
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Provides basic SPI functionality
 *
 */

#ifndef __SPI_H
#define __SPI_H

#include "hw_map.h"

/**
 * @brief Initialize the SPI Interface
 * 
 * @retval None
 */
void Init_SPI(void);

/**
 * @brief Complete an SPI Transfer
 * 
 * @param send Value to send
 * 
 * @returns Received data
 */
uint16_t SPI_Transfer(uint16_t send);

#endif // __SPI_H
