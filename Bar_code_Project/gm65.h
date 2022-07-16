 /******************************************************************************
 *
 * Module: GM65 Bar code Reader
 *
 * File Name: gm65.h
 *
 * Description: Header file for the Bar code reader
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#ifndef GM65_H_
#define GM65_H_

#include "std_types.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/
#define Bar_code_size 9
#define Bar_code_guard_size 2

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
void GM65_init(uint32 baud_rate);

/*
 * Description :
 * Function responsible for processing the incoming bytes
 * Send bytes to ESP32
 */
void GM65_ProcessByte_toESP32(void);

#endif /* GM65_H_ */
