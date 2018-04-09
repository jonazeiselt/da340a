/*
* adc_with_pdc.c
*
* Created: 2018-04-01 17:04:52
*  Author: Daniel
*/

/*
* The connected PDC channel to the ADC-peripheral is a Receive channel (i.e. a transfer from peripheral to memory)
* It receives/reads converted data from the ADC-sampling process and stores it in a memory space, i.e. the memory
* address we give it through the Receive Pointer Registers (which is the address of our buffer where we want our
* sample values to be stored).
*/
#include <asf.h>
#include "adc_with_pdc.h"
#include <string.h>
#include <inttypes.h>

#define M  2
static float xbuff[M+1] = {0}; // delayed values of input signal
static float b[M+1] = {0.3333, 0.3333, 0.3333}; //filter coefficients, gain = 1


/**
* \brief Read converted data through PDC channel.
*
* \param p_adc The pointer of ADC peripheral.
* \param p_s_buffer The destination buffer.
* \param ul_size The size of the buffer.
*/
static uint32_t adc_read_buffer(Adc * p_adc, uint16_t * p_s_buffer, uint32_t ul_size)
{
	/* Check if the first PDC bank is free: if so start transferring data to it.
	* Counters are decremented until data has been completely transferred to buffer.
	* Once they both reach zero the transfer of data to the buffer is done and RXBUFF flag is set.
	*/
	if ((p_adc->ADC_RCR == 0) && (p_adc->ADC_RNCR == 0)) {
		// The two lines of code below load the buffer address and size into the PDC associated channel register.
		p_adc->ADC_RPR = (uint32_t) p_s_buffer; /* Receive Pointer Register */
		p_adc->ADC_RCR = ul_size;               /* Receive Counter Register */
		
		/* Enables PDC receiver channel requests. PDC receive channel starts reading
		* ADC converted data and transfers sample values to buffer in memory location. */
		p_adc->ADC_PTCR = ADC_PTCR_RXTEN; /*ADC_PTCR = Transfer Control Register, RXTEN: Receiver Transfer Enable */

		return 1;
		} else {	/* Check if the second PDC bank is free. */
		if (p_adc->ADC_RNCR == 0)
		{
			p_adc->ADC_RNPR = (uint32_t) p_s_buffer; /* Receive Next Pointer Register */
			p_adc->ADC_RNCR = ul_size;               /* Receive Next Counter Register */
			return 1;
		}
		else {
			return 0;
		}
	}
}

/* Configure the ADC */
void adc_setup()
{
	pmc_enable_periph_clk(ID_ADC);
	/* Initialize ADC
	*     Startup  Time = startup value / ADCClock
	*     Startup time = 64 / 6.4MHz = 10 us
	*/
	adc_init(ADC, sysclk_get_cpu_hz(), ADC_CLOCK, ADC_STARTUP_TIME_4);
	
	/* Set ADC timing
	*     Transfer Time = (TRANSFER * 2 + 3) / ADCClock = (0 * 2 + 3) / 6.4MHz = 469 ns
	*     Tracking Time = (TRACKTIM + 1) / ADCClock = (0 + 1) / 6.4MHz = 156 ns
	*     Settling Time = settling value / ADCClock = 3 / 6.4MHz = 469 ns
	*/
	adc_configure_timing(ADC, TRACKING_TIME, SETTLING_TIME, TRANSFER_TIME);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_12);
	adc_enable_channel(ADC, ADC_CHANNEL_10);			//PB17 - AD8 for Arduino Due
	/* Trigger conversion just by software */
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);
	/* Start transferring converted data to buffer */
	adc_read_buffer(ADC, adc_buffer_sample_values, ADC_BUFFER_SIZE);
	/* Enable PDC channel interrupt. */
	adc_enable_interrupt(ADC, ADC_IER_RXBUFF);
	/* Enable ADC interrupt. */
	NVIC_EnableIRQ(ADC_IRQn);
}

static void smooth_values(uint16_t *buffer)
{
	uint16_t temp_buff[ADC_BUFFER_SIZE];
	uint16_t invalue, outvalue;
	for (int i = 0; i < ADC_BUFFER_SIZE; i++)
	{
		//Shift array values upwards
		for(int k = M-1; k >= 0; k--)
		{
			xbuff[k+1] = xbuff[k];
		}
		invalue = buffer[i];
		xbuff[0] =(float)invalue;
		float sum = 0;
		// Construct sum 
		for(int j = 0; j <= M; j++){
			sum += (xbuff[j]*b[j]);
		}
		outvalue = (uint16_t)sum;
		temp_buff[i] = outvalue;
	}
	//Copy values of temp_buff into old buffer
	for (int i = 0; i < ADC_BUFFER_SIZE; i++)
	{
		uint16_t *ip;       /* ip is a pointer to uint16_t */
		ip = &buffer[i];    /* sets ip to point to element i of buffer (contains address of buffer[i]) */
		*ip = temp_buff[i]; /* *ip points to content of buffer[i], this will change content of buffer[i] */
	}
}

void ADC_Handler(void){
	/* Data transfer has been stopped (is complete) and RXBUFF status flag is set because ADC_RCR
	* and the ADC_RNCR have reached zero. Buffer of sample values is full.
	*/
	if ((adc_get_status(ADC) & ADC_ISR_RXBUFF) == ADC_ISR_RXBUFF) {
		
		for (int i = 0; i < ADC_BUFFER_SIZE; i++)
		{
			printf("Buffer values: %u, index: %u\n", adc_buffer_sample_values[i], i);
		}
		smooth_values(adc_buffer_sample_values);
		for (int i = 0; i < ADC_BUFFER_SIZE; i++)
		{
			printf("Temp buffer: %u, index: %u\n", adc_buffer_sample_values[i], i);
		}
		
		/* Clear sample buffer */
		memset((void *)&adc_buffer_sample_values, 0, sizeof(adc_buffer_sample_values));
		/* Read new buffer data. Necessary, otherwise buffer values are null/zero */
		adc_read_buffer(ADC, adc_buffer_sample_values, ADC_BUFFER_SIZE);
	}
}


