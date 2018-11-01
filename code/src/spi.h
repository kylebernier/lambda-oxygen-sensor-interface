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

void Init_SPI(void);
void SPI_Transfer(uint16_t send, uint16_t recv, int send_size, int recv_size);

#endif // __SPI_H
