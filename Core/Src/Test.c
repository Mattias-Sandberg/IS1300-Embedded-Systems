/**
******************************************************************************
@brief      Test Program
@file       Test.c
@author     Mattias Erik Sandberg
@version    1.0
@date       11-December-2023
@brief      Implementation of a test program for LED and button functionality
******************************************************************************
*/

#include "gpio.h"
#include "spi.h"
#include "Test.h"
#include <stdint.h>
#include "stdbool.h"
#include "Task1_functions.h"

/**
@brief      Main Test Program Function
@details    Calls functions to test button and LED functionality
*/

void Test_program(void)
{
    BUTTONtest();  							// Test the Pedestrian buttons
    // LEDtest(); 							// Test LED functionality
    // TEST_toggle_PLblue_TLgreen();    	// Continuous testing for PL Blue toggle and TL Green static.
    // TEST_toggle_PLblue_TLorange();   	// Continuous testing for PL Blue toggle and TL Orange static.
    // TEST_toggle_PLblue_TLred();      	// Continuous testing for PL Blue toggle and TL Red static.
    // TEST_walkingDelay();              	// Continuous testing for walking delay animation.

}

/**
@brief      Shifts LED Data to a Shift Register
@details    Transmits data to a shift register using SPI communication
@param      buffer: An array containing the LED data
@param      regs: Number of registers to shift
*/

void ShiftLED(uint32_t buffer[], uint8_t regs)
{
    HAL_SPI_Transmit(&hspi3, (uint8_t*)&buffer[0], regs, 100);

    HAL_Delay(1);

    HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(STCP_595_GPIO_Port, STCP_595_Pin, GPIO_PIN_RESET);
}

/**
@brief      Test Pedestrian Button Functionality
@details    Tests the two Pedestrian buttons and shifts LED data accordingly
*/

void BUTTONtest(void)
{
    uint8_t bytes = 3;
    uint32_t leds0[] = { 0x0 };                            // Turn off all LEDs
    uint32_t ledsAll[] = { 0b001111110011111100111111 };  // Turn on all LEDs

    while (1)
    {
        if (HAL_GPIO_ReadPin(GPIOB, SW7_8_Pin) == GPIO_PIN_RESET) // Test the two Pedestrian buttons
            ShiftLED(ledsAll, bytes);
        else
            ShiftLED(leds0, bytes);
        HAL_Delay(1);
    }
}

/**
@brief      Test LED Functionality
@details    Tests the functionality of different traffic light and pedestrian LEDs
*/

void LEDtest(void)
{
    uint8_t bytes = 3;
    uint32_t ledsTLE[] = { 0b000000000000000000000111 }; // Traffic light East
    uint32_t ledsTLN[] = { 0b000000000000000000111000 }; // Traffic light North
    uint32_t ledsTLS[] = { 0b000000000000011100000000 }; // Traffic light South
    uint32_t ledsTLW[] = { 0b000001110000000000000000 }; // Traffic light West
    uint32_t ledsPLN[] = { 0b000000000011100000000000 }; // Pedestrian light North
    uint32_t ledsPLW[] = { 0b001110000000000000000000 }; // Pedestrian light West

    ShiftLED(ledsTLE, bytes);
    HAL_Delay(1000);
    ShiftLED(ledsTLN, bytes);
    HAL_Delay(1000);
    ShiftLED(ledsTLS, bytes);
    HAL_Delay(1000);
    ShiftLED(ledsTLW, bytes);
    HAL_Delay(1000);
    ShiftLED(ledsPLN, bytes);
    HAL_Delay(1000);
    ShiftLED(ledsPLW, bytes);
}

/**
@brief      Continuous Testing of PL Blue toggle and TL Green and PL red static.
@details    This function provides continuous testing for toggling PL Blue and
           	keeping TL Green and PL red static. It calls the 'toggle_PLblue_TLgreen'
           	function in an infinite loop, allowing repeated testing of the toggle behavior.
*/

void TEST_toggle_PLblue_TLgreen(void)
{
	while(1)
	{
		toggle_PLblue_TLgreen();
	}
}

/**
@brief      Continuous Testing of PL Blue toggle and TL Orange and PL red static.
@details    This function provides continuous testing for toggling PL Blue and
           	keeping TL Orange and PL red static. It calls the 'toggle_PLblue_TLgreen'
           	function in an infinite loop, allowing repeated testing of the toggle behavior.
*/

void TEST_toggle_PLblue_TLorange(void)
{
	while(1)
		{
			toggle_PLblue_TLorange();
		}
}

/**
@brief      Continuous Testing of PL Blue toggle and TL Red and PL red static.
@details    This function provides continuous testing for toggling PL Blue and
           	keeping TL Red and PL red static. It calls the 'toggle_PLblue_TLgreen'
           	function in an infinite loop, allowing repeated testing of the toggle behavior.
*/

void TEST_toggle_PLblue_TLred(void)
{
	while(1)
		{
			toggle_PLblue_TLred();
		}
}

/**
@brief      Continuous Testing of Walking Delay Animation for Traffic Lights
@details    It shifts the lights in three steps:
            1. TL Red lights and PL green.
            2. TL Red lights and PL red.
            3. TL Orange lights and PL red.
            Each step is displayed for a specified duration.
*/

void TEST_walkingDelay(void)
{
	while(1)
		{
			walkingDelay();
		}
}

