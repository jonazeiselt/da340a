/*
* bluetooth_functions.c
*
* Created: 2018-05-05 17:58:57
* Author: Acer
*/

#include <stdio_serial.h>
#include <asf.h>
#include "config/conf_board.h"
#include "bluetooth_functions.h"

#define TX3 IOPORT_CREATE_PIN(PIOD, 4)
#define RX3 IOPORT_CREATE_PIN(PIOD, 5)

void bluetooth_init()
{
	static usart_serial_options_t usart_serial_options = {
		.baudrate = USART_SERIAL_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};

	ioport_set_pin_dir(TX3, IOPORT_DIR_OUTPUT);
	ioport_set_pin_mode(TX3, IOPORT_MODE_PULLUP);

	ioport_set_pin_dir(RX3, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(RX3, IOPORT_MODE_PULLUP);

	sysclk_enable_peripheral_clock(BOARD_ID_USART3);
	
	//stdio_serial_init(USART_SERIAL, &usart_serial_options);
	
	usart_serial_init(USART_SERIAL, &usart_serial_options);

	/*pmc_enable_periph_clk(ID_USART3);
	
	ioport_set_pin_dir(TX3, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(RX3, IOPORT_DIR_INPUT);
	*/

	//usart_init_rs232(USART_SERIAL, &usart_options, sysclk_get_main_hz());
	
	usart_enable_tx(USART_SERIAL);
	usart_enable_rx(USART_SERIAL);
}

void bluetooth_getmessage(char *buf, int size)
{
	uint32_t received_byte;
	for (int i = 0; i < size; i++)
	{
		// uart_read(CONF_UART, &received_byte);
		usart_getchar(USART_SERIAL, &received_byte);
		buf[i] = received_byte;

		if (received_byte == '\n')
		{
			break;
		}
	}
}

void bluetooth_sendmessage(char *buf, int size)
{
	for (int i = 0; i < size; i++)
	{
		// uart_write(CONF_UART, buf[i]);
		if (usart_is_tx_empty(USART_SERIAL) == 1)
		{
			uint32_t retval = usart_putchar(USART_SERIAL, buf[i]);
			printf("success == 0? %d\n", retval);
		}

		if (buf[i] == '\n')
		{
			break;
		}
	}
}

/*
if (usart_is_tx_empty(USART_SERIAL) == 1)
{
printf("Sending?\n");
// usart_write_line(USART_SERIAL, "Hi\0");

uint32_t retval = usart_putchar(USART_SERIAL, 'A');
printf("Success (0)? %d\n", retval);

// usart_serial_write_packet(USART_SERIAL, "Test String", strlen("Test String"));
// usart_putchar(USART_SERIAL, '\n');
}
*/
// delay_ms(500);

