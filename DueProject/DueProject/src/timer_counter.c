/*
 * timer_counter.c
 *
 * Created: 2018-04-09 16:34:22
 *  Author: Daniel
 */ 

#include <inttypes.h> 
#include <asf.h>
#include "timer_counter.h"

/* Declaration and initialization of pointers to access hardware */
uint32_t *const p_PMC_PCSR0 = (uint32_t *) PMC_PCSR0; 
uint32_t *const p_PMC_PCER0 = (uint32_t *) PMC_PCER0;
uint32_t *const p_PMC_WPMR = (uint32_t *) PMC_WPMR;
uint32_t *const p_TC_CMR1 = (uint32_t *) TC_CMR1;
uint32_t *const p_TC1_CCR = (uint32_t *) TC1_CCR;
uint32_t *const p_TC1_WPMR = (uint32_t *) TC1_WPMR;
uint32_t *const p_TC1_CV = (uint32_t *) TC1_CV;
uint32_t *const p_TC_SR1 = (uint32_t *) TC_SR1;

uint32_t counterValue = 0;

static uint32_t disable_write_protect(uint32_t key);
static void enable_periph_clk(uint32_t periph_id);
static void enable_clock_TC1CH1(void);
static void select_clock(void);


/* Disable Write Protect on the PMC hardware registers in use by clearing WPEN bit */
static uint32_t disable_write_protect(uint32_t key){
	if(key == WPKEY_WPMR_PMC)
	{
		*p_PMC_WPMR &= 0;               // clear entire register just to be safe
		*p_PMC_WPMR |= WPKEY_WPMR_PMC;  // first write WPKEY = 0x504D43 to register
		*p_PMC_WPMR &= 0x11111100;      // then clear WPEN bit, mask upper bytes
		return 0;
	}
	else if (key == WPKEY_WPMR_TC)
	{
		enable_clock_TC1CH1();    /* in order to access TC_WPMR, the Timer Counter clock of the first channel must be enabled */	
		*p_TC1_WPMR &= 0;
		*p_TC1_WPMR |= WPKEY_WPMR_TC;
		*p_TC1_WPMR &= 0x11111100; // disable Write Protect by clearing WPEN bit, mask upper bytes
		return 0;
	}
	return 1;
}


static void enable_periph_clk(uint32_t periph_id){
	//disable_write_protect(WPKEY_WPMR_PMC);
	if(periph_id == PERIPH_ID_TCC1)
	{
		if((*p_PMC_PCSR0 & (1<<PERIPH_ID_TCC1)) != (1<<PERIPH_ID_TCC1)){  /* check status of peripheral clock corresponding to Timer Counter Channel 0 (if enabled) */
			*p_PMC_PCER0 = (1 << PERIPH_ID_TCC1);                         /* enable peripheral clock corresponding to Timer Counter Channel 0 */
		}
	}
}

static void enable_clock_TC1CH1(void){
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

/* The start and stop commands are effective only if the clock is enabled */
/* A trigger resets the counter and starts the counter clock */
/* Each channel has a software trigger, available by setting SWTRG in TC_CCR */
/* A software trigger is performed: the counter is reset and the clock is started */
static void start_clock(void){
	*p_TC1_CCR |= (1 << SWTRG); 
}

/* The current value of the counter is accessible in real time by reading the TC Counter Value Register (TC_CV) */
uint32_t read_counter_value(void){
	/* if COVFS is equal to 1 an overflow has occurred 	
	if((*p_TC_SR0 & (1 << COVFS)) == (1 << COVFS)){ // check if overflow has occurred
		start_clock(); // resets the counter and starts the counter clock anew
		*p_TC_CV = 0;
	}
	*/
	counterValue = *p_TC1_CV;
	return counterValue;
}

void TC1CH1_setup_and_kickoff(void){
	disable_write_protect(WPKEY_WPMR_PMC);
	disable_write_protect(WPKEY_WPMR_TC);
	enable_periph_clk(PERIPH_ID_TCC1);
	select_capture_mode();
	select_clock();
	enable_clock_TC1CH1();
	start_clock();
}