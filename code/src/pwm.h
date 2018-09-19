/**
 * @file pwm.h
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 September 9
 *
 * @brief Provides basic PWM functionality
 *
 */
#ifndef __PWM_H
#define __PWM_H

#include "stm32l4xx_ll_tim.h"
#include "hw_map.h"

/* Initialize PWM */
void Init_PWM();

#endif /* __PWM_H */
