/*
 * bluetooth_functions.c
 *
 * Created: 2018-05-05
 * Author: Jonas Eiselt
 */

#include <stdio_serial.h>
#include <asf.h>
#include "config/conf_board.h"
#include "bluetooth_functions.h"

void bluetooth_getmessage(char *buf)
{
	scanf("%s", buf);
}

void bluetooth_sendmessage(char *buf)
{
	printf("%s\n", buf);
}
