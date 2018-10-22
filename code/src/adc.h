/**
 * @file adc.h
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 July 15
 *
 * @brief Provides basic ADC functionality
 *
 */


#ifndef __ADC_H
#define __ADC_H

#include "hw_map.h"

/* Initialize the ADC with DMA */
void Init_ADC(
    uint32_t channels,
    uint16_t * values,
    int numValues
);
/* Callback for a complete DMA transfer */
void ADC_DMA_TransferComplete_Callback(void);
/* Callback for a failed DMA transfer */
void ADC_DMA_TransferError_Callback(void);
/* Callback for a complete ADC conversion */
void ADC_ConvComplete_Callback(void);
/* Callback for a ADC overrun error */
void ADC_OverrunError_Callback(void);


#endif // __ADC_H
