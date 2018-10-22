/**
 * @file spi.h
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 September 8
 *
 * @brief Provides basic SPI functionality
 *
 */



/**
 * @file spi.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Provides basic SPI functionality
 *
 */

#ifndef __SPI_H
#define __SPI_H

#include "hw_map.h"

void Init_SPI(uint8_t * send_buf, uint8_t * recv_buf, int max_transfer_size);
void SPI_Transfer(uint8_t * send, uint8_t * recv, int send_size, int recv_size);

#endif // __SPI_H
