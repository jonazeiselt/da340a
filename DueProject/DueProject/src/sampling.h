/*
 * sampling.h
 *
 * Created: 2018-04-03 11:48:15
 *  Author: Daniel
 */ 


#ifndef SAMPLING_H_
#define SAMPLING_H_

#define CYCLE_INTERVAL  11

extern uint32_t rising_edges;
extern uint32_t top_to_low;
uint32_t tc_values[CYCLE_INTERVAL];
//declaration of structure
struct ultrasoundPulse
{
	double signal1, signal2, signal3;
};

void pin_high_pulse_handler(const uint32_t id, const uint32_t index);
void init_pulse_pin(void);
void TC1_init(void);
//void determine_tdoa(double b1, double b2, double b3);

#endif /* SAMPLING_H_ */