/*
 * adc_with_pdc.h
 *
 * Created: 2018-04-01 17:05:15
 *  Author: Daniel
 */ 

#include <asf.h>
#include "adc.h"

#ifndef ADC_WITH_PDC_H_
#define ADC_WITH_PDC_H_

#define ADC_CLOCK        6400000 // ADC clock frequency in Hz, max frequency is 20 MHz
#define TRACKING_TIME    0
#define SETTLING_TIME    ADC_SETTLING_TIME_3
#define TRANSFER_TIME    0
#define ADC_BUFFER_SIZE  3260
#define sampel_frequency 500000

int16_t adc_buffer_sample_values[ADC_BUFFER_SIZE]; //the array will act as buffer, it contains ADC sample values

void adc_setup(void);

#endif /* ADC_WITH_PDC_H_ */