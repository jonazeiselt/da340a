/*
 * tdoa.h
 *
 * Created: 2018-04-13
 * Author: Danial Mahmoud and Jonas Eiselt
 */ 


#ifndef TDOA_H_
#define TDOA_H_

void tdoa_init(void);
void set_tdoa(void);
void set_sdoa(double sample_i, double sample_j, double sample_k, double sample_l);
void calculate_position(double *x, double *y, double *z);

#endif /* TDOA_H_ */