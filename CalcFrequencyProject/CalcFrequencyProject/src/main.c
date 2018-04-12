/*
* \file
*
* \brief Empty user application template
*/

#include <asf.h>
#include "console_functions.h"
#include "adc_functions.h"
#include "calc_frequency.h"
#include "dec_string.h"

int main (void)
{
	/* Initialize board */
	sysclk_init();
	board_init();

	configure_console();
	configure_adc(7); // AD7 = pin A0

	/*
		char *string = get_decimal_string(1.256);
		printf("%s\n", string);

		printf("%s\n", get_decimal_string(1.256));
	*/

	/* Fill array with sample values */
	int32_t sampleValues = 256;

	int32_t x[sampleValues];
	for (int32_t i = 0; i < sampleValues; i++)
	{
		adc_start(ADC);
		x[i] = adc_get_value();
		// printf("%d: %d\n", i, x[i]);

		delay_us(100);
	}

	int32_t nbrOfSamples = sizeof(x)/sizeof(int32_t);

	/* Calculate frequency */
	double sampleFrequency = 10000.00; // ~10 kHz
	
	int32_t offset = 500, halfWindow = 1; // 500 mV
	calc_init(halfWindow, offset);
	
	double frequency = calc_frequency(x, nbrOfSamples, sampleFrequency);
	printf("Frequency: %s Hz\n", get_decimal_string(frequency));

	return 0;
}

