/*
 * timer_counter.h
 *
 * Created: 2018-04-09 16:34:36
 *  Author: Daniel
 */ 


#ifndef TIMER_COUNTER_H_
#define TIMER_COUNTER_H_

#define PERIPH_ID_TCC1    28                 /* Peripheral ID of Timer Counter Channel 1 */
#define PMC_PCSR0         0x400E0618U        /* address of hardware register Peripheral Clock Status Register 0 of PMC */
#define PMC_PCER0         0x400E0610U        /* address of hardware register Peripheral Clock Enable Register 0 of PMC */
#define PMC_WPMR          0x400E06E4U        /* address of hardware register Writer Protect Mode Register of PMC */
#define TC_CMR1           0x40084044U        /* address of hardware register TC Channel Mode Register: Capture Mode, channel 1 of TC1 */
#define TC1_WPMR          0x400840E4U        /* address of hardware register TC Write Protection Mode Register, TC1 */
#define TC1_CCR           0x40084040U        /* address of hardware register TC Channel Control register, channel 1 of TC1 */
#define TC1_CV            0x40084050U        /* address of hardware register TC Counter Value Register, channel 1 of TC1 */
#define TC_SR1            0x40084060U        /* address of hardware register TC Status Register, channel 1 of TC1 */
#define WPKEY_WPMR_PMC    (uint32_t)0x504D43
#define WPKEY_WPMR_TC     (uint32_t)0x54494D
#define WAVE              15                 /* bit in TC_CMR that sets mode */
#define CLKEN             0                  /* bit in TC_CCR that enables clock */
#define CLKDIS            1                  /* bit in TC_CCR that disables clock */
#define SWTRG             2                  /* bit in TC_CCR that commands software trigger */
#define COVFS             0                  /* bit in TC_SR, short for Counter Overflow status */

extern uint32_t counterValue;

uint32_t read_counter_value(void);
void TC1CH1_setup_and_kickoff(void);


#endif /* TIMER_COUNTER_H_ */