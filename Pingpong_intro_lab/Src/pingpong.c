#include "main.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include "Pingpong.h"

/** ******************************************************************************
@brief	Pigpong, functions for Pingpong-program
@file	pingpong_functions.c
@author	Mattias Sandberg & Elis Gunnarsson
@version 1.0
@date 07-Nov-2023
@brief Functions and structures for program Pingpong ****************************************************************************** */


/* Define states for state machine */

typedef enum{
	Start,
	MoveRight,
	MoveLeft,
	ShowScore
} states;

static states State, NextState;

void Pingpong(void)
{
	bool ButtonPressed; // To remember that button is pressed
	bool R_player, L_player;

	uint32_t Varv, Speed; // Ball speed
	uint8_t Led, R_score, L_score; // LED nr

	State= Start; // Initiate State to Start
	NextState = Start;

	// Initiate of variables.
	Speed = 500000; // Number of loops
	ButtonPressed = false; // False to be able to change to True if pushed.
	L_score = 0;	// Left Player starting score
	R_score = 0;	// Right Player starting score
	L_player = true;	// Boolean for left player to serve
	R_player = true;	// Boolean for Right player to serve



	/* Infinite loop */
	while (1)
	{
		State = NextState;
		switch (State) // State machine
		{
		case Start:
		{
			Led_on(0); // Turn off all LEDs
			if ( L_hit() == true && L_player == true) // L serve
			{
				L_player = false;   // left player cant serve next time if served previous
				R_player = true;	// Right player can serve
				Led = 1;			// Start on Led 1
				NextState= MoveRight;	// Jump to case MoveRight
				while ( L_hit() == true ); // wait until button is released
			} else if ( R_hit() == true && R_player == true ) // R serve
			{
				R_player = false;	// Right player cant serve next time if served previous
				L_player = true;	// Left player can serve
				Led = 8;			// Start on Led 8
				NextState= MoveLeft;	// Jump to case MoveLeft
				while ( R_hit() == true ); // wait until button is released
			}
			else
				NextState = Start; // Stay in Start state
		}
			break;
		case MoveRight:
		{
			Led_on(Led);
			Varv = Speed;
			while( Varv != 0 )
			{
				if ( R_hit() ) ButtonPressed = true; // R hit
				Varv--;
			}
			if ( ButtonPressed ) // R pressed
			{
				if ( Led == 8 ) // and LED8 active
				{
					NextState = MoveLeft; // return ball
					Speed -= 75000;		// Increase the ball speed, Higher number = faster game
					Led=7;
				}
				else
				{
					L_score++;
					Speed = 500000;			// Reset Speed if player gets a point
					NextState = ShowScore; // hit to early
				}
			}
			else
			{
				if ( Led == 9 )  // no hit or to late
				{
					L_score++;
					Speed = 500000;			// Reset Speed if player gets a point
					NextState = ShowScore;
				}
				else
					NextState = MoveRight; // ball continues to move right
			}
			if ( !ButtonPressed ) Led++; // prepare to turn next LED on
			ButtonPressed=false;
		}
		break;

		case MoveLeft:
		{
			Led_on(Led);
			Varv = Speed;
			while(Varv != 0)
			{
				if ( L_hit() ) ButtonPressed = true; // L hit
				Varv--;
			}
			if ( ButtonPressed ) // L pressed
			{
				if ( Led == 1 ) // and LED1 active
				{
					NextState=MoveRight; // return ball
					Speed -= 75000;     // Increase the ball speed, Higher number = faster game
					Led=2;
				}
				else
				{
					R_score++;
					Speed = 500000;			// Reset Speed if player gets a point
					NextState = ShowScore; // hit to early
				}
			}
			else
			{
				if ( Led == 0 ) // no hit or to late
				{
					R_score++;
					Speed = 500000;	// Reset Speed if player gets a point
					NextState = ShowScore;
				}
				else
					NextState = MoveLeft; // ball continues to move left
			}
			if ( !ButtonPressed ) Led--; // prepare to turn next LED on
			ButtonPressed=false;
		}
		break;
		case ShowScore:
		{
			// Call on function to make the LEDs blink if a player fails.
			Blink_LEDs();

			// Game goes on until one player reach 4 points (Score goes from index 0 to 3)
			if(L_score < 4 && R_score < 4 )
			{
			Show_points(L_score, R_score);				// We display the score for 1000ms
				HAL_Delay(1000);
			NextState = Start;							// Go back to Start state for a new round
			}
			else if( L_score == 4 || R_score == 4)		// The game Resets and one player have won
			{
				Show_points(L_score, R_score);			// Display the players Final scores
				HAL_Delay(5000);						// Display the final scores for 5sec as specified

				R_score = 0;							// Right score reset
				L_score = 0;							// Left score reset

				// This makes it possible to choose wich one to start the game.
				R_player = true;						// Turn to serve reset
				L_player = true;						// Turn to serve reset

				NextState = Start;						// Go back to Start state for a completely new game
			}
		}
		break;
		default:
		break;
		}
	}
 } // End of function Pingpong
