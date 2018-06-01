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
extern uint32_t signal_arrival_time, start, stop;
#define CHECK_PIN PIO_PD0_IDX	//Ardiuno Due pin 25 used to measure work load

#endif /* TRIGGER_ON_AMPLITUDE_H_ */