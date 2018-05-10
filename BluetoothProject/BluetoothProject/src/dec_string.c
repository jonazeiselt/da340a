/*
 * dec_string.c
 *
 * Created: 2018-04-05
 * Author: Jonas Eiselt
 */ 

 #include <asf.h>
 #include <string.h>
 #include "dec_string.h"

 char* get_decimal_string(double in, int numberOfDecimals) 
 {
	char *string = malloc(20);

	memset(string, 0, 20);
	sprintf(string, "%0.*f", numberOfDecimals, in);

	return string;
 }
