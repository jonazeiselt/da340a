/*
* sampling.c
*
* Created: 2018-04-03 11:46:58
*  Author: Daniel
*/

#include <inttypes.h>
#include <asf.h>
#include <string.h>
#include <float.h>
#include <stdio.h>
#include "sampling.h"
#include "amplitude_trigger.h"
#include "dec_string.h"
#include "tdoa.h"

int rising_edges = 0;
uint32_t top_to_low = 0;
static uint32_t abs_value(uint32_t realFreq, uint32_t measuredFreq);
uint32_t realFrequencies[4] = {55000, 50000, 60000, 65000};
double arrayOfCoordinateValues[5][3];

static void calc_average(double matrix[5][3]);

static uint32_t abs_value(uint32_t realFreq, uint32_t measuredFreq)
{
	int32_t diffVal = (int32_t)realFreq-(int32_t)measuredFreq;
	if (diffVal < 0)
	{
		diffVal = diffVal*(-1);
	}
	return (uint32_t)diffVal;
}

static void calc_average(double matrix[5][3])
{
	double sumX = 0, sumY = 0, sumZ = 0;
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			switch(col)
			{
				case 0:
				sumX += matrix[row][col];
				break;
				case 1:
				sumY += matrix[row][col];
				break;
				case 2:
				sumZ += matrix[row][col];
				break;
			}
		}
	}
	double avegX = sumX/5;
	double avegY = sumY/5;
	double avegZ = sumZ/5;
	
	printf("x, y, z: %s, %s, %s \n", get_decimal_string(avegX),
	get_decimal_string(avegY), get_decimal_string(avegZ));
}

/**
*  Interrupt handler for TC0 interrupt. Buffer cycles of all four signals for about 150 ms
*  Executes once done buffering all four signals.
*/
void TC0_Handler(void)
{
	//ioport_set_pin_level(CHECK_PIN,LOW);		//put test pin LOW
	volatile uint32_t ul_dummy;
	//static int counter = 0;
	/* Clear status bit to acknowledge interrupt */
	ul_dummy = tc_get_status(TC0, 0);	//The compare bit is cleared by reading the register, manual p. 915

	/* Avoid compiler warning */
	UNUSED(ul_dummy);
	pio_enable_interrupt(PIOB, PIO_PB26);	
	/*
	pio_disable_interrupt(PIOA, PIO_PA14);
	//stop = tc_read_cv(TC1, 1);
	//printf("Nbr of edges: %i\n", rising_edges);
	//double res = (float)(stop-start)/42000000;
	//printf("Time 1: %s ms\n", get_decimal_string(res*1000));
	
	double arrayOfTDOAvalues[4];
	uint32_t arrayOfFrequencies[rising_edges];
	uint32_t frequency = 0;
	for (int i = CYCLE_INTERVAL; i < rising_edges; i++)
	{
		top_to_low = buffer_of_cycles[i]-buffer_of_cycles[i-CYCLE_INTERVAL];
		frequency = (uint32_t) ((float)42000000/((float)top_to_low/(CYCLE_INTERVAL)));
		printf("Frequency: %lu Hz\n", frequency);
		arrayOfFrequencies[i-CYCLE_INTERVAL] = frequency;
	}
	for (int k = 0; k < 4; k++)
	{
		int consecutiveCounter = 0;
		int maxConsecutiveCounter = 0;
		int offsetIndex = 0;
		int offsetIndex55kHz = 0;
		for (int i = 0; i < rising_edges; i++)
		{
			if (abs_value(realFrequencies[k], arrayOfFrequencies[i]) <= 2000)
			{
				consecutiveCounter++;
			}
			else
			{
				if (consecutiveCounter > maxConsecutiveCounter)
				{
					maxConsecutiveCounter = consecutiveCounter;
					offsetIndex = i - maxConsecutiveCounter;
					if (k == 0)
					{
						offsetIndex55kHz = offsetIndex;
					}
				}
				//printf("Number of %lu Hz in a row: %d \n", realFrequencies[k], consecutiveCounter);
				consecutiveCounter = 0;
			}
		}
		//printf("Max number of %lu Hz in a row: %d \n", realFrequencies[k], maxConsecutiveCounter);
		//printf("Max number of %lu Hz in a row occurs at index: %d \n", realFrequencies[k], offsetIndex);
		double interval = (float) (buffer_of_cycles[offsetIndex]-buffer_of_cycles[offsetIndex55kHz])/42000000;
		//printf("%lu has time of arrival: %s ms\n", realFrequencies[k], get_decimal_string(interval*1000));
		arrayOfTDOAvalues[k] = interval-k*0.03;
	}
	set_tdoa(arrayOfTDOAvalues[0], arrayOfTDOAvalues[1], arrayOfTDOAvalues[2], arrayOfTDOAvalues[3]);
	double x, y, z = 0;
	calculate_position(&x, &y, &z);
	arrayOfCoordinateValues[counter][0] = x;
	arrayOfCoordinateValues[counter][1] = y;
	arrayOfCoordinateValues[counter][2] = z;
	counter++;
	if (counter >= 5)
	{
		calc_average(arrayOfCoordinateValues);
		counter = 0;
	}
	//printf("x, y, z: %s, %s, %s\n", get_decimal_string(x), get_decimal_string(y), get_decimal_string(z));
	rising_edges = 0;
	memset((void *)&buffer_of_cycles, 0, sizeof(buffer_of_cycles));
	memset((void *)&arrayOfTDOAvalues, 0, sizeof(arrayOfTDOAvalues));
	//stop = tc_read_cv(TC1, 1);
	//res = (float)(stop-start)/42000000;
	//printf("Time 2: %s ms\n", get_decimal_string(res*1000));
	pio_enable_interrupt(PIOB, PIO_PB26);
	*/
}



void pin_high_pulse_handler(const uint32_t id, const uint32_t index)
{
	if ((id == ID_PIOA) && (index == PIO_PA14))
	{
		if (pio_get(PIOA, PIO_TYPE_PIO_INPUT, PIO_PA14))
		{
			buffer_of_cycles[rising_edges++] = tc_read_cv(TC1, 1);
		}
	}
}


void init_pulse_pin(void)
{
	pmc_enable_periph_clk(ID_PIOA);
	pio_set_input(PIOA, PIO_PA14, PIO_PULLUP); // PA14 = pin 23
	pio_pull_up(PIOA, PIO_PA14, 0); //enable pull-down, when no input then input state is low
	pio_handler_set(PIOA, ID_PIOA, PIO_PA14, PIO_IT_EDGE, pin_high_pulse_handler);
	pio_disable_interrupt(PIOA, PIO_PA14);
	NVIC_EnableIRQ(PIOA_IRQn);
}

void TC1_init(void)
{
	/* Configure power management of timer clocks (ID_TC4 = channel 1 of TC1) */
	pmc_enable_periph_clk(ID_TC4);
	tc_init(TC1, 1, 0 | TC_CMR_CPCTRG);
	tc_start(TC1, 1);
}

