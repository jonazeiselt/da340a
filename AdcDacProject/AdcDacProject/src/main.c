/*
 * main.c
 *
 * Created: 2018-05-10
 * Author: Acer
 */ 

#include <asf.h>
#include "console_functions.h"
#include "adc_functions.h"
#include "dacc_functions.h"
#include "tc_functions.h"

int main (void)
{
	/* Board initialization here */
	sysclk_init();
	board_init();
	ioport_init();
	configure_console();
	
	configure_adc();
	configure_dacc();
	configure_tc();

	/* Application code here */
	tc_start(TC0, 0);

	while (adc_finished != 1) {
		printf(".");
	}

	printf("\nFinished adc conversion...\n");
	printf("%d\n", dacc_values[0]);

	tc_start(TC1, 1);
	while (dacc_finished != 1) {
		printf(".");
	}
	printf("\nFinished dac conversion...\n");

	while (1);
}
