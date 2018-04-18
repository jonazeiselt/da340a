/*
 * sampling.h
 *
 * Created: 2018-04-03 11:48:15
 *  Author: Daniel
 */ 


#ifndef SAMPLING_H_
#define SAMPLING_H_

extern uint32_t edges;

void pin_pulse_handler(const uint32_t id, const uint32_t index);
void init_pulse_pin(void);
void TC1_init(void);


#endif /* SAMPLING_H_ */