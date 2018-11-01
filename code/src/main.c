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
#include "pwm.h"
#include "usart.h"
#include "spi.h"


#define CJ125_IDENT_REG         0x4800 // Identify request
#define CJ125_DIAG_REG          0x7800 // Diagnostic request
#define CJ125_DIAG_REG_OK       0x28ff // Diagnostic response CJ125 ready
#define CJ125_DIAG_REG_NOPWR    0x2855 // Diagnostic response no/low power
#define CJ125_DIAG_REG_NOSNSR   0x287F // Diagnostic response no sensor


void SystemClock_Config(void);


uint16_t aResultDMA[3];

/* Simple delay, will use systick at some point */
void delay(volatile unsigned delay)
{
    while (delay--);
}

int main(void)
{
    uint8_t i;
    uint16_t response = 0;

    // Initialize the GPIO pins
    HW_Init_GPIO();

    // Config the system clock to 8MHz
    SystemClock_Config();

    // Initialize peripherals
    Init_ADC(0xE0, (uint16_t *)aResultDMA, 3);
    Init_DAC();
    Init_PWM();
    Init_USART();
    Init_SPI();

    // Loop until CJ125 is ready. When CJ125 responds OK move on.
    while (response != CJ125_DIAG_REG_OK) {
        response = SPI_Transfer(CJ125_DIAG_REG);
        delay(2000);
    }

    // Enter CJ125 calibration mode
    //SPI_Transfer(CJ125_DIAG_REG);

    while(1) {
        DAC_SetValue(i);
        if (i > 2000000) i = 0;

        i += 1000;
    }
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follows :
 *            System Clock source            = PLL (MSI)
 *            SYSCLK(Hz)                     = 80000000
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
