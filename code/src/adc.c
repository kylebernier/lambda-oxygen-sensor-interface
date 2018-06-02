#include "stm32l4xx.h"

static void Wakeup_ADC(void);

// Initializes the ADC to PA1
void Init_ADC(void)
{
	SET_BIT(GPIOA->ASCR, GPIO_ASCR_EN_1);

	// Enable ADC clock
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_ADCEN);
	
	// Disable ADC1
	CLEAR_BIT(ADC1->CR, ADC_CR_ADEN);
	
	// Enable I/O analog switches voltage booster
	SET_BIT(ADC123_COMMON->CCR, SYSCFG_CFGR1_BOOSTEN);
	
	// Enable conversion of internal channels
	SET_BIT(ADC123_COMMON->CCR, ADC_CCR_VREFEN);
	
	// ADC Prescaler
	SET_BIT(ADC123_COMMON->CCR, ADC_CCR_PRESC_0);
	
	// Set ADC clock mode as synchronous clock mode
	SET_BIT(ADC123_COMMON->CCR, ADC_CCR_CKMODE_0);
	
	// Configure all ADCs as independent
	CLEAR_BIT(ADC123_COMMON->CCR, ADC_CCR_DUAL);
	
	// Wake up ADC
	Wakeup_ADC();
	
	// Configure RES bits to set resolution as 12 bits
	CLEAR_BIT(ADC1->CFGR, ADC_CFGR_RES);
	
	// Select right alignment
	CLEAR_BIT(ADC1->CFGR, ADC_CFGR_ALIGN);
	
	// Select 1 conversion in regular channel conversion sequence
	CLEAR_BIT(ADC1->SQR1, ADC_SQR1_L);
	
	// Specify channel 6 as the 1st conversion in regular sequence
	SET_BIT(ADC1->SQR1, ADC_SQR1_SQ1_1);
	SET_BIT(ADC1->SQR1, ADC_SQR1_SQ1_2);
	
	// Configure channel 6 as single-ended
	SET_BIT(ADC1->DIFSEL, ADC_DIFSEL_DIFSEL);

	// Select ADC sample time
	// Must allow input voltage to charge embedded capacitor
	CLEAR_BIT(ADC1->SMPR1, ADC_SMPR1_SMP6);
	SET_BIT(ADC1->SMPR1, ADC_SMPR1_SMP6_0);
	SET_BIT(ADC1->SMPR1, ADC_SMPR1_SMP6_1);
	
	// Select ADC as discontinuous mode
	CLEAR_BIT(ADC1->CFGR, ADC_CFGR_CONT);
	
	// Select software trigger
	CLEAR_BIT(ADC1->CFGR, ADC_CFGR_EXTEN);
	
	// Enable ADC1
	SET_BIT(ADC1->CR, ADC_CR_ADEN);
	
	// Wait until ADC1 is ready
	while ((ADC1->ISR & (uint32_t) ADC_ISR_ADRDY) == 0);
	
	// Connects PA1 to ADC
	SET_BIT(GPIOA->ASCR, GPIO_ASCR_EN_1);
}

static void Wakeup_ADC(void)
{
	int wait_time;
	
	// To start ADC operations, the following sequence should be applied
	// DEEPPWD = 0: ADC not in deep-power down
	// DEEPPWD = 1: ADC in deep-power-down (default reset state)
	if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD)
		
	CLEAR_BIT(ADC1->CR , ADC_CR_DEEPPWD); // Exit deep power down mode if still in that state
	
	// Enable the ADC internal voltage regulator
	// Before performing any operation such as launching a calibration or enabling the ADC,
	// the ADC voltage regulator must first be enabled and the software must wait for the
	// regulator start-up time.
	SET_BIT(ADC1->CR, ADC_CR_ADVREGEN);
	
	// Wait for ADC voltage regulator start-up time
	// The software must wait for the startup time of the ADC voltage regulator
	// (T_ADCVREG_STUP, i.e. 20 us) before launching a calibration or enabling the ADC.
	wait_time = 20 * (80000000 / 1000000);
	
	while(wait_time != 0) {
		wait_time--;
	}
}

int Read_ADC(void) {
	// Start a ADC conversion
	SET_BIT(ADC1->CR, ADC_CR_ADSTART);
	// Wait for the conversion to complete
	while ((ADC123_COMMON->CSR & ADC_CSR_EOC_MST) == 0);
	// Return the ADC value
	return ADC1->DR;
}
