/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    LPC802_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC802.h"
#include "fsl_debug_console.h"

#define OSCILLATOR_COUNT 12000000

#define CTIMER_MATCH_VALUE (50000) // visible LED blinking: 1000000 +
#define CTIMER_PRESCALE (1) // (1 to 2^32): Prescale divisor for APB clock for CTIMER counter

#define SYSTICK_TICK_DIVIDER 2 // 4 => (1,200,000 / 4)

#define DIGIT_ONE (17)
#define DIGIT_TWO (11)
#define DIGIT_THREE (14)
#define DIGIT_FOUR (10)

#define SEGMENT_A (4)
#define SEGMENT_B (16) // CHANGED THIS CUS 0 DOESNT WORK
#define SEGMENT_C (13)
#define SEGMENT_D (9)
#define SEGMENT_E (7)
#define SEGMENT_F (12)
#define SEGMENT_G (1)

//#define TWO_DOT (0) 0 did not work, 8 did not work, out of GPIO pins.

#define BUTTON_LEFT (8) // S1
#define BUTTON_RIGHT (5) // nRst

#define IS_HOUR_SYSTEM_24 (1) // 1 true 0 false

int minute = 0;
int hour = 12;
int second = 0;

int my_counter = 0;

int hourL, hourR, minuteL, minuteR;


