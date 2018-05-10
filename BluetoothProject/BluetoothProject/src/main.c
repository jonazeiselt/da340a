/*
 * main.c
 * Simple program sending random coordinates to the Bluetooth module 
 * HC-06 by means of the UART interface (TX0, RX0).
 *
 * Created: 2018-05-05
 * Author: Jonas Eiselt
 */

#include <asf.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "console_functions.h"
#include "bluetooth_functions.h"
#include "dec_string.h"

int main (void)
{
	sysclk_init();
	board_init();
	ioport_init();

	configure_console();
	
	char arr[20];
	bluetooth_getmessage(arr);

	if (strcmp(arr, "Hi") == 0)
	{
		bluetooth_sendmessage("Hey you!");
		delay_ms(20);

		double xRand = 0, yRand = 0, zRand = 0;
		double max = 0.7, min = 0;
		double range = (max - min);
		double div = RAND_MAX / range;

		while (1)
		{
			xRand = min + (rand() / div);
			yRand = min + (rand() / div);
			zRand = min + (rand() / div);
			
			char buf[100];	
			sprintf(buf, "coord: %s %s %s", get_decimal_string(xRand, 6), get_decimal_string(yRand, 6), get_decimal_string(zRand, 6));

			bluetooth_sendmessage(buf);
			delay_ms(200);
		}
	}
	else
	{
		bluetooth_sendmessage(arr);
	}
}
