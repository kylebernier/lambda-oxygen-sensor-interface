/**
 * @file main.c
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 May 27
 *
 * @brief Runs overall control for the CJ125 and LSU4.9 sensor
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
#include "cj125.h"

void Initialize_Heater(void);
void SystemClock_Config(void);
void Generate_Lookup_Tables(void);

/** @brief ADC values array 
 * Battery voltage, lambda value, sensor resistance, current sense 
 */
uint16_t adc_vals[5] = {0, 0, 0, 0, 0};

/**
 * @brief Lookup table for lambda values.
 * 
 * Values are calculated and inserted into array based on all possible ADC values
 */
uint16_t lambda_Lookup[4096];

/**
 * @brief Lookup table for temperature values.
 * 
 * Values are calculated and inserted into array based on all possible ADC values
 */
uint16_t temp_Lookup[4096];

/**
 * @brief The optimal ADC resistance value the CJ125 outputs during calibration.
 */
uint16_t optimal_resistance;

/**
 * @brief The optimal ADC resistance value the CJ125 outputs during calibration.
 */
uint16_t optimal_lambda;

/**
 * @brief The current voltage the PWM signal is using.
 */
uint32_t currentV;

/**
 * @brief Internal reference voltage of STM32.
 * 
 * This calculation is highlighted on page 583 of the RM0351 Reference Manual.
 */
uint32_t VDDA;

/**
 * @def CONDENSATION 
 * @brief Sensor resistance once condensation point has been reached.
 * 
 * This value represents the resistance of the actual sensor as it heats up. The higher
 * the resistance, the hotter the sensor.
 */
#define CONDENSATION 3900

/**
 * @def Kp 
 * @brief Proportional coefficient for the PID controller.
 * 
 * The proportional control is proportional to the error between the desired sensor 
 * resistance and the current resistance.
 */
#define Kp 60

/**
 * @def Ki 
 * @brief Integral coefficient for the PID controller.
 * 
 * The integral control is used to overcome steady state error for the P control. @n
 * In general the integral component is used for accumulating the running errors until the system stabilizes.
 */
#define Ki 0.8

/**
 * @def Kd
 * @brief Derivative coefficient for the PID controller.
 * 
 * The derivative control is used to prevent overshoot from the P control. @n
 * In general the derivative component is used to prevent the system from overshooting the desired result.
 */
#define Kd 0

/**
 * @def PREAMBLE
 * @brief Preamble signifies the start of a UART transmission.
 */
#define PREAMBLE 0xFFFF

/**
 * @def Vbat3V3
 * @brief Actual measured value for the 3V3 line on the PCB.
 * This value is required to make acurate readings of the battery voltage.
 */
#define Vbat3V3 3286

/**
 * @brief Main program entrypoint.
 * 
 * @return Should not return.
 */
