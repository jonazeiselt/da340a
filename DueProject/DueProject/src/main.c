/**
* \file main.c
*
* \brief Initialization of all necessary functions starts here
*
*/
#include <asf.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_serial.h>
#include "conf_board.h"
#include "adc_with_pdc.h"
#include "configure_tc.h"
#include "sampling.h"
#include "amplitude_trigger.h"
#include "tdoa.h"
#include "dec_string.h"

static uint32_t abs_value(uint32_t realFreq, uint32_t measuredFreq);
//uint32_t realFrequencies[4] = {55000, 50000, 60000, 40000};

/**
* \brief Configure UART for debug message output.
*/
static void configureConsole(void)
/* Enables feedback through the USB-cable back to terminal within Atmel Studio */
/* Note that  the baudrate, parity and other parameters must be set in conf/conf_uart_serial.h */
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};
	
	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	//printf("Console ready\n");
	//printf("=============\n");
}

static uint32_t abs_value(uint32_t realFreq, uint32_t measuredFreq)
{
	int32_t diffVal = (int32_t)realFreq-(int32_t)measuredFreq;
	if (diffVal < 0)
	{
		diffVal = diffVal*(-1);
	}
	return (uint32_t)diffVal;
}

int main (void)
{
	sysclk_init();
	board_init();
	ioport_init();
	configureConsole();
	ioport_set_pin_dir(PIO_PC28_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PC28_IDX, LOW);
	delay_ms(100);
	ioport_set_pin_level(PIO_PC28_IDX, HIGH);
	char buf[20];
	scanf("%s", buf);
	if (strcmp(buf, "Hi") == 0){
		
		tdoa_init();
		//adc_setup();
		configure_tc();
		//ioport_set_pin_dir(CHECK_PIN, IOPORT_DIR_OUTPUT);
		TC1_init();
		configure_tc();
		init_amplitude_trigger();
		//init_pulse_pin();
	}
	
	
	/*
	uint32_t start = tc_read_cv(TC1, 1);
	int risingEdges = 1010;
	static uint32_t frequency = 0;
	uint32_t arrayOfFrequencies[risingEdges];
	double arrayOfTDOAvalues[4];
	for (int i = CYCLE_INTERVAL; i < risingEdges; i++)
	{
	top_to_low = tc_values_1[i]-tc_values_1[i-CYCLE_INTERVAL];
	frequency = 42000000/(top_to_low/(CYCLE_INTERVAL));
	arrayOfFrequencies[i-CYCLE_INTERVAL] = frequency;
	}
	int firstArrival = 0;
	for (int k = 0; k < 4; k++)
	{
	int consecutiveCounter = 0;
	int maxConsecutiveCounter = 0;
	int offsetIndex = 0;
	for (int i = 0; i < risingEdges; i++)
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
	offsetIndex = i-maxConsecutiveCounter;
	if (k == 0)
	{
	firstArrival = offsetIndex;
	}
	}
	//printf("Number of %lu Hz in a row: %d \n", realFrequencies[k], consecutiveCounter);
	consecutiveCounter = 0;
	}
	}
	//printf("Max number of %lu Hz in a row: %d \n", realFrequencies[k], maxConsecutiveCounter);
	//printf("Max number of %lu Hz in a row occurs at index: %d \n", realFrequencies[k], offsetIndex);
	double interval = (float) (tc_values_1[offsetIndex]-tc_values_1[firstArrival])/42000000;
	printf("%lu has time of arrival: %s ms\n", realFrequencies[k], get_decimal_string(interval*1000-k*30));
	arrayOfTDOAvalues[k] = interval-k*0.03;
	}
	tdoa_init();
	set_tdoa(arrayOfTDOAvalues[0], arrayOfTDOAvalues[1], arrayOfTDOAvalues[2], arrayOfTDOAvalues[3]);
	double x, y, z = 0;
	calculate_position(&x, &y, &z);
	printf("x, y, z: %s, %s, %s\n", get_decimal_string(x), get_decimal_string(y), get_decimal_string(z));
	uint32_t stop = tc_read_cv(TC1, 1);
	double res = (float)(stop-start)/42000000;
	printf("Time algorithm takes: %s ms\n", get_decimal_string(res*1000));
	*/
	//nothing important in main()-loop
	while (1)
	{
		
	}

}
