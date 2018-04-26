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
//#include "tdoa_2d.h"
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
/*
void determine_tdoa(double b1, double b2, double b3)
{
	puts("Calculating TDOA");
	//double time_diff_between_beacon2_and_beacon1 = (double) (b2-b1)/42000000;
	//double time_diff_between_beacon3_and_beacon1 = (double) (b3-b1)/42000000;
	printf("TDOA 2-1: %s\n", get_decimal_string(time_diff_between_beacon2_and_beacon1));
	printf("TDOA 3-1: %s\n", get_decimal_string(time_diff_between_beacon3_and_beacon1));
	//duration of ultrasound waves must be shorter than TDOA to prevent overlap of signals
	//calculate_position(time_diff_between_beacon2_and_beacon1, time_diff_between_beacon3_and_beacon1);
	
	if ((ulPulse.signal1 < t21) && (ulPulse.signal2 < (t31-t21)))
	{
		calculate_position(t21, t31);
	}
	else
	{
		puts("The ultrasound signals overlap!");
	}
	
}
*/
void pin_high_pulse_handler(const uint32_t id, const uint32_t index)
{
	static uint32_t frequency = 0;
	static float period = 0;
	static double beacon_1_time, beacon_2_time, beacon_3_time, beacon_4_time;
	static int flag1, flag2, flag3, flag4 = 0;
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
				//period = (long double) 1/frequency;
				if ((flag1 == 0) && ((frequency >= 38500) && (frequency <= 42000)))
				{
					flag1 = 1; // we will not register anymore frequencies from beacon 1
					//ulPulse.signal1 = period*(CYCLE_INTERVAL-1);
					beacon_1_time = (double)signal_arrival_time;
					printf("Frequency - beacon 1: %lu Hz\n", frequency);
					//printf("Period - beacon 1: %s sec\n", get_decimal_string(period));
					//printf("Signal length - beacon 1: %s sec\n", get_decimal_string(ulPulse.signal1));
				}
				else if ((flag2 == 0) && ((frequency >= 42500) && (frequency <= 48500)))
				{
					flag2 = 1;
					//ulPulse.signal2 = period*(CYCLE_INTERVAL-1);
					beacon_2_time = (double)signal_arrival_time;
					printf("Frequency - beacon 2: %lu Hz\n", frequency);
					//printf("Period - beacon 2: %s sec\n", get_decimal_string(period));
					//printf("Signal length - beacon 2: %s sec\n", get_decimal_string(ulPulse.signal2));
				}
				else if ((flag3 == 0) && ((frequency >= 51000) && (frequency <= 55000)))
				{
					flag3 = 1;
					//ulPulse.signal3 = period*(CYCLE_INTERVAL-1);
					beacon_3_time = (double)signal_arrival_time;
					printf("Frequency - beacon 3: %lu Hz\n", frequency);
					//printf("Period - beacon 3: %s sec\n", get_decimal_string(period));
					//printf("Signal length - beacon 3: %s sec\n", get_decimal_string(ulPulse.signal3));
				}
				else if ((flag4 == 0) && ((frequency >= 56000) && (frequency <= 59000)))
				{
					flag4 = 1;
					//ulPulse.signal3 = period*(CYCLE_INTERVAL-1);
					beacon_4_time = (double)signal_arrival_time;
					printf("Frequency - beacon 4: %lu Hz\n", frequency);
					//printf("Period - beacon 3: %s sec\n", get_decimal_string(period));
					//printf("Signal length - beacon 3: %s sec\n", get_decimal_string(ulPulse.signal3));
				}
				
				if (flag1 && flag2 && flag3 & flag4)
				{
					//puts("All three frequencies found");
					//determine_tdoa(beacon_1_time, beacon_2_time, beacon_3_time, beacon_4_time); //pass struct by value?
					double b1_in_sec = (float)beacon_1_time*((float)1/42000000);
					double b2_in_sec = (float)beacon_2_time*((float)1/42000000);
					double b3_in_sec = (float)beacon_3_time*((float)1/42000000);
					double b4_in_sec = (float)beacon_4_time*((float)1/42000000);
					printf("Beacon 1 signal: %s\n", get_decimal_string(b1_in_sec));
					printf("Beacon 2 signal: %s\n", get_decimal_string(b2_in_sec));
					printf("Beacon 3 signal: %s\n", get_decimal_string(b3_in_sec));
					printf("Beacon 4 signal: %s\n", get_decimal_string(b4_in_sec));
					set_tdoa(b1_in_sec, b2_in_sec, b3_in_sec, b4_in_sec);
					flag1 = 0;
					flag2 = 0;
					flag3 = 0;
					flag4 = 0; //register new frequencies
					double x = 0;
					double y = 0;
					double z = 0;
					calculate_position(&x, &y, &z);
					printf("x-coord: %s \n", get_decimal_string(x));
					printf("y-coord: %s \n", get_decimal_string(y));
					printf("z-coord: %s \n", get_decimal_string(z));
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

