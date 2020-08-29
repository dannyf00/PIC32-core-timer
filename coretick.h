#ifndef _CORETICK_H
#define _CORETICK_H

#include "gpio.h"					//we use cp0def.h

//hardware configuration
//end hardware configuration

//global defines
//read core timer - returns at half of rate of SYSCLK
#define coreticks()			_CP0_GET_COUNT()	

//if no systicks is defined
//use coreticks in its place - for compatibility
#ifndef systicks
#define systicks()			coreticks()
#endif

//global variables

//initialize core timer
void coretimer_init(void);

//set period
//pr is the match point
void coretimer_setpr(uint32_t pr);

//install user handler
void coretimer_act(void (*isr_ptr)(void));

#endif
