/**
 * @file pwm.c
 * @author Kyle Bernier 
 * @author Daeghan Elkin
 * @date 2018 September 9
 *
 * @brief Provides basic PWM functionality
 *
 */
#include "pwm.h"

/**
 * @brief Current state of the PWM signal; 1: high, 0: low.
 * 
 * Value is set during PWM interrupts.
 */
uint8_t pwm_state = 0;

/* Initialize PWM */
void Init_PWM(void)
{
    // Enable PWM interrupts
    NVIC_SetPriority(PWMx_IRQ, 2);
    NVIC_EnableIRQ(PWMx_IRQ);

    // Set the pre-scaler value to 10 kHz 
    LL_TIM_SetPrescaler(PWMx_BASE, __LL_TIM_CALC_PSC(SystemCoreClock, 10000));
  
    // Set the auto-reload value to have a counter frequency of 100 Hz 
    LL_TIM_SetAutoReload(PWMx_BASE, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(PWMx_BASE), 100));
  
    // Set output mode 
    LL_TIM_OC_SetMode(PWMx_BASE, PWMx_CHANNEL, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetMode(PWMx_BASE, PWMx_IRQ_CHANNEL, LL_TIM_OCMODE_PWM1);
  
    // Set compare value have a 0% duty cycle
    LL_TIM_OC_SetCompareCH2(PWMx_BASE, 0);
    LL_TIM_OC_SetCompareCH1(PWMx_BASE, 0);
  
    // Enable PWM register preload. 
    LL_TIM_OC_EnablePreload(PWMx_BASE, PWMx_CHANNEL);
    LL_TIM_OC_EnablePreload(PWMx_BASE, PWMx_IRQ_CHANNEL);
  
    // Enable output channel 
    LL_TIM_CC_EnableChannel(PWMx_BASE, PWMx_CHANNEL);
    LL_TIM_CC_EnableChannel(PWMx_BASE, PWMx_IRQ_CHANNEL);

    // Enable outputs 
    LL_TIM_EnableAllOutputs(PWMx_BASE);

    // Enable the interrupts
    LL_TIM_EnableIT_CC1(PWMx_BASE);
    LL_TIM_EnableIT_CC2(PWMx_BASE);
  
    // Enable counter 
    LL_TIM_EnableCounter(PWMx_BASE);
  
    // Force update generation 
    LL_TIM_GenerateEvent_UPDATE(PWMx_BASE);
}

/* Callback for Compare/Capture 1 Interrupt */
void TimerCC1_Callback(void) {
    SET_BIT(GPIOA->ODR, GPIO_ODR_OD8_Msk);
    pwm_state = 1;
}

/* Callback for Compare/Capture 2 Interrupt */
void TimerCC2_Callback(void) {
    CLEAR_BIT(GPIOA->ODR, GPIO_ODR_OD8_Msk);
    pwm_state = 0;
}

/* Returns the current state of the PWM signal */
uint8_t PWM_GetState(void) {
    return pwm_state;
}
