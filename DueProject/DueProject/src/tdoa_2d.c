/*
 * tdoa_2d.c
 *
 * Created: 2018-04-24 11:58:40
 *  Author: Daniel
 */ 
#include <asf.h>
#include <inttypes.h>
#include <machine\fastmath.h>
#include <math.h>
#include <string.h>
#include "tdoa_2d.h"
#include "dec_string.h"

int x2 = 4;
int x3 = 2;
int y3 = 4;

/*
void calculate_position(double t21, double t31)
{
	double v = 343;
	double r21 = v*t21;
	double r31 = v*t31;
	
	double g = (r31*(x2/r21)-x3)/y3;
	double h = (x3*x3+y3*y3-r31*r31+(r31*r21)*(1-(x2/r21)*(x2/r21)))/(2*y3);
	double d = -(1-(x2/r21)*(x2/r21)+g*2);
	double e = x2*(1-(x2/r21)*(x2/r21))-(2*g*h);
	double f = ((r21*r21)/4)*(1-(x2/r21)*(x2/r21))*(1-(x2/r21)*(x2/r21))-h*h;
	
	double x = (-e-sqrt(e*e-(4*d*f)))/(2*d);
	double y = g*x+h;
	printf("x-coordinate: %s\n", get_decimal_string(x));
	printf("y-coordinate: %s\n", get_decimal_string(y));
}*/