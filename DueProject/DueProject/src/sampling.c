/*
 * sampling.c
 *
 * Created: 2018-04-03 11:46:58
 *  Author: Daniel
 */ 

#include <inttypes.h>
#include <asf.h>
#include "sampling.h"

/**
 *  Interrupt handler for TC0 interrupt.
 */
void TC0_Handler(void)
{
	volatile uint32_t ul_dummy;

	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);	//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	/* Start sampling (i.e. convert one sample value) */
	adc_start(ADC);
	
}

