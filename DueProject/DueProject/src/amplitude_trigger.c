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
#include "tdoa.h"

uint32_t signal_arrival_time, beaconCounter = 0;
uint32_t previous_signal_time = 0;
uint32_t start, stop = 0;
uint32_t arrayOfTDMAvalues[4];


void pin_edge_handler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOB) && (index == PIO_PB26)){
		if (pio_get(PIOB, PIO_TYPE_PIO_INPUT, PIO_PB26)){
			static int counter = 0;
			signal_arrival_time = tc_read_cv(TC1, 1);
			switch (counter)
			{
				case 0:
				arrayOfTDMAvalues[counter++] = signal_arrival_time;
				pio_disable_interrupt(PIOB, PIO_PB26);
				tc_write_rc(TC0, 0, 1050000); //25 ms
				tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
				tc_start(TC0, 0);
				break;
				case 1:
				arrayOfTDMAvalues[counter++] = signal_arrival_time;
				pio_disable_interrupt(PIOB, PIO_PB26);
				tc_write_rc(TC0, 0, 1050000);
				tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
				tc_start(TC0, 0);
				break;
				case 2:
				arrayOfTDMAvalues[counter++] = signal_arrival_time;
				pio_disable_interrupt(PIOB, PIO_PB26);
				tc_write_rc(TC0, 0, 1050000);
				tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
				tc_start(TC0, 0);
				break;
				case 3:
				arrayOfTDMAvalues[counter] = signal_arrival_time;
				pio_disable_interrupt(PIOB, PIO_PB26);
				float arrayOfTDOAvalues[4] = {(float)(arrayOfTDMAvalues[0])/42000000, (float) (arrayOfTDMAvalues[1])/42000000-0.03, 
				(float) (arrayOfTDMAvalues[2])/42000000-2*0.03, (float) (arrayOfTDMAvalues[3])/42000000-3*0.03};
				set_tdoa(arrayOfTDOAvalues[0], arrayOfTDOAvalues[1], arrayOfTDOAvalues[2], arrayOfTDOAvalues[3]);
				double x, y, z = 0;
				calculate_position(&x, &y, &z);
				printf("x, y, z: %s, %s, %s\n", get_decimal_string(x), get_decimal_string(y), get_decimal_string(z));
				tc_write_rc(TC0, 0, 2100000); //50ms
				tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
				tc_start(TC0, 0);
				tc_start(TC1, 1); //retrigger TC1
				counter = 0;
				break;
			}
			//puts("Amplitude level detected");
			/*
			ioport_set_pin_level(CHECK_PIN, HIGH);		//put test pin HIGH
			tc_start(TC1, 1);
			//signal_arrival_time = tc_read_cv(TC1, 1);
			start = tc_read_cv(TC1, 1);
			tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
			pio_disable_interrupt(PIOB, PIO_PB26);
			pio_enable_interrupt(PIOA, PIO_PA14); //estimate frequency
			tc_start(TC0, 0);
			*/
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
}
/*
void TC2_init(void)
{
// Configure timer 2 for TDOA
pmc_enable_periph_clk(ID_TC8);
// TC2, ch2 is for TDOA
tc_init(TC2, 2, 0 | TC_CMR_CPCTRG);
}*/
