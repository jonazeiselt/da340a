/*
* TimerCounter.c
*
* Created: 2017-04-26 16:46:56
*  Author: Danial Mahmoud
*/

#include <inttypes.h>
#include <asf.h>
#include "timer_counter.h"

/* Declaration and initialization of pointers to access hardware */
uint32_t *const p_TC_CV1 = (uint32_t *) TC_CV1;
uint32_t *const p_TC_CMR1 = (uint32_t *) TC_CMR1;
uint32_t *const p_TC1_CCR = (uint32_t *) TC1_CCR;

static void enable_channel_clock(void);
static void select_clock(void);
static void start_clock(void);

uint32_t read_counter_value(){
	uint32_t counterValue = *p_TC_CV1;
	return counterValue;
}

static void enable_channel_clock(void){
	*p_TC1_CCR &= ~(1 << CLKDIS); // clear disable bit
	*p_TC1_CCR |= (1 << CLKEN);   // set enable bit
}

/* Capture mode allows the TC channel to perform signal measurements */
/* Capture Mode is entered by clearing the WAVE bit in the TC_CMR */
static void select_capture_mode(void){
	*p_TC_CMR1 &= ~(1 << WAVE);
}

/* Set TCCLKS bits in TC_CMR (clock selected MCK/2 clock signal (from PMC)) */
static void select_clock(void){
	*p_TC_CMR1 &= 0x11111110;
}

/* A software trigger is performed: the counter is reset and the clock is started */
static void start_clock(void){
	*p_TC1_CCR |= (1 << SWTRG);
}

void configure_timerCounter(void)
{
	/* Configure power management of timer clocks (ID_TC4 = channel 1 of TC1) */
	pmc_enable_periph_clk(ID_TC4);
	//tc_init(TC1, 1, 0 | TC_CMR_CPCTRG);
	//tc_start(TC1, 1);
	
	/* Configure TC for a MCK/2 (i.e. 42 MHz) frequency */
	select_capture_mode();
	select_clock();
	enable_channel_clock();
	start_clock();
}

