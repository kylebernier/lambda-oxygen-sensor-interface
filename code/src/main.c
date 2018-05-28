/**
 * @file main.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 May 27
 * 
 * @brief Blinks an led at the moment. Using macros to
 *        increase readability.
 *
 */

#include "stm32l4xx.h"

/* Simple delay, will use systick at some point */
void delay(volatile unsigned delay)
{
	while (delay--);
}

/* Main function */
int main(void)
{
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

