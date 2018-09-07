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


#include "stm32l4xx_ll_bus.h"
#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_cortex.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_exti.h"
#include "stm32l4xx_ll_adc.h"
#include "stm32l4xx_ll_dma.h"


/* Initialize the ADC with DMA */
void Init_ADC(
    uint32_t channels,
    uint16_t * values,
    int numValues
);
void ADC_DMA_TransferComplete_Callback(void);
void ADC_DMA_TransferError_Callback(void);
void ADC_ConvComplete_Callback(void);
void ADC_OverrunError_Callback(void);


#endif // __ADC_H
