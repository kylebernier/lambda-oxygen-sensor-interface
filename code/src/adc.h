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


/* Initialize the ADC with DMA */
void Init_ADC(
    uint32_t channels,
    uint32_t * values,
    int numValues
);


#endif // __ADC_H
