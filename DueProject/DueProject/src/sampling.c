/*
 * sampling.c
 *
 * Created: 2018-04-03 11:46:58
 *  Author: Daniel
 */ 

#include <inttypes.h>
#include <asf.h>
#include "sampling.h"

#define ADC_MR               0x400C0004  /* ADC Mode Register */
#define SLEEP_BIT            6
#define WPEN                 0
#define ADC_WPMR             0x400C00E4  /* ADC Write Protect Mode Register */
#define WPKEY_ADC            0x414443

/* Pointers to access hardware registers */
uint32_t *const p_ADC_MR = (uint32_t*) ADC_MR;
uint32_t *const p_ADC_WPMR = (uint32_t*) ADC_WPMR;

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;

	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);			//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	adc_start(ADC);
	
}

/*
//Only sample values above lower threshold value in Comparison Window, else enter Sleep Mode. 
//How do we detect amplitude level of input signal without ADC?
static uint32_t check_threshold(){
	//Disable write protection
	*p_ADC_WPMR = 0;
	*p_ADC_WPMR = WPKEY_ADC;
	*p_ADC_WPMR &= ~(1 << WPEN);
	return 0;
}
*/