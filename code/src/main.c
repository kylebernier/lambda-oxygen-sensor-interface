/**
 * @file main.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 May 27
 * 
 * @brief Blinks an led and updates variables with the ADC.
 *        Has basic functions to us FreeRTOS
 *
 */


#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

#include "adc.h"


void SystemClock_Config(void);


uint32_t aResultDMA[3];


/* Simple delay, will use systick at some point */
void delay(volatile unsigned delay)
{
    while (delay--);
}

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    Init_ADC(0xE0, (uint32_t *)aResultDMA, 3);

    // Enable GPIOB
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
    // Enable GPIOE
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN);

    // Set GPIOB_2 and GPIOE_8 as outputs
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE2, GPIO_MODER_MODE2_0);
    MODIFY_REG(GPIOE->MODER, GPIO_MODER_MODE8, GPIO_MODER_MODE8_0);

    // Alternate blinking of two leds
    while (1) {
        // Turn on read led
        SET_BIT(GPIOB->ODR, GPIO_ODR_OD2);
        // Turn off green led
        CLEAR_BIT(GPIOE->ODR, GPIO_ODR_OD8);

        // Delay a bit
        delay(200000);

        // Turn off red led
        CLEAR_BIT(GPIOB->ODR, GPIO_ODR_OD2);
        // Turn on green led
        SET_BIT(GPIOE->ODR, GPIO_ODR_OD8);

        // Delay a bit
        delay(200000);
    }
}

/**
 * @brief  System Clock Configuration
 * 
 * Hummels Config to give 80 MHz SYSCLK, with PLL48M1CLK=48 MHz
 *         The system Clock is configured as follows :
 *            System Clock source            = PLL (MSI)
 *            SYSCLK(Hz)                     = 80000000
 *            HCLK(Hz)                       = 80000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 1
 *            APB2 Prescaler                 = 1
 *            MSI Frequency(Hz)              = 16000000 (MSI Range=8) 
 *            PLL_M                          = 2
 *            PLL_N                          = 20
 *            PLL_R                          = 2 ( SYSCLK = PLLCLK = (16MHz)*N/M/R = 80 MHz )
 *            PLL_P                          = 7 (No reason for this...)
 *            PLL_Q                          = 5 ( PLL48M1CLK = (16MHz)(N/M/Q) = 32 MHz ?! )
 *            Flash Latency(WS)              = 4
 * 
 * HSE: Not assumed active (xtal not populated on STM32L476G-Discovery)
 * MSI: 16 MHz (multiple speed internal RC Oscillator, configured using Range=8)
 * HSI: 16 MHz (Fixed frequency high speed internal Oscillator)
 * LSI: 32.768 kHz (Low freq internal oscillator)
 *    ( MSI *N/M = 160 MHz )
 * SYSCLK: 80 MHz  (= 160/R)
 * HCLK (AHB Bus, Core, Memory, and DMA): 80 MHz (Max value)
 * PCLK1 (APB1 Periferals, some USARTs and Timers): 80 MHz (Max value)
 * PCLK2 (APB2 Periferals, some USARTs and Timers): 80 MHz (Max value)
 * 
 * (ALTERNATIVE???  Use the HSI as the reference oscillator.  Change N to 15.)
 * 
 * @param  None
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};

    /* MSI is enabled after System reset, activate PLL with MSI as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_8;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    RCC_OscInitStruct.PLL.PLLM = 2;
    RCC_OscInitStruct.PLL.PLLN = 20; 
    RCC_OscInitStruct.PLL.PLLR = 2;  
    RCC_OscInitStruct.PLL.PLLP = 7;
    RCC_OscInitStruct.PLL.PLLQ = 5;
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        /* Initialization Error */
        while(1);
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
    clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
        /* Initialization Error */
        while(1);
    }
}
