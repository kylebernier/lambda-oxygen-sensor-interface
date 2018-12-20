/**
 * @file pwm.h
 * @author Kyle Bernier
 * @author Daeghan Elkin
 * @date 2018 September 9
 *
 * @brief Provides basic PWM functionality
 *
 */
#ifndef __PWM_H
#define __PWM_H

#include "hw_map.h"

/**
 * @brief Initialize PWM
 * 
 * Sets up the PWM peripheral. The PWM has a counter rate of 100Hz.
 * Because the PWM signal is used to control the sensor heater, it 
 * is initialized to a 0% duty cycle. The Timer for PWM is also used
 * to trigger ADC conversions so the Capture/Compare Channel 1 is set
 * accordingly.
 * 
 * @retval None
 */
void Init_PWM(void);

/**
 * @brief This function handles timer Compare/Capture 1 interrupt.
 * 
 * This handler simply turns on the LED on PA8.
 * 
 * @retval None
 */
void TimerCC1_Callback(void);

/**
 * @brief  This function handles timer Compare/Capture 2 interrupt.
 * 
 * This handler simply turns off the LED on PA8.
 * 
 * @retval None
 */
void TimerCC2_Callback(void);

#endif /* __PWM_H */
