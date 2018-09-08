/**
 * @file dac.h
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 29
 *
 * @brief Provides basic DAC functionality
 *
 */


#ifndef __DAC_H
#define __DAC_H


#include "stm32l4xx.h"

#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_dac.h"


/* Initialize the DAC interface */
int Init_DAC(void);
/* Adjust the DAC output value */
void DAC_SetValue(uint32_t value);


#endif // __DAC_H
