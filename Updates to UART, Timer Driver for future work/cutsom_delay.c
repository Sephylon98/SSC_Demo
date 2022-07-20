 /******************************************************************************
 *
 * Module: Delay elements
 *
 * File Name: custom_delay.c
 *
 * Description: Source file for delaying functions.
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "timer.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
Timer1_ConfigType time = {prescaler_64, CTC_OCR1A_mode, Pin_Disconnected, Pin_Disconnected, 0 , 62500 , 0};

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Function responsible for setting delays. */
void SetDelay_sec_times(uint8 secs){
	uint8 counter = 0;
	uint8 i = 0;
	Timer1_init(&time);
	while(counter != (2 * secs)){
		while(!(TIFR & (1<<OCF1A)));
		TIFR |= (1<<OCF1A);
		counter ++;
		if(counter == 2 * secs){
			Timer1_deinit();
		}
	}
	counter = 0;
}
