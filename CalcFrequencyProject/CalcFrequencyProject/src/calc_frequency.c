/*
* calc_frequency.c
*
* Created: 2018-04-04 10:53:59
*  Author: Acer
*/

#include <stdio.h>
#include <string.h>
#include <asf.h>
#include "calc_frequency.h"
#include "dec_string.h"

static int32_t windowSize = 0;
static int32_t halfWindow = 0;

static int32_t bitOffset = 0;

/* Calculate offset in bits */
void calc_init(int32_t filterPoints, int32_t voltOffset)
{
	windowSize = filterPoints;
	halfWindow = filterPoints/2;

	double offsetRatio = 4095.0/3300.0;
	bitOffset = offsetRatio*voltOffset;

	printf("Points = %d\n", windowSize);
	printf("Offset is %d\n", bitOffset);
}

double calc_frequency(int32_t x[], int32_t nbrOfSamples, double Fs)
{
	// Fill this array with filtered data
	int32_t y[nbrOfSamples]; 
	
	int32_t sign1 = 0, sign2 = 0;
	int32_t prevVal = 0;
	uint32_t zeroCrossings = 0;

	int32_t lim = nbrOfSamples-halfWindow; 
	
	// Filter and determine zero crossings
	for (int32_t i = halfWindow; i < lim; i++)
	{
		y[i] = bitOffset;
		for (int32_t j = -halfWindow; j < halfWindow; j++) 
		{
			y[i] = y[i] + x[i+j];
			printf("Add %d: %d\n", i, y[i]);
		}
		y[i] = y[i]/windowSize;
		printf("Result %d: %d\n", i, y[i]);
		
		// compare y[i] to a previous value?
		if (i > 1)
		{
			sign1 = getSign(prevVal);
			sign2 = getSign(y[i]);
			
			if (sign1 != sign2) 
			{
				zeroCrossings++;
			}
		}
		prevVal = y[i];
	}
	
	// Calculate frequency
	double timeSpan = nbrOfSamples/Fs;
	double nbrOfCycles = zeroCrossings/2;
	double frequency = nbrOfCycles/timeSpan;
	
	printf("Cycles: %d\n", nbrOfCycles);
	printf("Time span: %s s\n", get_decimal_string(timeSpan));
	printf("Zeros: %d\n", zeroCrossings);
	
	return frequency;
}

int32_t getSign(int32_t data)
{
	int32_t sign = data - bitOffset;
	
	if (sign > 0)
		return 1;
	else
		return 0;	
}

