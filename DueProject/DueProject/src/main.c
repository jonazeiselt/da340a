/**
 * \file main.c
 *
 * \brief Initialization of all necessary functions starts here
 *
 */
#include <asf.h>
#include <stdio_serial.h>
#include <inttypes.h>
#include "conf_board.h"
#include "adc_with_pdc.h"
#include "configure_tc.h"
#include "sampling.h"
#include "amplitude_trigger.h"
#include "tdoa.h"
#include "dec_string.h"


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
	printf("Console ready\n");
	printf("=============\n");
}


int main (void)
{
	sysclk_init();
	board_init();
	configureConsole();
	/*
	tdoa_init();
	double ti = 2.578327; //(double)42035700*((float)1/42000000);
	double tj = 1.376376; //(double)42000000*((float)1/42000000);
	double tk = 4.488732; //(double)41815200*((float)1/42000000);
	double tl = 0.678136; //(double)41746740*((float)1/42000000);
	printf("ti: %s, tj: %s, tk: %s, tl: %s\n", get_decimal_string(ti), get_decimal_string(tj), get_decimal_string(tk), get_decimal_string(tl));
	set_tdoa(ti, tj, tk, tl); //set_tdoa(1.00085, 1, 0.9956, 0.99397);
	double x = 0;
	double y = 0;
	double z = 0;
	calculate_position(&x, &y, &z);
	printf("x-coord: %s \n", get_decimal_string(x));
	printf("y-coord: %s \n", get_decimal_string(y));
	printf("z-coord: %s \n", get_decimal_string(z));
	*/
	
	ioport_init();
	tdoa_init();
	//calc_init(5, 1650);
	//adc_setup(); 
	//configure_tc();
	TC1_init();
	init_pulse_pin();
	init_amplitude_trigger();
	
	
	//nothing important in main()-loop
	while (1)
	{
		//printf("TC1, ch1 value: %lu\n", tc_read_cv(TC1, 1)); 
		//printf("TC2, ch2 value: %lu\n", tc_read_cv(TC2, 2));

		
	}

}
