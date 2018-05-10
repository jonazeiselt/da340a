/*
 * adc_functions.h
 *
 * Created: 2018-04-01
 * Author: Danial
 */ 

#ifndef ADC_FUNCTIONS_H_
#define ADC_FUNCTIONS_H_

#define ADC_CLOCK        6400000 
#define TRACKING_TIME    0
#define SETTLING_TIME    ADC_SETTLING_TIME_3
#define TRANSFER_TIME    0
#define ADC_BUFFER_SIZE  3260
#define sampel_frequency 500000

int16_t adc_values[ADC_BUFFER_SIZE]; 
extern int16_t adc_finished;

void configure_adc(void);
uint32_t adc_read_buffer(int16_t *p_s_buffer);

#endif /* ADC_FUNCTIONS_H_ */