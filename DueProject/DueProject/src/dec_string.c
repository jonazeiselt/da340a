/*
 * dec_string.c
 *
 * Created: 2018-04-05 08:24:33
 *  Author: Acer
 */ 

 #include <asf.h>
 #include <string.h>
 #include "dec_string.h"

 char* get_decimal_string(double in) 
 {
	char *string = malloc(20);

	memset(string, 0, 20);
	sprintf(string, "%0.6f", in);

	return string;
 }
