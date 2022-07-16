 /******************************************************************************
 *
 * Module: GM65 Bar code Reader
 *
 * File Name: gm65.c
 *
 * Description: Source file for the Bar code reader
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "gm65.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

 /*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 UDR_Read = 0; /* Global variable to read UDR */
uint8 data[Bar_code_size+Bar_code_guard_size]; /* Global array to store ASCII coming from GM65 */
uint8 Bar_code_counter = 0; /* Global variable to track size of data */

 /*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initializing the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void GM65_init(uint32 baud_rate){
	UART_init(baud_rate);
	UART_setCallBack(GM65_ProcessByte_toESP32);
}

/*
 * Description :
 * Function responsible for processing the incoming bytes
 * Send bytes to ESP32
 */
void GM65_ProcessByte_toESP32(void){
	UDR_Read = UDR;
	switch(UDR_Read){
		case'_':
		case'0':
		case'1':
		case'2':
		case'3':
		case'4':
		case'5':
		case'6':
		case'7':
		case'8':
		case'9':
			data[Bar_code_counter] = UDR_Read;
			UART_sendByte(data[Bar_code_counter]);
			Bar_code_counter++;
			break;
		}
		if(Bar_code_counter == (Bar_code_size + (Bar_code_guard_size - 1))){
			Bar_code_counter = 0;
		}
}
