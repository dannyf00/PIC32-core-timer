#include "coretick.h"						//we use core timer

//hardware configuration
//end hardware configuration

//global defines

//global variables
uint32_t coretimer_pr=0;			//core timer period

//empty handler
static void /*_tmr1_*/empty_handler(void) {
	//default tmr handler
}

//global variables
static void (* /*_tmr1*/_isr_ptr)(void)=empty_handler;				//tmr1_ptr pointing to empty_handler by default

//core timer isr
void __ISR(_CORE_TIMER_VECTOR, ipl2) CoreTimerHandler(void) {
	//clear the flag
	//When the value of COUNT equals the value of COMPARE, the CPU asserts an interrupt signal
	//to the system interrupt controller. This signal will remain asserted until COMPARE is written.
	IFS0CLR = _IFS0_CTIF_MASK;	_CP0_SET_COMPARE(_CP0_GET_COMPARE() + coretimer_pr);			//advance compare to the next match point
	_isr_ptr();						//execute user handler
}
	
//initialize core timer
void coretimer_init(void) {
	//reset the handler
	_isr_ptr = empty_handler;
	
	//do nothing as the core timer is always running
	
	//clear the flag
	//IFS0CLR = _IFS0_CTIF_MASK;
	//disable core timer interrupt
	// Set up core timer interrupt
 	// clear core timer interrupt flag
 	IFS0CLR = _IFS0_CTIF_MASK;
 	// set core time interrupt priority of 2
 	IPC0CLR = _IPC0_CTIP_MASK;
 	IPC0SET = (2 << _IPC0_CTIP_POSITION);
 	// set core time interrupt subpriority of 0
 	IPC0CLR = _IPC0_CTIS_MASK;
 	IPC0SET = (0 << _IPC0_CTIS_POSITION);
 	// disenable core timer interrupt
 	IEC0CLR = _IEC0_CTIE_MASK;
 	IEC0CLR = (1 << _IEC0_CTIE_POSITION);
}


//set period
//pr is the match point
void coretimer_setpr(uint32_t pr) {
	coretimer_pr = pr;				//set coretimer_pr
	_CP0_SET_COMPARE(_CP0_GET_COUNT() + coretimer_pr);				//advance tot he next match point
}

//install user handler
void coretimer_act(void (*isr_ptr)(void)) {
	_isr_ptr = isr_ptr;				//install user handler
	//clear the flag
	IFS0CLR = _IFS0_CTIF_MASK;
	//enable core timer interrupt
	IEC0SET = (1 << _IEC0_CTIE_POSITION);
}
