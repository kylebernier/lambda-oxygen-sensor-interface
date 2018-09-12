#include "pwm.h"

void Init_PWM(void)
{
  /***********************************************/
  /* Configure the NVIC to handle TIM1 interrupt */
  /***********************************************/
  //NVIC_SetPriority(TIM1_IRQn, 0);
  //NVIC_EnableIRQ(TIM1_IRQn);
  
  /***************************/
  /* Time base configuration */
  /***************************/
  /* Set counter mode */
  /* Reset value is LL_TIM_COUNTERMODE_UP */
  //LL_TIM_SetCounterMode(TIM1, LL_TIM_COUNTERMODE_UP);
  
  /* Set the pre-scaler value to have TIM1 counter clock equal to 10 kHz */
  LL_TIM_SetPrescaler(TIM1, __LL_TIM_CALC_PSC(SystemCoreClock, 10000));
  
  /* Enable TIM1_ARR register preload. Writing to or reading from the         */
  /* auto-reload register accesses the preload register. The content of the   */
  /* preload register are transferred into the shadow register at each update */
  /* event (UEV).                                                             */  
  LL_TIM_EnableARRPreload(TIM1);
  
  /* Set the auto-reload value to have a counter frequency of 100 Hz */
  LL_TIM_SetAutoReload(TIM1, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM1), 100));
  
  /*********************************/
  /* Output waveform configuration */
  /*********************************/
  /* Set output mode */
  /* Reset value is LL_TIM_OCMODE_FROZEN */
  LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
  
  /* Set output channel polarity */
  /* Reset value is LL_TIM_OCPOLARITY_HIGH */
  //LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCPOLARITY_HIGH);
  
  /* Set compare value to half of the counter period (50% duty cycle ) */
  LL_TIM_OC_SetCompareCH2(TIM1, (LL_TIM_GetAutoReload(TIM1) / 2));
  
  /* Enable TIM1_CCR1 register preload. Read/Write operations access the      */
  /* preload register. TIM1_CCR1 preload value is loaded in the active        */
  /* at each update event.                                                    */
  LL_TIM_OC_EnablePreload(TIM1, LL_TIM_CHANNEL_CH2);
  
  /**************************/
  /* TIM1 interrupts set-up */
  /**************************/
  /* Enable the capture/compare interrupt for channel 1*/
  LL_TIM_EnableIT_CC1(TIM1);
  
  /**********************************/
  /* Start output signal generation */
  /**********************************/
  /* Enable output channel 1 */
  LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH2);
  
  /* Enable counter */
  LL_TIM_EnableCounter(TIM1);
  
  /* Force update generation */
  LL_TIM_GenerateEvent_UPDATE(TIM1);
}