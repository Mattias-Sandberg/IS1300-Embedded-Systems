#include "main.h"
#include "usart.h"
#include "gpio.h"
#include <stdbool.h>

/** ******************************************************************************
@brief	Pigpong, functions for Pingpong-program
@file	pingpong_functions.c
@author	Mattias Sandberg & Elis Gunnarsson
@version 1.0
@date 07-Nov-2023
@brief Functions and structures for program Pingpong ****************************************************************************** */


// We can select wich Test we want to display.
void Test_program(void) {
    // Test_Led();
	//Test_show_points();
	//Test_buttons();
	//Test_blink();
}


// Test function for the Blink function, Makes the The leds blink multiple time depending on the magnitude of the loop
void Test_blink(void)
{
	int8_t i;
	for(i = 0; i < 7; i++)
	{
		Blink_LEDs();
	}
}






// from PDF
void Test_Led(void) {
int8_t Lednr;
/* Loop checking that all leds can be turned on*/
for (Lednr=1; Lednr<= 8; Lednr++) {
	Led_on(Lednr);
	HAL_Delay(500);
}
Led_on(9); // Turn off led 8 HAL_Delay(1000); // 1000 ms return;
}





// Test for the Point system, Hardcoded to Left=1 points and Right=2 points.
void Test_show_points(void) {
	Show_points(1,2);
	return;
}








// From PDF.
void Test_buttons(void) {
	uint8_t j;

	/* Checking buttons */
	j=4;
	Led_on(j); // Light on
	while (j<9 && j>0){
		if (L_hit() == true) { // Wait for left button hit
			j++; // next led to the right
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( L_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
		}
		if ( R_hit() == true ){ // Wait for right button hit
			j--; // next led to the left
			Led_on(j); // Light on
			HAL_Delay(100); // 100 ms
			while ( R_hit() == true ); // Wait for button release
			HAL_Delay(100); // 100 ms
			if (j<1) j=0; // Start again from left
		}
	}
	return;
}
