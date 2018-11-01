/**
 * @file pwm.c
 * @author Kyle Bernier and Daeghan Elkin
 * @date 2018 September 9
 *
 * @brief Provides basic PWM functionality
 *
 */
#include "pwm.h"

/* Initialize PWM */
void Init_PWM(void)
{
    // Set the pre-scaler value to 10 kHz 
    LL_TIM_SetPrescaler(PWMx_BASE, __LL_TIM_CALC_PSC(SystemCoreClock, 10000));
  
    // Set the auto-reload value to have a counter frequency of 100 Hz 
    LL_TIM_SetAutoReload(PWMx_BASE, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(PWMx_BASE), 100));
  
    // Set output mode 
    LL_TIM_OC_SetMode(PWMx_BASE, PWMx_CHANNEL, LL_TIM_OCMODE_PWM1);
  
    // Set compare value have a 0% duty cycle
    // If the Timer channel is changed, change this to match 
    LL_TIM_OC_SetCompareCH1(PWMx_BASE, 0);
  
    // Enable PWMx_BASE_CCR1 register preload. 
    LL_TIM_OC_EnablePreload(PWMx_BASE, PWMx_CHANNEL);
  
    // Enable output channel 
    LL_TIM_CC_EnableChannel(PWMx_BASE, PWMx_CHANNEL);

    // Enable outputs 
    LL_TIM_EnableAllOutputs(PWMx_BASE);

    // Enable the capture/compare interrupt for channel 
    LL_TIM_EnableIT_CC1(PWMx_BASE);
  
    // Enable counter 
    LL_TIM_EnableCounter(PWMx_BASE);
  
    // Force update generation 
    LL_TIM_GenerateEvent_UPDATE(PWMx_BASE);
}