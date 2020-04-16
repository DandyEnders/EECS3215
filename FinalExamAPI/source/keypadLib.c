/*
 * @Author Jinho Hwang
 * @Breif An API to connect 4x4 keypad.
 *
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC802.h"
#include "fsl_debug_console.h"

int pin_row_GPIO[4];
int pin_col_GPIO[4];


void GPIO_setup(){

}

void config_4x4_keypad(int r0, int r1, int r2, int r3, int c0, int c1, int c2, int c3){
	pin_row_GPIO[0] = r0;
	pin_row_GPIO[1] = r1;
	pin_row_GPIO[2] = r2;
	pin_row_GPIO[3] = r3;

	pin_col_GPIO[0] = c0;
	pin_col_GPIO[1] = c1;
	pin_col_GPIO[2] = c2;
	pin_col_GPIO[3] = c3;




	return;
}

