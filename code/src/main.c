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

#include "hw_map.h"
#include "adc.h"
#include "dac.h"
#include "spi.h"


void SystemClock_Config(void);


uint16_t aResultDMA[3];

uint8_t tx[5] = "Hello";
uint8_t rx[5];


/* Simple delay, will use systick at some point */
void delay(volatile unsigned delay)
{
    while (delay--);
}

int main(void)
{
    uint16_t i = 0;

    // Initialize the GPIO pins
    HW_Init_GPIO();

    // Config the system clock to 80MHz
    SystemClock_Config();

    // Initialize the ADC with channels 5, 6, and 7
    Init_ADC(0xE0, (uint16_t *)aResultDMA, 3);

    Init_DAC();

    Init_SPI((uint8_t *)tx, (uint8_t *)rx, 5);

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

        DAC_SetValue(i);

        i+=1;

        if (i > 0xFFF) i = 0;

        SPI_Transfer(tx, rx, 5, 0);
    }
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follows :
 *            System Clock source            = PLL (MSI)
 *            SYSCLK(Hz)                     = 80000000
 *            HCLK(Hz)                       = 80000000
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
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_MSI, LL_RCC_PLLM_DIV_1, 40, LL_RCC_PLLR_DIV_2);
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
