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
	char *string = malloc(100);

	memset(string, 0, 100);
	sprintf(string, "%0.10f", in);

	return string;
 }
