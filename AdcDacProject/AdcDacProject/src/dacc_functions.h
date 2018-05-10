/*
 * dacc_functions.h
 *
 * Created: 2018-05-10
 * Author: Jonas Eiselt
 */ 


#ifndef DACC_FUNCTIONS_H_
#define DACC_FUNCTIONS_H_

#define DACC_CHANNEL 0
#define DACC_BUFFER_SIZE 3260

extern int16_t dacc_finished;
extern int16_t dacc_index;
extern int16_t dacc_values[DACC_BUFFER_SIZE];

void configure_dacc(void);

#endif /* DACC_FUNCTIONS_H_ */