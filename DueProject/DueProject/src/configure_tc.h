/*
 * configure_tc.h
 *
 * Created: 2018-04-01 17:07:48
 *  Author: Daniel
 */ 

#include <inttypes.h>

#ifndef CONFIGURE_TC_H_
#define CONFIGURE_TC_H_

void configure_tc(void);
extern int configureDone; //header file declares external variable
                          //other files may include the declaration of the external variable (declaration suffices once)

#endif /* CONFIGURE_TC_H_ */