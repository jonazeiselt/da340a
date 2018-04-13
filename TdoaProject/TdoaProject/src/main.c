/*
 * tdoa.c
 *
 * Created: 2018-04-13
 * Author: Danial Mahmoud and Jonas Eiselt
 */ 

#include <asf.h>
#include "tdoa.h"
#include "console_functions.h"
#include "dec_string.h"

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	configure_console();

	/* Insert application code here, after the board has been initialized. */
	double x = 0;
	double y = 0;
	double z = 0;
	tdoa_init();
	set_sdoa(3440, 3015, 815, 0);
	calculate_position(&x, &y, &z);

	printf("x = %s \n", get_decimal_string(x));
	printf("y = %s \n", get_decimal_string(y));
	printf("z = %s \n", get_decimal_string(z));
}
