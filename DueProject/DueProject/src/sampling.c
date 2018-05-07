/*
* sampling.c
*
* Created: 2018-04-03 11:46:58
*  Author: Daniel
*/

#include <inttypes.h>
#include <asf.h>
#include <string.h>
#include <float.h>
#include <stdio.h>
#include "sampling.h"
#include "amplitude_trigger.h"
#include "dec_string.h"
#include "tdoa.h"

uint32_t rising_edges = 0;
uint32_t top_to_low = 0;


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

void pin_high_pulse_handler(const uint32_t id, const uint32_t index)
{
	static uint32_t frequency = 0;
	static double beacon_1_time, beacon_2_time, beacon_3_time, beacon_4_time;
	if ((id == ID_PIOA) && (index == PIO_PA14)){
		if (pio_get(PIOA, PIO_TYPE_PIO_INPUT, PIO_PA14))
		{
			if (rising_edges < CYCLE_INTERVAL)
			{
				tc_values[rising_edges] = tc_read_cv(TC1, 1);
				rising_edges++;
			}
			else
			{
				pio_disable_interrupt(PIOA, PIO_PA14);
				top_to_low = tc_values[CYCLE_INTERVAL-1]-tc_values[0];
				frequency = 42000000/(top_to_low/(CYCLE_INTERVAL-1));
				//printf("Frequency: %lu Hz\n", frequency);
				rising_edges = 0;
				if ((frequency >= 38500) && (frequency <= 41500))
				{
					switch(beaconCounter){
						case 0:
						beacon_1_time = signal_arrival_time; //threshold voltage value reacts after 7th period
						break;
						case 1:
						beacon_2_time = signal_arrival_time;
						break;
						case 2:
						beacon_3_time = signal_arrival_time;
						break;
						case 3:
						beacon_4_time = signal_arrival_time;
						uint32_t start = tc_read_cv(TC2, 2);
						double b1_in_sec = (float)beacon_1_time*((float)1/42000000)-0.0002; //remove certain periods to get real TDOA values
						double b2_in_sec = (float)beacon_2_time*((float)1/42000000)-0.000375;
						double b3_in_sec = (float)beacon_3_time*((float)1/42000000)-0.0002;
						double b4_in_sec = (float)beacon_4_time*((float)1/42000000)-0.000225;
						printf("B2-B1: %s ms\n", get_decimal_string((b2_in_sec-b1_in_sec)*1000));
						printf("B3-B2: %s ms\n", get_decimal_string((b3_in_sec-b2_in_sec)*1000));
						printf("B4-B3: %s ms\n", get_decimal_string((b4_in_sec-b3_in_sec)*1000));
						set_tdoa(b1_in_sec, b2_in_sec-0.02, b3_in_sec-0.04, b4_in_sec-0.06);
						double x = 0;
						double y = 0;
						double z = 0;
						calculate_position(&x, &y, &z);
						printf("x-coord: %s \n", get_decimal_string(x));
						printf("y-coord: %s \n", get_decimal_string(y));
						printf("z-coord: %s \n", get_decimal_string(z));
						printf("-----------------------------------------\n"); 		
						uint32_t stop = tc_read_cv(TC2, 2);
						uint32_t result = stop - start;
						printf("Time it takes: %s ms\n", get_decimal_string((float)result*((float)1/42000000)*1000));	
						break;
					}
				}
				pio_enable_interrupt(PIOB, PIO_PB26);
				
			}
			
		}
	}
}


void init_pulse_pin(void)
{
	pmc_enable_periph_clk(ID_PIOA);
	pio_set_input(PIOA, PIO_PA14, PIO_PULLUP); // PA14 = pin 23
	pio_pull_up(PIOA, PIO_PA14, 0); //enable pull-down, when no input then input state is low
	pio_handler_set(PIOA, ID_PIOA, PIO_PA14, PIO_IT_EDGE, pin_high_pulse_handler);
	pio_disable_interrupt(PIOA, PIO_PA14);
	NVIC_EnableIRQ(PIOA_IRQn);
}

void TC1_init(void)
{
	/* Configure power management of timer clocks (ID_TC4 = channel 1 of TC1) */
	pmc_enable_periph_clk(ID_TC4);
	tc_init(TC1, 1, 0 | TC_CMR_CPCTRG);
	tc_start(TC1, 1);
}