int main(void)
{
    uint8_t *data_out;
    uint8_t i = 0;
    uint16_t response = 0;
    uint16_t lambda, lambda_adc, temp, temp_adc;
    int16_t derivative, error, change; 
    int16_t integral = 0;
    int16_t last_error = 0;
    uint32_t desiredV, Vbat;
    //uint64_t t1, t2, diff; // Only used for timing
    float pwm_duty_cycle;

    // Initialize the GPIO pins
    HW_Init_GPIO();

    // Config the system clock to 8MHz
    SystemClock_Config();

    // Initialize ADC on channels 0, 8, 11, 12, and 16
    Init_ADC(0x11901, (uint16_t *)adc_vals, 5);
    // Initialize DAC
    Init_DAC();
    // Initialize PWM with duty cycle of 0%
    Init_PWM();
    // Initialize USART connection to external device
    Init_USART();
    // Initialize SPI connection to CJ125
    Init_SPI();

    // Determine actual value of the 3.3V the STM is using.
    LL_mDelay(500);
    VDDA = VREFINT_CAL_VREF*(*VREFINT_CAL_ADDR)/adc_vals[0];

    /*
    // Enable cycle counter; Use for timing
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    */
    
    // Loop until CJ125 is ready. When CJ125 responds OK move on.
    while (response != CJ125_DIAG_REG_OK) {
        response = SPI_Transfer(CJ125_DIAG_REG);
        LL_mDelay(200);
    } 

    // Enter CJ125 calibration mode
    response = SPI_Transfer(CJ125_CALIBRATE_MODE);
    LL_mDelay(2000);

    // Store optimal resistance the CJ125 sees for the sensor
    optimal_resistance = adc_vals[3];

    // Store optimal lambda the CJ125 sees for the sensor; The result of this is close to 1
    optimal_lambda = adc_vals[2];

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
        // Read lambda and temp values from CJ125
        lambda_adc = adc_vals[2];
        temp_adc = adc_vals[3];

        // Find lambda and temp values in lookup table
        lambda = lambda_Lookup[lambda_adc];
        temp = temp_Lookup[temp_adc];

        // Output lambda value via DAC 
        // Contract specification only calls for 0.65 to 1.36, so all other values are capped
        if (lambda >= 650 && lambda < 1360) {
            DAC_SetValue((lambda-650)*4096/710);
        } else if (lambda >= 1360) {
            DAC_SetValue(4095);
        } else if (lambda < 650) {
            DAC_SetValue(0);
        }

        // Transmit over UART every 100ms
        if (i == 20) {
            // Turn on LED before UART Transmit
            SET_BIT(GPIOC->ODR, GPIO_ODR_OD9_Msk);
            
            // Transmit preamble before data
            USART_Transmit((uint8_t *)PREAMBLE, 2);

            // Transmit lambda value over UART
            data_out = (uint8_t *)(&lambda);
            USART_Transmit(data_out, 2);
            
            // Transmit temperature value over UART
            data_out = (uint8_t *)(&temp);
            USART_Transmit(data_out, 2);

            // Turn off LED after UART transmission
            CLEAR_BIT(GPIOC->ODR, GPIO_ODR_OD9_Msk);

            i = 0;
        }


        // Determine battery voltage
        Vbat = (adc_vals[1] * 3286 / 4096) * 955 / 187;

        // Determine error between desired value and current value
        error = optimal_resistance - temp_adc;
        
        // Set integral term
        integral = integral + error;

        // Set derivative term; Found not required for this setup
        derivative = error - last_error;
        
        // Calculate desired change to result in 0 error
        change = (Kp * error) + (Ki * integral) + (Kd * derivative);

        // Set current error to last error for next loop through; Found not required for this setup
        last_error = error;

        // Set voltage based on desired change
        if (currentV - change > Vbat) {
            desiredV = Vbat;
        } else if (currentV - change < 0) {
            desiredV = 0;
        } else {
            desiredV = currentV - change;
        }

        // Calculate PWM duty cycle
        pwm_duty_cycle = pow((float)desiredV / Vbat, 2);
        //pwm_duty_cycle = pow((float)2000 / Vbat, 2);

        // Adjust PWM signal for heater so it stays at 780C
        LL_TIM_OC_SetCompareCH2(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);

        i++;
        // Delay 10ms
        LL_mDelay(10);
    }
}

/**
 * @brief  System Clock Configuration.
 * 
 * The system Clock is configured as follows :
 *    System Clock source            = PLL (MSI)    @n
 *    SYSCLK(Hz)                     = 80000000     @n
 *    HCLK(Hz)                       = 80000000     @n
 *    AHB Prescaler                  = 1            @n
 *    APB1 Prescaler                 = 1            @n
 *    APB2 Prescaler                 = 1            @n
 *    MSI Frequency(Hz)              = 4000000      @n
 *    PLL_M                          = 1            @n
 *    PLL_N                          = 40           @n
 *    PLL_R                          = 2            @n
 *    Flash Latency(WS)              = 4            @n
 * @retval None
 */
