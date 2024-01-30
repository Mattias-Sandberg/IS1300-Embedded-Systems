/**
******************************************************************************
@brief      Functions for the main Task1.c state machine to utilize
@file       Task1_functions.c
@author     Mattias Erik Sandberg
@version    1.0
@date       11-December-2023
@brief      Implementation of control functions for pedestrian light and
            traffic light, and ability to make PL blue toggle whit toggleFreq
******************************************************************************
*/


#include "gpio.h"
#include "spi.h"
#include "Test.h"
#include <stdint.h>
#include "stdbool.h"
#include "main.h"

/**
@brief      Toggles Pedestrian Light Blue and Keeps Traffic Light Green Static
@details    Toggles the pedestrian light blue while keeping the traffic light
            green and pedestrian red static.
*/

void toggle_PLblue_TLgreen(void)
{
    int toggleFreq = 500; // 500 milliseconds
    int totalTime = 5000; // 5000 milliseconds

    uint8_t bytes = 3;
    uint32_t ledsTLGPLR[] = {0b000000000000110000100000};       // TL Green, PL Red
    uint32_t ledsTLGPLRB[] = {0b000000000010110000100000};     	// TL Green, PL Red & Blue
    uint8_t status = 0;
    uint32_t startTime = HAL_GetTick(); 	// Get the current time in milliseconds

    while ((HAL_GetTick() - startTime) < totalTime)		// Check elapsed time
    {
        status = !status;
        if (status)
        {
            ShiftLED(ledsTLGPLR, bytes);
        } else
        {
            ShiftLED(ledsTLGPLRB, bytes);
        }
        HAL_Delay(toggleFreq);
    }
}

/**
@brief      Toggles Pedestrian Light Blue and Keeps Traffic Light Orange Static
@details    Toggles the pedestrian light blue while keeping the traffic light
            orange and pedestrian red static.
*/

void toggle_PLblue_TLorange(void)
{
    int toggleFreq = 500; //500 milliseconds
    int totalTime = 3000; // 3000 milliseconds

    uint8_t bytes = 3;
    uint32_t ledsTLOPLR[] = {0b000000000000101000010000};          // TL Orange lights and PL red
    uint32_t ledsTLOPLRB[] = {0b000000000010101000010000};     // Both Orange lights and PL red and blue lights
    uint8_t status = 0;
    uint32_t startTime = HAL_GetTick(); // Get the current time in milliseconds

    while ((HAL_GetTick() - startTime) < totalTime) // Check elapsed time
    {
        status = !status;
        if (status)
        {
            ShiftLED(ledsTLOPLR, bytes);
        } else
        {
            ShiftLED(ledsTLOPLRB, bytes);
        }
        HAL_Delay(toggleFreq);
    }
}

/**
@brief      Toggles Pedestrian Light Blue and Keeps Traffic Light Red Static
@details    Toggles the pedestrian light blue while keeping the traffic light
            orange and pedestrian red static.
*/

void toggle_PLblue_TLred(void)
{
    int toggleFreq = 500; // 500 milliseconds
    int totalTime = 3000; // 3000 milliseconds

    uint8_t bytes = 3;
    uint32_t ledsTLRPLR[] = {0b000000000000100100001000};      // TL Red lights and PL Red
    uint32_t ledsTLGPLRB[] = {0b000000000010100100001000};     // Both Red lights and PL red and blue lights
    uint8_t status = 0;
    uint32_t startTime = HAL_GetTick(); // Get the current time in milliseconds

    while ((HAL_GetTick() - startTime) < totalTime) // Check elapsed time
    {
        status = !status;
        if (status)
        {
            ShiftLED(ledsTLRPLR, bytes);
        } else
        {
            ShiftLED(ledsTLGPLRB, bytes);
        }
        HAL_Delay(toggleFreq);
    }
}

/**
@brief      Implements a Walking Delay Animation for Traffic Lights
@details    The function simulates a walking delay animation for traffic lights.
            It shifts the lights in three steps:
            1. TL Red lights and PL green.
            2. TL Red lights and PL red.
            3. TL Orange lights and PL red.
            Each step is displayed for a specified duration.
*/

void walkingDelay(void)
{
    int totalTime = 7000; // 7000 milliseconds
    int firstShiftDuration = 3000; // Duration of the first ShiftLED operation
    int secondShiftDuration = 2000; // Duration of the second ShiftLED operation
    int thirdShiftDuration = totalTime - firstShiftDuration - secondShiftDuration; // Remaining time for the third ShiftLED operation

    uint8_t bytes = 3;
    uint32_t ledsTLRPLG[] = {0b000000000001000100001000}; // TL red lights and PL green
    uint32_t ledsTLRPLR[] = {0b000000000000100100001000}; // TL red lights and PL red
    uint32_t ledsTLOPLR[] = {0b000000000000101000010000}; // TL Orange lights and PL red
    uint32_t startTime = HAL_GetTick(); // Get the current time in milliseconds

    // First ShiftLED operation
    while ((HAL_GetTick() - startTime) < firstShiftDuration)
    {
        ShiftLED(ledsTLRPLG, bytes);
    }
    startTime = HAL_GetTick(); // Reset the start time for the second ShiftLED operation

    // Second ShiftLED operation
    while ((HAL_GetTick() - startTime) < secondShiftDuration) {
        ShiftLED(ledsTLRPLR, bytes);
    }
    startTime = HAL_GetTick(); // Reset the start time for the third ShiftLED operation

    // Third ShiftLED operation
    while ((HAL_GetTick() - startTime) < thirdShiftDuration) {
        ShiftLED(ledsTLOPLR, bytes);
    }
}

