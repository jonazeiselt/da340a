/*
 * real_time_timer.h
 *
 * Created: 2018-04-09 15:50:06
 *  Author: Daniel
 */ 

#include <inttypes.h>

#ifndef REAL_TIME_TIMER_H_
#define REAL_TIME_TIMER_H_

/* The Power Management Controller has no effect on RTT behavior since it is continuously fed by SLCK (Slow Clock) */
#define RTT_MR          0x400E1A30U     /* address of hardware register Real-time Timer Mode Register */
#define RTT_VR          0x400E1A38U     /* address of hardware register Real-time Timer Value Register */
#define RTPRES          0x00008000U     /* defines the number of SLCK periods required to increment RTT */

extern uint32_t realTimeValue;

uint32_t get_current_value(void);
void start_RTT(void);

#endif /* REAL_TIME_TIMER_H_ */