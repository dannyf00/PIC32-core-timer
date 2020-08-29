#include "config.h"						//configuration words
#include "gpio.h"
#include "delay.h"						//we use software delays
#include "coretick.h"					//we use core timer

//hardware configuration
#define LED_PORT			LATB
#define LED_DDR				TRISB
#define LED					(1<<7)
#define LED_DLY				10000
//end hardware configuration

//global defines

//global variables

void led_flp(void) {
	IO_FLP(LED_PORT, LED);
}
	
int main(void) {
	uint32_t t;
	mcu_init();						//reset the mcu
	IO_OUT(LED_DDR, LED);
	coretimer_init();				//reset core timer
	coretimer_setpr(LED_DLY/2);		//set compare / period -> core timer runs at half the rate
	coretimer_act(led_flp);			//install user handler
	ei();							//enable interrupts
	while (1) {
		t=coreticks();
		delay_ms(100);
		t=coreticks() - t;
	}
}
