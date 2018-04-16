/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <stdio_serial.h>
#include <inttypes.h>
#include "conf_board.h"
#include "adc_with_pdc.h"
#include "configure_tc.h"
#include "sampling.h"
#include "trigger_on_amplitude.h"
#include "timer_counter.h"

//#define CHECK_PIN PIO_PB26_IDX	//Arduino Due pin 22 used to measure work load


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
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	configureConsole();
	/*
	ioport_init();
	adc_setup();
	configure_tc();
	init_amplitude_trigger();
	*/
	configure_timerCounter();
	
	
	//do nothing in main()-loop
	while (1)
	{
		printf("Timer Counter value: %lu\n", read_counter_value()); //tc_read_cv(TC1, 1)
		
	}

}
