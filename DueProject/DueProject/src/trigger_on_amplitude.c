/*
* trigger_on_amplitude.c
*
* Created: 2018-04-09 09:56:25
*  Author: Daniel
*/

#include "configure_tc.h"
#include <asf.h>
#include <inttypes.h>
#include "trigger_on_amplitude.h"
#include <pio.h>


void pin_edge_handler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOB) && (index == PIO_PB26)){
		if (pio_get(PIOB, PIO_TYPE_PIO_INPUT, PIO_PB26)){
			puts("Amplitude level detected");
			if(configureDone == 1){ //access external variable, declaration has been done in the included header-file
				tc_start(TC0, 0); 
				pio_disable_interrupt(PIOB, PIO_PB26); //disable interrupt for now
				puts("Sampling has been started");
			}
			else{
				puts("Timer has not been configured!");
			}
		}else{
			puts("------------No edge detected------------");
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
}
