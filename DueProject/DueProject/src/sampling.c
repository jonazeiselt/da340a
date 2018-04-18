/*
* sampling.c
*
* Created: 2018-04-03 11:46:58
*  Author: Daniel
*/

#include <inttypes.h>
#include <asf.h>
#include <string.h>
#include "sampling.h"

uint32_t edges = 0;

/**
*  Interrupt handler for TC0 interrupt. Timer frequency corresponds to sample frequency.
*  Take one sample of input signal every time routine runs.
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

/* The interrupt is generated every once second. Since the input signal also passes through a comparator
 * a square wave is generated with the same frequency as the signal. We count the number of cycles per second
 * in order to determine frequency of input signal.
 */
void TC4_Handler(void){
	volatile uint32_t ul_dummy;
	static uint32_t frequency = 0;
	static float cycles = 0;

	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC1, 1);	//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	
	/* Calculate frequency of input signal */
	cycles = (float)edges*(2.47); // we count two edges on a single cycle (period), may require additional scaling because
	                              // other cycles (such as interrupt cycles; ISR latency) are involved which may give more 
								  // or less edges
	frequency = (uint32_t)cycles; // f = cycles per sec
	printf("Frequency: %lu Hz\n", frequency);
	edges = 0;
	
}

/* Once a rising edge is detected, the interrupt routine increments a counter. A period interrupt 
 * is generated after 1 second has elapsed (RC compare). 
 */
void pin_pulse_handler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOA) && (index == PIO_PA14)){
		/* Count each high edge */
		if(pio_get(PIOA, PIO_TYPE_PIO_INPUT, PIO_PA14)){
			edges++;
		}		
	}
	
}


void init_pulse_pin(void)
{
	pmc_enable_periph_clk(ID_PIOA);
	pio_set_input(PIOA, PIO_PA14, PIO_PULLUP); // PA14 = pin 23
	pio_pull_up(PIOA, PIO_PA14, 0); //enable pull-down, when no input then input state is low
	pio_handler_set(PIOA, ID_PIOA, PIO_PA14, PIO_IT_EDGE, pin_pulse_handler);
	pio_enable_interrupt(PIOA, PIO_PA14);
	NVIC_EnableIRQ(PIOA_IRQn);
}

void TC1_init(void)
{
	/* Configure power management of timer clocks (ID_TC4 = channel 1 of TC1) */
	pmc_enable_periph_clk(ID_TC4);
	tc_init(TC1, 1, 0 | TC_CMR_CPCTRG);
	tc_write_rc(TC1, 1, 42000000); // frequency = 42MHz/42000000 = 1 Hz = 1 sec
	NVIC_EnableIRQ((IRQn_Type) ID_TC4);
	tc_enable_interrupt(TC1, 1, TC_IER_CPCS);
	tc_start(TC1, 1);
}

