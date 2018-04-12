/*
 * adc_functions.h
 *
 * Created: 2018-04-02
 *  Author: Acer
 */ 

#ifndef ADC_FUNCTIONS_H_
#define ADC_FUNCTIONS_H_

#include <inttypes.h>

#define ADC_BASE_ADDRESS 0x400C0000U
#define ADC_CLOCK 6400000

void configure_adc(int adc_channel);
uint32_t adc_get_value(void);

#endif /* ADC_FUNCTIONS_H_ */