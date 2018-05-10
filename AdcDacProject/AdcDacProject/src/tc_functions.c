 /*
  * configure_tc.c
  *
  * Created: 2018-04-01
  * Author: Danial and Jonas
  */

 #include <asf.h>
 #include "tc_functions.h"
 #include "dacc_functions.h"

 int16_t dacc_finished;
 int16_t dacc_index;

 /*
  * Configure and enable interrupt for TC0 with a 500 kHz frequency
  * TC0 = MCK / 2 <-> 84 MHz / 2 = 42 MHz
  * Fs = 0.5 MHz, TC0 = 42 MHz -> 42 MHz / 0.5 MHz = 84
  */
 void configure_tc(void)
 {
	 // Configure TC0
	 pmc_enable_periph_clk(ID_TC0);
	 
	 tc_init(TC0, 0, 0 | TC_CMR_CPCTRG);
	 tc_write_rc(TC0, 0, 84);

	 NVIC_EnableIRQ((IRQn_Type) ID_TC0);
	 tc_enable_interrupt(TC0, 0, TC_IER_CPCS);
	 
	 // Configure TC1
	 pmc_enable_periph_clk(ID_TC4);
	 
	 tc_init(TC1, 1, 0 | TC_CMR_CPCTRG);
	 tc_write_rc(TC1, 1, 84);

	 NVIC_EnableIRQ((IRQn_Type) ID_TC4);
	 tc_enable_interrupt(TC1, 1, TC_IER_CPCS);
 }

 /*
  * Interrupt handler for TC0 interrupt. Takes one single sample
  */
 void TC0_Handler(void)
 {
	 volatile uint32_t ul_dummy;
	 ul_dummy = tc_get_status(TC0, 0);

	 /* Avoid compiler warning */
	 UNUSED(ul_dummy);
	 
	 adc_start(ADC);
 }

 /*
  * Interrupt handler for TC1 interrupt
  */
 void TC4_Handler(void)
 {
	 volatile uint32_t ul_dummy;
	 ul_dummy = tc_get_status(TC1, 1);

	 /* Avoid compiler warning */
	 UNUSED(ul_dummy);
	 
	 dacc_write_conversion_data(DACC, dacc_values[dacc_index]);
	 dacc_index++;

	 if (dacc_index >= DACC_BUFFER_SIZE)
	 {
	 	dacc_index = 0;
		dacc_finished = 1;
	 }
 }