/*
 * trigger_on_amplitude.h
 *
 * Created: 2018-04-09 10:02:26
 *  Author: Daniel
 */ 


#ifndef TRIGGER_ON_AMPLITUDE_H_
#define TRIGGER_ON_AMPLITUDE_H_

void init_amplitude_trigger(void);
void pin_edge_handler(const uint32_t id, const uint32_t index);
extern uint32_t signal_arrival_time;

#endif /* TRIGGER_ON_AMPLITUDE_H_ */