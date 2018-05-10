/*
 * dacc_functions.c
 *
 * Created: 2018-05-10
 * Author: Jonas Eiselt
 *
 * See: http://asf.atmel.com/docs/latest/sam.drivers.dacc.sinewave_example.arduino_due_x/html/group__sam__drivers__dacc__group.html#ga8e08574684fec1ab40817495b0d403c9
 */ 

 #include <asf.h>
 #include "dacc_functions.h"
 
 void configure_dacc(void)
 {
	pmc_enable_periph_clk(ID_DACC);
	
	dacc_reset(DACC);
	dacc_set_transfer_mode(DACC, 0);
	dacc_set_timing(DACC, 1, 1, 0);			
	
	dacc_set_channel_selection(DACC, 0);	
	dacc_enable_channel(DACC, 0);		
 }
