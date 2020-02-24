// KsKa lab 1, part3
#include "LPC802.h"

int main(void){

	// Turn on the GPIO system.
	SYSCON->SYSAHBCLKCTRL0 |= (SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK);

	// Set GPIO 9 to be output (bit 9 is a 1)
	GPIO->DIRSET[0] = 0b100000000;

	while(1){
		// Bit 9 is responsible for GPIO 9
		GPIO->SET[0] = 0b100000000;
		GPIO->CLR[0] = 0b100000000;
	}

}
