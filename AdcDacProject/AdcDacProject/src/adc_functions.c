/*
 * adc_functions.c
 *
 * Created: 2018-04-01
 * Author: Danial
 */

#include <asf.h>
#include <inttypes.h>
#include <string.h>
#include "adc_functions.h"
#include "dacc_functions.h"

int16_t adc_finished;
int16_t dacc_values[ADC_BUFFER_SIZE];

/*
 * Sets ADC timing
 * Transfer Time = (TRANSFER * 2 + 3) / ADCClock = (0 * 2 + 3) / 6.4MHz = 469 ns
 * Tracking Time = (TRACKTIM + 1) / ADCClock = (0 + 1) / 6.4MHz = 156 ns
 * Settling Time = settling value / ADCClock = 3 / 6.4MHz = 469 ns
 *
 * Initializes ADC
 * Startup  Time = startup value / ADCClock
 * Startup time = 64 / 6.4MHz = 10 us
 */
void configure_adc(void)
{
	pmc_enable_periph_clk(ID_ADC);
	
	adc_init(ADC, sysclk_get_cpu_hz(), ADC_CLOCK, ADC_STARTUP_TIME_4);
	adc_configure_timing(ADC, TRACKING_TIME, SETTLING_TIME, TRANSFER_TIME);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	
	// A0 = PA16 (AD7)
	adc_enable_channel(ADC, ADC_CHANNEL_7);
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);

	adc_read_buffer(adc_values);

	adc_enable_interrupt(ADC, ADC_IER_RXBUFF);
	NVIC_EnableIRQ(ADC_IRQn);
}

uint32_t adc_read_buffer(int16_t *p_s_buffer)
{
	if ((ADC->ADC_RCR == 0) && (ADC->ADC_RNCR == 0))
	{
		ADC->ADC_RPR = (uint32_t) p_s_buffer;
		ADC->ADC_RCR = ADC_BUFFER_SIZE;
		ADC->ADC_PTCR = ADC_PTCR_RXTEN;
		
		return 1;
	}
	else if (ADC->ADC_RNCR == 0)
	{
		ADC->ADC_RNPR = (uint32_t) p_s_buffer;
		ADC->ADC_RNCR = ADC_BUFFER_SIZE;
		
		return 1;
	}
	return 0;
}

/* Interrupt handler for ADC */
void ADC_Handler(void)
{
	if ((adc_get_status(ADC) & ADC_ISR_RXBUFF) == ADC_ISR_RXBUFF)
	{
		tc_stop(TC0, 0);

		for (int i = 0; i < ADC_BUFFER_SIZE; i++)
		{
			dacc_values[i] = adc_values[i];
		}
		adc_finished = 1;

		memset((void *) &adc_values, 0, sizeof(adc_values));
		adc_read_buffer(adc_values);
	}
}
