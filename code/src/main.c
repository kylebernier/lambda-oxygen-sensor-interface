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
#include "arm_math.h"
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

uint16_t optimal_resistance;
uint32_t currentV;
uint32_t Vbat = 12000;

#define CONDENSATION 3900
#define Kp 60   // Proportional Coefficient
#define Ki 0.8  // Integral Coefficient
#define Kd 0    // Derivative Coefficient 

/**
 * @brief Main program entrypoint
 * 
 * @return Should not return 
 */
int main(void)
{
    uint8_t *data_out;
    uint16_t response = 0;
    uint16_t lambda, temp, UA, UR;
    uint16_t optimal_lambda;
    uint32_t minVbat, desiredV;
    int16_t error;
    static int16_t last_error = 0;
    int16_t integral = 0;
    int16_t derivative;
    //uint64_t t1, t2, diff; // Only used for timing
    float pwm_duty_cycle;
    int16_t change; 
    int i = 0;

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

    // Enable cycle counter; Use for timing
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    
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
    

    // Set t1 to how many clock cycles have gone by
    //t1 = DWT->CYCCNT;
    
    // Initialize heater before using it
    Initialize_Heater();
    
    // Set t2 to how many clock cycles have gone by
    //t2 = DWT->CYCCNT;
    // Determine the amount of time passed since start
    //diff = t2-t1;

    // Continuous loop to read in values from CJ125, adjust heater, and output data.
    while(1) {
        
        // Read in battery voltage, lambda voltage and restance values from CJ125
        UA = adc_vals[1];
        UR = adc_vals[2];

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
        if (lambda >= 650 && lambda < 1360) {
            DAC_SetValue((lambda-650)*4096/710);
        } else if (lambda >= 1360) {
            DAC_SetValue(4095);
        } else if (lambda < 650) {
            DAC_SetValue(0);
        }

        // Enable LED on PA8
        //MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE8, GPIO_MODER_MODE8_0);
        // Turn on LED before UART Transmit
        //SET_BIT(GPIOA->ODR, GPIO_ODR_OD8_Msk);

        // Output lambda and temperature via UART
        data_out = (uint8_t *)(&lambda);
        USART_Transmit(data_out, 2);
        data_out = (uint8_t *)(&temp);
        USART_Transmit(data_out, 2);

        // Turn off LED after UART transmission
        //CLEAR_BIT(GPIOA->ODR, GPIO_ODR_OD8_Msk);

        // Determine battery voltage
        //if (ADC_GetPWMValid()) {
            Vbat = (adc_vals[0] * 3300 / 4096) * 955 / 187;
        //}

        // Determine error between desired value and current value
        error = optimal_resistance - UR;
        
        // Set integral term
        integral = integral + error;

        // Set derivative term
        //derivative = error - last_error;
        
        // Calculate desired change to result in 0 error
        change = (Kp * error) + (Ki * integral);// + (Kd * derivative);

        // Set current error to last error for next loop through
        //last_error = error;

        // Set voltage based on desired change
        desiredV = currentV - change;

        // Adjust PWM signal for heater so it stays at 780C
        pwm_duty_cycle = pow((float)desiredV / Vbat, 2);

        LL_TIM_OC_SetCompareCH2(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);
        //LL_TIM_OC_SetCompareCH2(PWMx_BASE, 0);

        LL_mDelay(15);
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
    LL_Init1msTick(8000000);

    // Update CMSIS variable
    LL_SetSystemCoreClock(8000000);
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
    uint32_t avgCur, res;
    uint16_t CurADC, avgCurADC = 0;
    uint16_t UR;

    // Warm up heater, supply <= 2V to heater until out of condensation phase
    // Uses the current sense value to determine when condensation phase is over
    do {
        // Calculate the battery voltage from the ADC
        if (ADC_GetPWMValid()) {
            Vbat = (adc_vals[0] * 3279 / 4096) * 955 / 187;
        }

        // Set PWM signal to equivalent of 2Vrms
        currentV = 2000;
        pwm_duty_cycle = pow((float)currentV / Vbat, 2);
        LL_TIM_OC_SetCompareCH2(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);

        // Sample current sense ADC to determine the average value
        while(i < 50) {
            CurADC = adc_vals[3];
            if (CurADC > 450) {
                avgCurADC += CurADC;
                i++;
            }
        }

        avgCurADC /= i;

        // Calculate the most recent battery voltage
        if (ADC_GetPWMValid()) {
            Vbat = (adc_vals[0] * 3300 / 4096) * 973 / 187;
        }

        // Determine the actual current based on ADC values
        avgCur = (avgCurADC * 3300 / 4096);

        // Determine sensor resisitance
        res = Vbat * 7 * 50 / avgCur - 23;

        // Reset max current value for next loop through
        avgCurADC = 0;

        // Delay for 500ms
        LL_mDelay(50);
    } while (res < CONDENSATION);

    //currentV = 8500;
    // Set initial ramp up voltage to 8.5Vrms and ramp up at 0.4V/s
    do {
        // Get the current battery voltage
        if (ADC_GetPWMValid()) {
            Vbat = (adc_vals[0] * 3278 / 4096) * 955 / 187;
        }
        // Set PWM signal to equivalent of ramp up voltage RMS
        pwm_duty_cycle = pow((float)currentV / Vbat, 2);
        LL_TIM_OC_SetCompareCH2(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);

        UR = adc_vals[2];

        // Ramp up voltage by 200mV/s
        currentV += 1;
        // Delay 25ms
        LL_mDelay(5);
    } while (currentV < 11000 && UR > optimal_resistance);
}