void num_to_seven_segment(int number){

	switch(number)
			{
			case -1:
				GPIO->SET[0] = (1UL<<SEGMENT_A);	// all off
				GPIO->SET[0] = (1UL<<SEGMENT_B);
				GPIO->SET[0] = (1UL<<SEGMENT_C);
				GPIO->SET[0] = (1UL<<SEGMENT_D);
				GPIO->SET[0] = (1UL<<SEGMENT_E);
				GPIO->SET[0] = (1UL<<SEGMENT_F);
				GPIO->SET[0] = (1UL<<SEGMENT_G);
				break;
			case 0:
				GPIO->CLR[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->CLR[0] = (1UL<<SEGMENT_B);
				GPIO->CLR[0] = (1UL<<SEGMENT_C);
				GPIO->CLR[0] = (1UL<<SEGMENT_D);
				GPIO->CLR[0] = (1UL<<SEGMENT_E);
				GPIO->CLR[0] = (1UL<<SEGMENT_F);
				GPIO->SET[0] = (1UL<<SEGMENT_G);
				break;
			case 1:
				GPIO->SET[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->CLR[0] = (1UL<<SEGMENT_B);
				GPIO->CLR[0] = (1UL<<SEGMENT_C);
				GPIO->SET[0] = (1UL<<SEGMENT_D);
				GPIO->SET[0] = (1UL<<SEGMENT_E);
				GPIO->SET[0] = (1UL<<SEGMENT_F);
				GPIO->SET[0] = (1UL<<SEGMENT_G);
				break;
			case 2:
				GPIO->CLR[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->CLR[0] = (1UL<<SEGMENT_B);
				GPIO->SET[0] = (1UL<<SEGMENT_C);
				GPIO->CLR[0] = (1UL<<SEGMENT_D);
				GPIO->CLR[0] = (1UL<<SEGMENT_E);
				GPIO->SET[0] = (1UL<<SEGMENT_F);
				GPIO->CLR[0] = (1UL<<SEGMENT_G);
				break;
			case 3:
				GPIO->CLR[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->CLR[0] = (1UL<<SEGMENT_B);
				GPIO->CLR[0] = (1UL<<SEGMENT_C);
				GPIO->CLR[0] = (1UL<<SEGMENT_D);
				GPIO->SET[0] = (1UL<<SEGMENT_E);
				GPIO->SET[0] = (1UL<<SEGMENT_F);
				GPIO->CLR[0] = (1UL<<SEGMENT_G);
				break;
			case 4:
				GPIO->SET[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->CLR[0] = (1UL<<SEGMENT_B);
				GPIO->CLR[0] = (1UL<<SEGMENT_C);
				GPIO->SET[0] = (1UL<<SEGMENT_D);
				GPIO->SET[0] = (1UL<<SEGMENT_E);
				GPIO->CLR[0] = (1UL<<SEGMENT_F);
				GPIO->CLR[0] = (1UL<<SEGMENT_G);
				break;
			case 5:
				GPIO->CLR[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->SET[0] = (1UL<<SEGMENT_B);
				GPIO->CLR[0] = (1UL<<SEGMENT_C);
				GPIO->CLR[0] = (1UL<<SEGMENT_D);
				GPIO->SET[0] = (1UL<<SEGMENT_E);
				GPIO->CLR[0] = (1UL<<SEGMENT_F);
				GPIO->CLR[0] = (1UL<<SEGMENT_G);
				break;
			case 6:
				GPIO->CLR[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->SET[0] = (1UL<<SEGMENT_B);
				GPIO->CLR[0] = (1UL<<SEGMENT_C);
				GPIO->CLR[0] = (1UL<<SEGMENT_D);
				GPIO->CLR[0] = (1UL<<SEGMENT_E);
				GPIO->CLR[0] = (1UL<<SEGMENT_F);
				GPIO->CLR[0] = (1UL<<SEGMENT_G);
				break;
			case 7:
				GPIO->CLR[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->CLR[0] = (1UL<<SEGMENT_B);
				GPIO->CLR[0] = (1UL<<SEGMENT_C);
				GPIO->SET[0] = (1UL<<SEGMENT_D);
				GPIO->SET[0] = (1UL<<SEGMENT_E);
				GPIO->CLR[0] = (1UL<<SEGMENT_F);
				GPIO->SET[0] = (1UL<<SEGMENT_G);
				break;
			case 8:
				GPIO->CLR[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->CLR[0] = (1UL<<SEGMENT_B);
				GPIO->CLR[0] = (1UL<<SEGMENT_C);
				GPIO->CLR[0] = (1UL<<SEGMENT_D);
				GPIO->CLR[0] = (1UL<<SEGMENT_E);
				GPIO->CLR[0] = (1UL<<SEGMENT_F);
				GPIO->CLR[0] = (1UL<<SEGMENT_G);
				break;
			case 9:
				GPIO->CLR[0] = (1UL<<SEGMENT_A);	// LED is off
				GPIO->CLR[0] = (1UL<<SEGMENT_B);
				GPIO->CLR[0] = (1UL<<SEGMENT_C);
				GPIO->CLR[0] = (1UL<<SEGMENT_D);
				GPIO->SET[0] = (1UL<<SEGMENT_E);
				GPIO->CLR[0] = (1UL<<SEGMENT_F);
				GPIO->CLR[0] = (1UL<<SEGMENT_G);
				break;
			}

}

void num_to_seven_segment_digit(int number, int digit){

	GPIO->CLR[0] = (1UL<<DIGIT_ONE);
	GPIO->CLR[0] = (1UL<<DIGIT_TWO);
	GPIO->CLR[0] = (1UL<<DIGIT_THREE);
	GPIO->CLR[0] = (1UL<<DIGIT_FOUR);

	switch(digit)
		{
		case 1: GPIO->SET[0] = (1UL<<DIGIT_ONE); break;
		case 2: GPIO->SET[0] = (1UL<<DIGIT_TWO); break;
		case 3: GPIO->SET[0] = (1UL<<DIGIT_THREE); break;
		case 4: GPIO->SET[0] = (1UL<<DIGIT_FOUR); break;
		}
	num_to_seven_segment(number);
}

void GPIO_config(){
	// disable interrupts
//	__disable_irq(); // turn off globally
	NVIC_DisableIRQ(PIN_INT0_IRQn); // turn off the PIN INT0 interrupt.

	// ----------------------- Begin GPIO setup ------------------------------------
	// Set up a general GPIO for use
	// Only the ISR needs the GPIO.
	SYSCON->SYSAHBCLKCTRL0 |= ( SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK | // GPIO is on
	SYSCON_SYSAHBCLKCTRL0_GPIO_INT_MASK); // GPIO Interrupt is on
	// Put 0 in the GPIO and GPIO Interrupt reset bit to reset it.
	// Then put a 1 in the GPIO and GPIO Interrupt reset bit to allow both to operate.
	// manual: Section 6.6.10
	SYSCON->PRESETCTRL0 &= ~(SYSCON_PRESETCTRL0_GPIO0_RST_N_MASK |
	SYSCON_PRESETCTRL0_GPIOINT_RST_N_MASK);// reset GPIO and GPIO Interrupt (bit=0)
	SYSCON->PRESETCTRL0 |= (SYSCON_PRESETCTRL0_GPIO0_RST_N_MASK |
	SYSCON_PRESETCTRL0_GPIOINT_RST_N_MASK);// clear reset (bit=1)

	GPIO->SET[0] = (1UL<<SEGMENT_A);	// LED is off
	GPIO->SET[0] = (1UL<<SEGMENT_B);
	GPIO->SET[0] = (1UL<<SEGMENT_C);
	GPIO->SET[0] = (1UL<<SEGMENT_D);
	GPIO->SET[0] = (1UL<<SEGMENT_E);
	GPIO->SET[0] = (1UL<<SEGMENT_F);
	GPIO->SET[0] = (1UL<<SEGMENT_G);

	GPIO->SET[0] = (1UL<<DIGIT_ONE);
	GPIO->SET[0] = (1UL<<DIGIT_TWO);
	GPIO->SET[0] = (1UL<<DIGIT_THREE);
	GPIO->SET[0] = (1UL<<DIGIT_FOUR);

	GPIO->DIRSET[0] = (1UL<<SEGMENT_A);	// output
	GPIO->DIRSET[0] = (1UL<<SEGMENT_B);
	GPIO->DIRSET[0] = (1UL<<SEGMENT_C);
	GPIO->DIRSET[0] = (1UL<<SEGMENT_D);
	GPIO->DIRSET[0] = (1UL<<SEGMENT_E);
	GPIO->DIRSET[0] = (1UL<<SEGMENT_F);
	GPIO->DIRSET[0] = (1UL<<SEGMENT_G);

	GPIO->DIRSET[0] = (1UL<<DIGIT_ONE);
	GPIO->DIRSET[0] = (1UL<<DIGIT_TWO);
	GPIO->DIRSET[0] = (1UL<<DIGIT_THREE);
	GPIO->DIRSET[0] = (1UL<<DIGIT_FOUR);

	GPIO->DIRCLR[0] = (1UL<<BUTTON_LEFT); // button input
	GPIO->DIRCLR[0] = (1UL<<BUTTON_RIGHT); // button input

	// Set up GPIO IRQ: interrupt channel 0 (PINTSEL0) to GPIO 8
	SYSCON->PINTSEL[0] = BUTTON_LEFT; // PINTSEL0 is P0_8
	SYSCON->PINTSEL[1] = BUTTON_RIGHT; // PINTSEL0 is P0_8
	// Configure the Pin interrupt mode register (a.k.a ISEL) for edge-sensitive
	// on PINTSEL0. 0 is edge sensitive. 1 is level sensitive.
	PINT->ISEL = 0x00; // channel 0 bit is 0: is edge sensitive (so are the other channels)
	// Use IENR or IENF (or S/CIENF or S/CIENR) to set edge type
	// Configure Chan 0 for only falling edge detection (no rising edge detection)
	PINT->CIENR = 0b00000011; // bit 0 is 1: disable channel 0 IRQ for rising edge
	PINT->SIENF = 0b00000011; // bit 0 is 1: enable channel 0 IRQ for falling edge
	// Remove any pending or left-over interrupt flags
	PINT->IST = 0xFF; // each bit set to 1 removes any pending flag.

	// enable global interrupts & GPIO INT channel 0
	NVIC_EnableIRQ(PIN_INT0_IRQn); // GPIO interrupt
	NVIC_EnableIRQ(PIN_INT1_IRQn); // GPIO interrupt
//	__enable_irq(); // global
}

int bounced = 0;

void PIN_INT0_IRQHandler(void){
	// hour
	// was an IRQ requested for Channel 0 of GPIO INT?
	if (PINT->IST & (1<<0)){
		// remove the any IRQ flag for Channel 0 of GPIO INT
		PINT->IST = (1<<0);
		if (bounced == 0){
			bounced = 1;

			int modulo;
			if (IS_HOUR_SYSTEM_24){
				modulo = 24;
			}else{
				modulo = 12;
			}

			hour = (hour + 1) % modulo;
			hourL = hour / 10;
			hourR = hour % 10;
		}


	}else{
		asm("NOP"); // Place a breakpt here if debugging.
	}
	return;
}

void PIN_INT1_IRQHandler(void){
	// minute
	// was an IRQ requested for Channel 1 of GPIO INT?
	if (PINT->IST & (1<<1)){
		// remove the any IRQ flag for Channel 1 of GPIO INT
		PINT->IST = (1<<1);

		int modulo = 60;
		minute = (minute + 1) % modulo;
		minuteL = minute / 10;
		minuteR = minute % 10;
	}else{
		asm("NOP"); // Place a breakpt here if debugging.
	}
	return;
}


int display_segment_turn = 0;

// Interrupt Service Routine for _all_ CTIMER functions
void CTIMER0_IRQHandler(void) {

	// Test the bit for Interrupt on Match Channel 0
	if(((CTIMER0->IR)>>CTIMER_IR_MR0INT_SHIFT) & 1)
	{
		// RESET the interrupt flag by writing a ONE (1) to the bit.
		// Only concerned with Channel 0 Matching.
		CTIMER0->IR = CTIMER_IR_MR0INT_MASK;
		// toggle LED



		if (display_segment_turn == 0){
//			hourL = hour / 10; // for debug
			num_to_seven_segment_digit(hourL, 1);
		}else if (display_segment_turn == 1){
//			hourR = hour % 10;
			num_to_seven_segment_digit(hourR, 2);
		}else if (display_segment_turn == 2){
//			minuteL = minute / 10;
			num_to_seven_segment_digit(minuteL, 3);
		}else if (display_segment_turn == 3){
//			minuteR = minute % 10;
			num_to_seven_segment_digit(minuteR, 4);
		}

		display_segment_turn = (display_segment_turn + 1) % (4);

//		num_to_seven_segment_digit(my_counter, 1);
		// Manually reset the timer.
		// Set the timer counter and prescale counter back to 0
		CTIMER0->TCR |= CTIMER_TCR_CRST_MASK; // set bit 1 to 1
		CTIMER0->TCR &= ~(CTIMER_TCR_CRST_MASK); // clear bit 1 to 0

	}
	else
	{
	// all other interrupt requests for CTIMER would end up here.
		asm("NOP");
	}

//	my_counter += 1;
//	if (my_counter == 10){
//		my_counter = 0;
//	}

	return;
}

void ctimer_config(){
	// disable interrupts
//	 __disable_irq(); // turn off globally
	 NVIC_DisableIRQ(CTIMER0_IRQn); // turn off the CTIMER interrupt.
	 // ----------------------- Begin Core Clock Select -----------------------
	 // Specify that we will use the Free-Running Oscillator
	 // Set the main clock to be the FRO
	 // 0x0 is FRO; 0x1 is external clock ; 0x2 is Low pwr osc.; 0x3 is FRO_DIV
	 // Place in bits 1:0 of MAINCLKSEL.
	 SYSCON->MAINCLKSEL = (0x0<<SYSCON_MAINCLKSEL_SEL_SHIFT);
	 // Update the Main Clock
	 // Step 1. write 0 to bit 0 of this register
	 // Step 2. write 1 to bit 0 this register
	 SYSCON->MAINCLKUEN &= ~(0x1); // step 1. (Sec. 6.6.4 of manual)
	 SYSCON->MAINCLKUEN |= 0x1; // step 2. (Sec. 6.6.4 of manual)

	 // Set the FRO frequency (clock_config.h in SDK)
	  //
	  // For FRO at 9MHz: BOARD_BootClockFRO18M();
	  // 12MHz: BOARD_BootClockFRO24M();
	  // 15MHz: BOARD_BootClockFRO30M();
	  // See: Section 7.4 User Manual
	  // This is more complete than just using set_fro_frequency(24000);
	  BOARD_BootClockFRO30M(); // 30, 24 or 18 to get 15, 12 or 9 MHZ FRO.
	  // ----------------------- End of Core Clock Select -----------------------

	  // ---------------------- Begin CTIMER code (Match on Ch 0) ---------------
	   // Match and Interrupt on Ch. 0. Toggle within the ISR.
	   //
	   // Enable the CTIMER clock: SYSCON->SYSAHBCLKCTRL0 CTIMER0 clock
	   SYSCON->SYSAHBCLKCTRL0 |= (SYSCON_SYSAHBCLKCTRL0_CTIMER0_MASK);
	   // Reset the CTIMER module
	  // 1. Assert CTIMER-RST-N
	  // 2. Clear CTIMER-RST-N
	  SYSCON->PRESETCTRL0 &= ~(SYSCON_PRESETCTRL0_CTIMER0_RST_N_MASK); // Reset
	  SYSCON->PRESETCTRL0 |= (SYSCON_PRESETCTRL0_CTIMER0_RST_N_MASK); // clear the reset.
	  // Match Channel 0 and generate IRQ
	  CTIMER0->MCR |= CTIMER_IR_MR0INT_MASK; // interrupt on Ch 0 match
	  // Match at this rate for ch 0 for ISR
	  CTIMER0->MR[0] = CTIMER_MATCH_VALUE; // this should determine period
	  // prescale the counter clock from APB bus.
	  CTIMER0->PR = (CTIMER_PRESCALE-1); // PR = 0: Divide by 1 of APB clock
	  // PR = 1: Divide by 2
	  // PR = 2: Divide by 3...
	  // Enable the timer.
	  CTIMER0->TCR |= CTIMER_TCR_CEN_MASK;
	   // At this point, the TCR ENable bit gets set to 1
	   // and then, automatically, we should see the timer TCVAL value change.
	   // that should confirm that the timer is actually running.
	  // ---------------------- end of CTIMER code --------------------------
	  // enable global interrupts & the CTIMER IRQ.
	  NVIC_EnableIRQ(CTIMER0_IRQn);
//	  __enable_irq(); // global
}


void switch_matrix_config(){
	// enable switch matrix
	 SYSCON->SYSAHBCLKCTRL0 |= (SYSCON_SYSAHBCLKCTRL0_SWM_MASK);
	 SWM0->PINENABLE0 |= (1UL << 6); // disable RESETN

}

void systick_config(){
	// disable interrupts (global (all) and SysTick (specific))

	NVIC_DisableIRQ(SysTick_IRQn); // turn off the SysTick interrupt.

	// ----------------------- Begin Core Clock Select -----------------------
	// Specify that we will use the Free-Running Oscillator
	// Set the main clock to be the FRO. 0x0 is FRO; 0x1 is external clock;
	// 0x2 is Low pwr osc.; 0x3 is FRO_DIV. Place in bits 1:0 of MAINCLKSEL.
	SYSCON->MAINCLKSEL = (0x0<<SYSCON_MAINCLKSEL_SEL_SHIFT);
	// Update the Main Clock
	// Step 1. write 0 to bit 0 of this register
	// Step 2. write 1 to bit 0 this register
	SYSCON->MAINCLKUEN &= ~(0x1); // step 1. (Sec. 6.6.4 of manual)
	SYSCON->MAINCLKUEN |= 0x1; // step 2. (Sec. 6.6.4 of manual)

	SysTick_Config(OSCILLATOR_COUNT / SYSTICK_TICK_DIVIDER); // for some second ( this will be used to clear button debouncing too, every tick. )

	// Enable IRQs (SysTick & global)
	NVIC_EnableIRQ(SysTick_IRQn);

}

int systick_count = 0;

void SysTick_Handler(void){
	if (systick_count + 1 == SYSTICK_TICK_DIVIDER){
		if ((second + 1) == 60){
			if ((minute + 1) == 60){
				hour = (hour + 1) % 24;
			}
			minute = (minute + 1) % 60;
		}
		second = (second + 1) % 60;

		hourL = hour / 10;
		hourR = hour % 10;
		minuteL = minute / 10;
		minuteR = minute % 10;
	}




	systick_count = (systick_count + 1) % SYSTICK_TICK_DIVIDER;
	bounced = 0; // for debouncing
}

int main(void) {

	__disable_irq(); // turn off globally
	GPIO_config();
	ctimer_config();
	switch_matrix_config();
	systick_config();
	__enable_irq(); // global




    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

        asm("NOP");
    }
    return 0 ;
}
