/**
******************************************************************************
@brief 		Task1 - Traffic Light Control Program
@file 		Task1.c
@author 		Mattias Erik Sandberg
@version 1.0
@date 		11-December-2023
@brief 		Implementation of a state-machine controlling a traffic light
******************************************************************************
*/

#include "gpio.h"
#include "spi.h"
#include "Test.h"
#include <stdint.h>
#include "stdbool.h"
#include "main.h"
#include "Task1_functions.h"
#include "Task1.h"

// Enumeration for traffic light states
typedef enum {
    START,           // Initial state
    TL_TO_ORANGE,    // Transition from TL Green to Orange
    TL_TO_RED,       // Transition from TL Orange to Red
    WALKING_DELAY    // Delay for pedestrians to cross
} states;

// Static variables to track current and next states
static states State, NextState;

/**
@brief      Main Task1 function
@details    Implements a state-machine controlling the traffic light
*/

void Task1(void)
{
    State = START;     // Initialize state to START
    NextState = START;

    /* Infinite loop */
    while (1)
    {
        State = NextState;  // Update current state

        switch (State)       // State machine
        {
        case START:
        {
            uint8_t bytes = 3;
            uint32_t ledsTLGPLR[] = {0b000000000000110000100000}; // TL Green and PL Red

            while (1)
            {
                if (HAL_GPIO_ReadPin(GPIOB, SW7_8_Pin) == GPIO_PIN_RESET)
                {
                	toggle_PLblue_TLgreen();	// Call the function to toggle blue while TL Green

                    NextState = TL_TO_ORANGE;  // Transition to the TL_TO_ORANGE state
                    break;  // Exit the while loop
                }
                else
                {
                    ShiftLED(ledsTLGPLR, bytes); // Start with Traffic light green and pedestrian light red
                }
            }
        }
        	break;
        case TL_TO_ORANGE:
        	while (1)
        	         {
        			toggle_PLblue_TLorange();	// Call the function to toggle blue while TL Orange

        	             NextState = TL_TO_RED;  // Transition to the TL_TO_RED state
        	             break;  // Exit the while loop
        	         }
            break;
        case TL_TO_RED:
                    while (1)
                    {
                    	toggle_PLblue_TLred();  // Call the function to toggle blue while TL Red

                        NextState = WALKING_DELAY;  // Transition to the WALKING_DELAY state
                        break;  // Exit the while loop
                    }
            break;
        case WALKING_DELAY:
        			while (1)
        			{
        				walkingDelay();  // Call the function for pedestrian crossing delay

        				NextState = START;  // Transition to the START state and repeat
        				break;  // Exit the while loop
        			}
        	break;
        }
    }
}
