 /******************************************************************************
 *
 * Application: Smart Shopping Cart System (Graduation Project)
 *
 * File Name: weight_sensor_application.c
 *
 * Description: Source file for application
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "lcd.h"
#include "hx711.h"

/* Global variable to store weight reading */
uint32 Weight = 0;

/* Scale used for calibration process */
#define scale 3.275132275

//3.386243386
//3.275132275

int main(void){

	LCD_init();
	HX711_init(128);
	HX711_set_offset(75);
	LCD_displayString("Weight in grams:");
	LCD_moveCursor(1,0);

	while(1){
		Weight = HX711_get_value(50);
		Weight = (int)Weight/scale;
		if(Weight >= 0 && Weight < 10){
			LCD_intgerToString(Weight);
			LCD_displayCharacter(' ');
			LCD_displayCharacter(' ');
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,0);
		}
		else if(Weight >= 10 && Weight <100){
			LCD_intgerToString(Weight);
			LCD_displayCharacter(' ');
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,0);
		}
		else if(Weight >= 100 && Weight <1000){
			LCD_intgerToString(Weight);
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,0);
		}
		else if(Weight >= 1000 && Weight < 10000){
			Weight = ceil(Weight / 1000);
			LCD_intgerToString(Weight);
			LCD_moveCursor(1,0);
		}
		else{
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("OVERLOAD");
			_delay_ms(500);
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Weight in grams:");
			LCD_moveCursor(1,0);
		}
	}
}




