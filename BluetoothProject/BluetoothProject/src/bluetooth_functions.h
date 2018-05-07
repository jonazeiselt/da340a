/*
 * bluetooth_functions.h
 *
 * Created: 2018-05-05 17:59:16
 * Author: Acer
 */ 


#ifndef BLUETOOTH_FUNCTIONS_H_
#define BLUETOOTH_FUNCTIONS_H_

void bluetooth_init();
void bluetooth_getmessage(char *buf, int size);
void bluetooth_sendmessage(char *buf, int size);

#endif /* BLUETOOTH_FUNCTIONS_H_ */