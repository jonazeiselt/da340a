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
	
	ioport_init();
	adc_setup();
	configure_tc();
	init_amplitude_trigger();
	init_pulse_pin();
	TC1_init();

	
	
	//nothing important in main()-loop
	while (1)
	{
		//printf("Timer Counter value: %lu\n", read_counter_value()); //tc_read_cv(TC1, 1)
		
	}

}
