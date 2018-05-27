#include "stm32l4xx.h"

void delay(volatile unsigned dly)
{
    while (dly--);
}

int main()
{
	// Enable GPIOB and GPIOE
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN 
		+ RCC_AHB2ENR_GPIOEEN;

	// Set GPIOB_2 and GPIOE_8 as outputs
	GPIOB->MODER |= GPIO_MODER_MODE2_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE2_1;
	GPIOE->MODER |= GPIO_MODER_MODE8_0;
	GPIOE->MODER &= ~GPIO_MODER_MODE8_1;

	// Alternate blinking of two leds
	while (1) {
		// Turn on read led
		GPIOB->ODR |= GPIO_ODR_OD2;
		// Turn off green led
		GPIOE->ODR &= ~GPIO_ODR_OD8;
		
		// Delay
		delay(200000);
		
		// Turn off red led
		GPIOB->ODR &= ~GPIO_ODR_OD2;
		// Turn on green led
		GPIOE->ODR |= GPIO_ODR_OD8;

		// Delay
		delay(200000);
	}
}

