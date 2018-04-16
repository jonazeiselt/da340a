/*
 * TimerCounter.h
 *
 * Created: 2017-04-27 16:49:47
 *  Author: Danial Mahmoud
 */ 

#ifndef TIMER_COUNTER_H_
#define TIMER_COUNTER_H_

#define TC_CV1            0x40084050U        /* address of hardware register TC Counter Value Register, channel 1 of TC1 */
#define TC1_CCR           0x40084040U        /* address of hardware register TC Channel Control register, channel 1 of TC1 */
#define TC_CMR1           0x40084044U        /* address of hardware register TC Channel Mode Register: Capture Mode, channel 1 of TC1 */

#define WAVE              15                 /* bit in TC_CMR that sets mode */
#define CLKEN             0                  /* bit in TC_CCR that enables clock */
#define CLKDIS            1                  /* bit in TC_CCR that disables clock */
#define SWTRG             2                  /* bit in TC_CCR that commands software trigger */

void configure_timerCounter(void);
uint32_t read_counter_value(void);

#endif /* TIMER_COUNTER_H_ */