void SystemClock_Config(void) {
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
    uint16_t CurADC, VbatADC, UR;
    uint16_t maxCurADC = 0;
    uint32_t Vbat, maxCur, res;

    // Warm up heater, supply <= 2V to heater until out of condensation phase
    // Uses the current sense value to determine when condensation phase is over
    do {
        // Calculate the battery voltage from the ADC
        Vbat = (adc_vals[1] * 3286 / 4096) * 955 / 187;

        // Set initial "warm-up" voltage to 2V
        currentV = 2000;

        // Calculate PWM duty cycle using equation found in LSU 4.9 manual
        pwm_duty_cycle = pow((float)currentV / Vbat, 2);

        // Set PWM signal to equivalent of 2Vrms
        LL_TIM_OC_SetCompareCH2(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);

        // Sample current sense ADC to determine the maximum value
        for (i= 0; i < 50; i++) {
            CurADC = adc_vals[4];
            if (CurADC > maxCurADC) {
                maxCurADC = CurADC;
                VbatADC = adc_vals[1];
            }
            // Delay 10ms
            LL_mDelay(10);
        }

        // Determine the actual current based on ADC values
        maxCur = (maxCurADC * VDDA / 4096);

        // Determine the actual voltage at highest ADC value
        Vbat = (VbatADC * 3286 / 4096) * 955 / 187;

        // Determine sensor resisitance
        res = Vbat * 7 * 50 / maxCur - 23;

        // Reset max current value for next loop through
        maxCurADC = 0;

        // Delay for 500ms
        LL_mDelay(50);
    } while (res < CONDENSATION);

    // Generate lookup tables for both lambda and temperature values
    Generate_Lookup_Tables();

    //currentV = 8500;
    // Set initial ramp up voltage to 8.5Vrms and ramp up at 0.4V/s
    do {
        // Get the current battery voltage
        Vbat = (adc_vals[1] * 3286 / 4096) * 955 / 187;

        // Calculate duty cycle, equation from LSU 4.9 datasheet
        pwm_duty_cycle = pow((float)currentV / Vbat, 2);

        // Set PWM signal to equivalent of ramp up voltage RMS
        LL_TIM_OC_SetCompareCH2(PWMx_BASE, LL_TIM_GetAutoReload(PWMx_BASE)*pwm_duty_cycle);

        UR = adc_vals[3];

        // Ramp up voltage by 200mV/s
        currentV += 1;
        // Delay 25ms
        LL_mDelay(5);
    } while (currentV < 11000 && UR > optimal_resistance);
}

/**
 * @brief Generates lookup tables for lambda and temperature values
 * Equations were determined by applying best fit curves to plots present in
 * the LSU4.9 manual. @n
 * MATLAB was used to fit the plots.
 * 
 * @retval None
 */
void Generate_Lookup_Tables(void) {
    int16_t i;
    uint32_t uacal, ua, urcal, ur;
    int32_t lambda, temp;
    float ip, o2, ri;
    // Determine resistance calibration value for calculations further on
    ur = optimal_resistance * VDDA * (365 + 187) / 365 / 4096;
    urcal = -((15.5 * 0.000158 * 301) * 1000 - ur) * 17;

    // Determine lambda calibration value for calculations further on
    uacal = optimal_lambda * VDDA * (365 + 187) / 365 / 4096;

    for (i = 0; i < 4096; i++) {
        // Calculate the Lambda value
        ua = i * VDDA * (365 + 187) / 365 / 4096;      // mV
        ip = (ua - uacal) * 1000 / (61.9 * 8);         // mA
        o2 = ip * 0.2095 / 2540;
        lambda = (o2 / 3 + 1) / (1 - 4.77 * o2) * 1000;
        if (lambda >= 10119 || lambda <= 0) {
            lambda = 10119;
        }
        // Set lambda lookup table value
        lambda_Lookup[i] = lambda;

        // Calculate the temperature value
        ur = i * VDDA * (365 + 187) / 365 / 4096;
        ri = (ur - urcal / 17) / (15.5 * 0.158);
        temp = 4445 * pow(ri, -0.4449) + 428.6;
        if (temp >= 7049|| temp <= 0) {
            temp = 7049;
        }
        // Set temperature lookup table value
        temp_Lookup[i] = temp;
    }
}