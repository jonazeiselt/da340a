/*
* main.c
*
* Created: 2018-05-05
* Author: Acer
*/

#include <asf.h>
#include <stdio.h>
#include <string.h>
#include "console_functions.h"
#include "bluetooth_functions.h"

int main (void)
{
	sysclk_init();
	board_init();
	ioport_init();

	configure_console();
	bluetooth_init();
	
	char arr[10] = {0};

	bluetooth_getmessage(arr, 10);
	printf("Received %s\n", arr);

	bluetooth_sendmessage(arr, 10);
	printf("Sent %s\n", arr);

	/*while (1)
	{
		char str[3];
		receive_message(str);
		printf("%s", str);

		if (strcmp(str, "Hi") == 0)
		{
			printf("Hi!");
		}
	}*/
}
