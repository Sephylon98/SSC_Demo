 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                                Enums                                        *
 *******************************************************************************/

typedef enum{
	Normal_mode, DoubleSpeed_mode
}UART_TransmissionSpeed;

typedef enum{
	Disabled, Enabled_even = 2, Enabled_odd
}UART_ParityBits;

typedef enum{
	one_bit, two_bits
}UART_StopBits;

typedef enum{
	five_bits, six_bits, seven_bits, eight_bits, nine_bits = 7
}UART_CharacterSize;

/*******************************************************************************
 *                               Structures                                    *
 *******************************************************************************/
typedef struct{
	uint32 baud_rate;
	UART_TransmissionSpeed speed;
	UART_ParityBits parity;
	UART_StopBits stopBits;
	UART_CharacterSize msgSize;
}UART_Config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_Config *MyConfig);

/*
 * Description :
 * Functional responsible for enabling receiver interrupt of the UART device.
 */
void UART_EnableRx_Interrupt(void);

/*
 * Description :
 * Function responsible for enabling transmitter interrupt of the UART device.
 */
void UART_EnableTx_Interrupt(void);

/*
 * Description :
 * Function responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Function responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
