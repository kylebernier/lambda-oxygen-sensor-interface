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
 * Sets up the PWM peripheral. The PWM has a pre-scalar of 10kHz and
 * a counter rate of 100Hz. Because the PWM signal is used to control the 
 * sensor heater, it is initialized to 0% duty cycle. 
 * 
 * @retval None
 */
void Init_PWM(void);

/**
* @brief  This function handles timer Compare/Capture 1 interrupt.

* @retval None
*/
void TimerCC1_Callback(void);

/**
* @brief  This function handles timer Compare/Capture 2 interrupt.

* @retval None
*/
void TimerCC2_Callback(void);

/**
 * @brief Returns the state of the PWM signal; 1-High, 0-Low.
 * 
 * @return uint8_t PWM state
 */
uint8_t PWM_GetState(void);

#endif /* __PWM_H */
