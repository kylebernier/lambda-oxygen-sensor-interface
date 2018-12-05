/**
 * @file main.c
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 May 27
 *
 * @brief Runs overall control for the CJ125 and LSU4.9 sensor
 *
 */


#include "stm32l4xx.h"

#include "stm32l4xx_ll_rcc.h"
#include "stm32l4xx_ll_system.h"
#include "stm32l4xx_ll_utils.h"
#include <math.h>

#include "hw_map.h"
#include "adc.h"
#include "dac.h"
#include "pwm.h"
#include "usart.h"
#include "spi.h"
#include "temp.h"
#include "v8Lambda.h"
#include "v17Lambda.h"
#include "cj125.h"

void Initialize_Heater(void);
void SystemClock_Config(void);

/** @brief ADC values array 
 * Battery voltage, lambda value, sensor resistance, current sense 
 */
uint16_t adc_vals[4] = {0, 0, 0, 0};

#define CONDENSATION 4000

/**
 * @brief Main program entrypoint
 * 
 * @return Should not return 
 */
int main(void)
{
    uint16_t response = 0;
    uint8_t *data_out;
    uint16_t optimal_lambda, optimal_resistance, lambda, temp, UA, UR;
    float pwm_duty_cycle;
    uint32_t Vbat, desiredV = 0;

    // Initialize the GPIO pins
    HW_Init_GPIO();

    // Config the system clock to 8MHz
    SystemClock_Config();

    // Initialize ADC on channels 8, 11, 12, and 16
    Init_ADC(0x11900, (uint16_t *)adc_vals, 4);
    // Initialize DAC
    Init_DAC();
    // Initialize PWM with duty cycle of 0%
    Init_PWM();
    // Initialize USART connection to external device
    Init_USART();
    // Initialize SPI connection to CJ125
    Init_SPI();

    
    // Loop until CJ125 is ready. When CJ125 responds OK move on.
    while (response != CJ125_DIAG_REG_OK) {
        response = SPI_Transfer(CJ125_DIAG_REG);
        LL_mDelay(200);
    } 

    // Enter CJ125 calibration mode
    response = SPI_Transfer(CJ125_CALIBRATE_MODE);
    LL_mDelay(2000);

    // Store optimal values from CJ125
    optimal_lambda = adc_vals[1];
    optimal_resistance = adc_vals[2];

    // Set CJ125 into normal operation mode with an amplification of 8
    response = SPI_Transfer(CJ125_V8_MODE);
    //response = SPI_Transfer(CJ125_V17_MODE);
    

    // Initialize heater before using it
    Initialize_Heater();

    // Continuous loop to read in values from CJ125, adjust heater, and output data.
    while(1) {
        
        // Read in battery voltage, lambda voltage and restance values from CJ125
        UA = adc_vals[1];
        UR = adc_vals[2];
        //UA = optimal_lambda;
        //UR = optimal_resistance;

        // Calculate lambda value
        // If using the V=8 on the CJ125 comment out V17 section and uncomment this section
        if (UA >= 2142) {
            lambda = 10159;
        } else {
            lambda = v8Lambda_Lookup[UA];
        }
         
        // If using the V=17 on the CJ125 comment out V8 section and uncomment this section
        //if (UA >= 3170) {
        //    lambda = 10147;
        //} else {
        //    lambda = v17Lambda_Lookup[UA];
        //} 
        

        // Calculate heater temperature
        if (UR <= 315) {
            temp = 1816;
        } else {
            temp = temp_Lookup[UR];
        }

        // Output lambda value via DAC
        if (lambda >= 650 && lambda <= 10159) {
            DAC_SetValue((lambda-650)*4096/710);
        }

        // Output lambda and temperature via UART
        data_out = (uint8_t *)(&lambda);
        USART_Transmit(data_out, 2);
        data_out = (uint8_t *)(&temp);
        USART_Transmit(data_out, 2);
        

        // Adjust PWM signal for heater so it stays at 780C
        Vbat = (adc_vals[0] * 3300 / 4096) * 973 / 187;
        pwm_duty_cycle = pow(desiredV / Vbat, 2);
        LL_TIM_OC_SetCompareCH2(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);
    }
}

/**
 * @brief  System Clock Configuration
 * 
 * The system Clock is configured as follows :
 *    System Clock source            = PLL (MSI)
 *    SYSCLK(Hz)                     = 80000000
 *    HCLK(Hz)                       = 80000000
 *    AHB Prescaler                  = 1
 *    APB1 Prescaler                 = 1
 *    APB2 Prescaler                 = 1
 *    MSI Frequency(Hz)              = 4000000
 *    PLL_M                          = 1
 *    PLL_N                          = 40
 *    PLL_R                          = 2
 *    Flash Latency(WS)              = 4
 * @retval None
 */
void SystemClock_Config(void)
{
    // MSI configuration and activation
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
    LL_RCC_MSI_Enable();
    while(LL_RCC_MSI_IsReady() != 1);

    // Main PLL configuration and activation
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 4, LL_RCC_PLLR_DIV_2);
    LL_RCC_PLL_Enable();
    LL_RCC_PLL_EnableDomain_SYS();
    while(LL_RCC_PLL_IsReady() != 1);

    // Sysclk activation on the main PLL
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

    // Set APB1 & APB2 prescaler
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

    // Set systick to 1ms in using frequency set to 80MHz
    LL_Init1msTick(80000000);

    // Update CMSIS variable
    LL_SetSystemCoreClock(80000000);
}

/**
 * @brief Heater initialization routine
 * 
 * Initializes heater to a starting voltage of less than 2V during the condensation phase.
 * Once past condensation phase heater voltage is ramped up at a rate of 0.4V/s until
 * reaching a maximum of 13V. This is highlighted in section 1.6 of the LSU 4.9 manual.
 * 
 * @retval None
 */
void Initialize_Heater(void) {
    int i = 0;
    float pwm_duty_cycle;
    uint32_t Vbat, maxCur, res;
    uint16_t maxCurADC = 0;
    uint16_t VbatADC;
    uint16_t cur;

    // Sample current sense ADC to determine the maximum value
    for (i= 0; i < 50; i++) {
        cur = adc_vals[3];
        if (cur > maxCurADC) {
            maxCurADC = cur;
            VbatADC = adc_vals[0];
        }
    }

    // Determine the actual current based on ADC values
    maxCur = (maxCurADC * 3300 / 4096);

    // Warm up heater, supply <= 2V to heater until out of condensation phase
    // Uses the current sense value to determine when condensation phase is over
    do {
        // Get the current battery voltage
        Vbat = (VbatADC * 3300 / 4096) * 973 / 187;

        // Determine sensor resisitance
        res = Vbat * 7 * 50 / maxCur - 23;

        // Set PWM signal to equivalent of 2Vrms
        pwm_duty_cycle = pow(2000.0 / Vbat, 2);
        LL_TIM_OC_SetCompareCH2(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);

        // Delay for 500ms
        LL_mDelay(500);
    } while (res < CONDENSATION);

    i = 0;
    // Set initial ramp up voltage to 8.5Vrms and ramp up at 0.4V/s
    while (8500 + i < 11000) {
        // Get the current battery voltage
        Vbat = (adc_vals[0] * 3300 / 4096) * 973 / 187;
        // Set PWM signal to equivalent of ramp up voltage RMS
        pwm_duty_cycle = pow((8500.0 + i) / Vbat, 2);
        LL_TIM_OC_SetCompareCH2(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);

        // Ramp up voltage by 200mV/s
        i += 5;
        // Delay 25ms
        LL_mDelay(25);
    }
}
