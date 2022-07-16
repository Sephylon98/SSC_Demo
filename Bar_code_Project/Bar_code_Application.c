 /******************************************************************************
 *
 * Application: Smart Shopping Cart System (Graduation Project)
 *
 * File Name: Barcoode_Application.c
 *
 * Description: source file for application
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "gm65.h"
#include <avr/io.h>

int main(void){

	GM65_init(9600);
	SREG = 0x80;
	while(1);
}
