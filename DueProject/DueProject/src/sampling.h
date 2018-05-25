/*
 * sampling.h
 *
 * Created: 2018-04-03 11:48:15
 *  Author: Daniel
 */ 


#ifndef SAMPLING_H_
#define SAMPLING_H_

#define CYCLE_INTERVAL  11

extern int rising_edges;
extern uint32_t top_to_low;
uint32_t tc_values[CYCLE_INTERVAL];
uint32_t buffer_of_cycles[1000];

void pin_high_pulse_handler(const uint32_t id, const uint32_t index);
void init_pulse_pin(void);
void TC1_init(void);

#endif /* SAMPLING_H_ */