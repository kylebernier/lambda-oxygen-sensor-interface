/**
 * @file dac.h
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 July 29
 *
 * @brief Provides basic DAC functionality
 *
 */


#ifndef __DAC_H
#define __DAC_H

#include "hw_map.h"

/**
 * @brief Initialize the DAC interface 
 * @retval None
 */
int Init_DAC(void);

/** 
 * @brief Adjust the DAC output value 
 * @param value Value to set the DAC output to
 * @retval None
 */
void DAC_SetValue(uint32_t value);

#endif // __DAC_H
