/*
* adc_functions.c
*
* Created: 2018-04-02
*  Author: Acer
*/

#include <asf.h>
#include "adc_functions.h"

uint32_t *const p_ADC_CR = (uint32_t*) ADC_BASE_ADDRESS;
uint32_t *const p_ADC_CDRx = (uint32_t*) (ADC_BASE_ADDRESS + 0x50U);
uint32_t *const p_ADC_CHER = (uint32_t*) (ADC_BASE_ADDRESS + 0x10U);

/*
* A0 = PA16 (AD7)
* http://asf.atmel.com/docs/latest/sam.drivers.adc.adc_example.arduino_due_x/html/sam_adc_quickstart.html
*/
void configure_adc(int adc_channel)
{
	/* Enable ADC clock */
	pmc_enable_periph_clk(ID_ADC);

	adc_init(ADC, sysclk_get_main_hz(), ADC_CLOCK, 8);
	adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_channel(ADC, adc_channel);

	// adc_enable_interrupt(ADC, ADC_IER_DRDY);
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
}

uint32_t adc_get_value()
{
	while ((adc_get_status(ADC) & ADC_ISR_DRDY) != ADC_ISR_DRDY); 
	return adc_get_latest_value(ADC);
}