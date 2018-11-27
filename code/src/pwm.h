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

#endif /* __PWM_H */
