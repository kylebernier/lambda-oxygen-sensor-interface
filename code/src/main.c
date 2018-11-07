/**
 * @file main.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 May 27
 *
 * @brief Blinks an led and updates variables with the ADC.
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


#define CJ125_IDENT_REG         0x4800  // Identify request
#define CJ125_DIAG_REG          0x7800  // Diagnostic request
#define CJ125_DIAG_REG_OK       0x28ff  // Diagnostic response CJ125 ready
#define CJ125_DIAG_REG_NOPWR    0x2855  // Diagnostic response no/low power
#define CJ125_DIAG_REG_NOSNSR   0x287f  // Diagnostic response no sensor
#define CJ125_CALIBRATE_MODE    0x569d  // Calibration mode for CJ125
#define CJ125_V8_MODE           0x5688  // Set CJ125 into V=8 mode
#define CJ125_V17_MODE          0x5689  // Set CJ125 into V=17 mode

void SystemClock_Config(void);
void Initialize_Heater(void);


uint16_t aResultDMA[3];
// ADC values: Battery voltage, lambda value, sensor resistance
uint16_t adc_vals[3] = {0, 0, 0};

int main(void)
{
    uint16_t response = 0;
    int i = 0;
    uint8_t *data_out;
    uint16_t optimal_lambda, optimal_resistance, lambda, temp, UA, UR;

    // Initialize the GPIO pins
    HW_Init_GPIO();

    // Config the system clock to 8MHz
    SystemClock_Config();

    // Initialize ADC on channels 8, 10, and 11
    Init_ADC(0x1900, (uint16_t *)adc_vals, 3);
    // Initialize DAC
    Init_DAC();
    // Initialize PWM with duty cycle of 0%
    Init_PWM();
    // Initialize USART connection to external device
    Init_USART();
    // Initialize SPI connection to CJ125
    Init_SPI();

    /*
    // Loop until CJ125 is ready. When CJ125 responds OK move on.
    while (response != CJ125_DIAG_REG_OK || adc_vals[0] < BAT_MIN) {
        SPI_Transfer(CJ125_DIAG_REG, response, 1, 1);
        LL_mDelay(200);
    } 

    // Enter CJ125 calibration mode
    SPI_Transfer(CJ125_CALIBRATE_MODE, response, 1, 0);
    delay(2000);

    // Store optimal values from CJ125
    optimal_lambda = adc_vals[1];
    optimal_resistance = adc_vals[2];

    // Set CJ125 into normal operation mode with an amplification of 8
    SPI_Transfer(CJ125_V8_MODE, response, 1, 0);
    SPI_Transfer(CJ125_V17_MODE, response, 1, 0);
    */

    // Initialize heater before using it
    //Initialize_Heater();

    // Continuous loop to read in values from CJ125, adjust heater, and output data.
    while(1) {
        // Read in battery voltage, lambda voltage and restance values from CJ125
        UA = adc_vals[1];
        UR = adc_vals[2];

        // Calculate lambda value and heater temperature
        //v8Lambda = 10159;
        //v17Lambda = 10159;
        temp = 780;

        // Output lambda value via DAC
        DAC_SetValue((lambda-650)*4096/710);

        // Output lambda and temperature via UART
        data_out = (uint8_t *)(&lambda);
        USART_Transmit(data_out, 2);
        data_out = (uint8_t *)(&temp);
        USART_Transmit(data_out, 2);

        // Adjust PWM signal for heater so it stays at 780C
        LL_mDelay(500);
    }
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follows :
 *            System Clock source            = PLL (MSI)
 *            SYSCLK(Hz)                     = 8000000
 *            HCLK(Hz)                       = 8000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 1
 *            APB2 Prescaler                 = 1
 *            MSI Frequency(Hz)              = 4000000
 *            PLL_M                          = 1
 *            PLL_N                          = 40
 *            PLL_R                          = 2
 *            Flash Latency(WS)              = 4
 * @param  None
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

    // Set systick to 1ms in using frequency set to 8MHz
    LL_Init1msTick(8000000);

    // Update CMSIS variable
    LL_SetSystemCoreClock(8000000);
}

/* Initializes heater to start at a low voltage and then ramp up to operating range. */
void Initialize_Heater(void) {
    int i = 0;
    float pwm_duty_cycle;
    uint32_t Vbat;

    // Warm up heater, supply <= 2V to heater for 5 seconds to heat it during condensation phase.
    while (i < 20) {
        // Set PWM signal to equivalent of 2Vrms
        Vbat = (adc_vals[0] * 3300 / 4096) * 973 / 187;
        pwm_duty_cycle = pow(2000.0 / Vbat, 2);
        LL_TIM_OC_SetCompareCH1(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);

        LL_mDelay(500);
        i++;
    }

    // Set initial ramp up voltage to 8.5Vrms
    i = 0;
    while (8500 + i < 11000) {
        Vbat = (adc_vals[0] * 3300 / 4096) * 973 / 187;
        pwm_duty_cycle = pow((8500.0 + i) / Vbat, 2);
        LL_TIM_OC_SetCompareCH1(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);

        // Ramp up voltage by 400mV/s
        i += 10;
        LL_mDelay(25);
    }
}
