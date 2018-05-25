/*
* trigger_on_amplitude.c
*
* Created: 2018-04-09 09:56:25
*  Author: Daniel
*/

#include <asf.h>
#include <inttypes.h>
#include <string.h>
#include <pio.h>
#include "configure_tc.h"
#include "amplitude_trigger.h"
#include "dec_string.h"

uint32_t signal_arrival_time, beaconCounter = 0;
uint32_t previous_signal_time = 0;

void pin_edge_handler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOB) && (index == PIO_PB26)){
		if (pio_get(PIOB, PIO_TYPE_PIO_INPUT, PIO_PB26)){
			//puts("Amplitude level detected");
			signal_arrival_time = tc_read_cv(TC1, 1);
			pio_enable_interrupt(PIOA, PIO_PA14); //estimate frequency
			pio_disable_interrupt(PIOB, PIO_PB26);
		}
		else{
			//puts("------------No edge detected------------");
		}
	}
	
}


void init_amplitude_trigger(void){
	pmc_enable_periph_clk(ID_PIOB);
	pio_set_input(PIOB, PIO_PB26, PIO_PULLUP);
	pio_pull_up(PIOB, PIO_PB26, 0); //enable pull-down, when no input then input state is low
	pio_handler_set(PIOB, ID_PIOB, PIO_PB26, PIO_IT_EDGE, pin_edge_handler);
	pio_enable_interrupt(PIOB, PIO_PB26);
	NVIC_EnableIRQ(PIOB_IRQn);
	/*
	// Configure timer 2 for TDOA
	pmc_enable_periph_clk(ID_TC8);
	// TC2, ch2 is for TDOA 
	tc_init(TC2, 2, 0 | TC_CMR_CPCTRG);
	tc_start(TC2, 2);*/
}
