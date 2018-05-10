/*
* ConsoleFunctions.c
*
* Created: 2018-03-30 14:15:13
*  Author: Acer
*/

#include <stdio_serial.h>
#include <asf.h>
#include "config/conf_board.h"
#include "console_functions.h"

void configure_console(void)
{
	const usart_serial_options_t uart_serial_options =
	{
		.baudrate = CONF_UART_BAUDRATE,
		.paritytype = CONF_UART_PARITY
	};

	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONF_UART, &uart_serial_options);

	//printf("Console ready\n");
	//printf("=============\n");
}
