/*
 * calc_frequency.h
 *
 * Created: 2018-04-04 10:54:25
 *  Author: Acer
 */ 

#ifndef CALC_FREQUENCY_H_
#define CALC_FREQUENCY_H_

#include <inttypes.h>

void calc_init(int16_t filterPoints, int16_t milliVoltOffset);
double calc_frequency(int16_t values[], int16_t nbrOfSamples, double Fs);

int16_t getSign(int16_t data);

#endif /* CALC_FREQUENCY_H_ */