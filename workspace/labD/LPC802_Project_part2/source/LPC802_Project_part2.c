// EECS 3215 Lab D, part 2

#include "LPC802.h"

int main(void) {
	// Turn onthe GPIO system.
	SYSCON->SYSAHBCLKCTRL0 |= SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK;
	// loop infinitely
	while (1) {
		asm("NOP");
	}
} // END OF MAIN
