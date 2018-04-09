/*
 * configure_tc.c
 *
 * Created: 2018-04-01 17:07:11
 *  Author: Daniel
 */ 

#include "configure_tc.h"
#include <asf.h>

int configureDone = 0; // define and initialize external variable
                       // initialization goes only with definition
					   // Only one source file may define the external variable, and definition is done only ONCE

void configure_tc(void)
{
	/* Configure PMC */
	pmc_enable_periph_clk(ID_TC0);
	/* Configure TC for a 500 kHz frequency and trigger on RC compare. */
	tc_init(TC0, 0, 0 | TC_CMR_CPCTRG);			//Timer_clock_1 - MCK/2 - 42 MHz (internal clock signal)
	tc_write_rc(TC0, 0, 84);					//84 corresponds to fs = 500 kHz (42 MHz/84 = 500 kHz)

	/* Configure and enable interrupt on RC compare:
	 * A trigger resets the counter and starts the counter clock. RC Compare Trigger is implemented 
	 * in each channel and can provide a trigger when the counter value matches the RC value.
	 */
	NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	tc_enable_interrupt(TC0, 0, TC_IER_CPCS); //CPCS is 5th bit (nr 4) in  TC Interrupt Enable Register (TC_IER0, ch 0: 0x40080024)

	configureDone = 1;

}