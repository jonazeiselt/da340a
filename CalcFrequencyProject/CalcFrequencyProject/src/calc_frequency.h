/*
 * calc_frequency.h
 *
 * Created: 2018-04-04 10:54:25
 *  Author: Acer
 */ 

#ifndef CALC_FREQUENCY_H_
#define CALC_FREQUENCY_H_

#include <inttypes.h>

void calc_init(int32_t hWindow, int32_t voltOffset);
double calc_frequency(int32_t values[], int32_t nbrOfSamples, double Fs);

int32_t getSign(int32_t data);

#endif /* CALC_FREQUENCY_H_ */