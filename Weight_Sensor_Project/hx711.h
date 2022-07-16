 /******************************************************************************
 *
 * Module: HX711
 *
 * File Name: hx711.h
 *
 * Description: Header file for the HX711 AVR driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/
#ifndef HX711_H_
#define HX711_H_

#include "std_types.h"
#include <avr/io.h>
#include <util/delay.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PD_SCK_PORT         PORTD	                        // Power Down and Serial Clock Input Port
#define PD_SCK_DDR          DDRD                            // Power Down and Serial Clock DDR
#define PD_SCK_PIN          PD5                             // Power Down and Serial Clock Pin
#define DOUT_PORT           PORTD                           // Serial Data Output Port
#define DOUT_DDR            DDRD                            // Serial Data Output DDR
#define DOUT_INPUT          PIND                            // Serial Data Output Input
#define DOUT_PIN            PD6 		                    // Serial Data Output Pin
#define DOUT_READ           (DOUT_INPUT & (1<<DOUT_PIN))    // Serial Data Output Read Pin

/*******************************************************************************
*                              Global Variables                                *
*******************************************************************************/

uint8 GAIN;		                // amplification factor
float64 OFFSET;	                // used for tare weight
float32 SCALE;	                // used to return weight in grams, kg, ounces, whatever

/*******************************************************************************
*                            Function-Like Macros                              *
*******************************************************************************/

#define DOUT_SET_HIGH       DOUT_PORT |= (1<<DOUT_PIN)
#define DOUT_SET_LOW        DOUT_PORT &= ~(1<<DOUT_PIN)
#define DOUT_SET_INPUT      DOUT_DDR &= ~(1<<DOUT_PIN); DOUT_SET_HIGH
#define DOUT_SET_OUTPUT     DOUT_DDR |= (1<<DOUT_PIN); DOUT_SET_LOW
#define PD_SCK_SET_OUTPUT   PD_SCK_DDR |= (1<<PD_SCK_PIN)
#define PD_SCK_SET_HIGH     PD_SCK_PORT |= (1<<PD_SCK_PIN)
#define PD_SCK_SET_LOW      PD_SCK_PORT &= ~(1<<PD_SCK_PIN)

/*******************************************************************************
*                              Functions Prototypes                           *
*******************************************************************************/

// define clock and data pin, channel, and gain factor
// channel selection is made by passing the appropriate gain: 128 or 64 for channel A, 32 for channel B
// gain: 128 or 64 for channel A; channel B works with 32 gain factor only
void HX711_init(uint8 gain);

// check if HX711 is ready
// from the datasheet: When output data is not ready for retrieval, digital output pin DOUT is high. Serial clock
// input PD_SCK should be low. When DOUT goes to low, it indicates data is ready for retrieval.
int HX711_is_ready(void);

// set the gain factor; takes effect only after a call to read()
// channel A can be set for a 128 or 64 gain; channel B has a fixed 32 gain
// depending on the parameter, the channel is also set to either A or B
void HX711_set_gain(uint8 gain);

// waits for the chip to be ready and returns a reading
uint32 HX711_read(void);

// returns an average reading; times = how many times to read
uint32 HX711_read_average(uint8 times);

// returns (read_average() - OFFSET), that is the current value without the tare weight; times = how many readings to do
float64 HX711_get_value(uint8 times);

// returns get_value() divided by SCALE, that is the raw value divided by a value obtained via calibration
// times = how many readings to do
float32 HX711_get_units(uint8 times);

// set the OFFSET value for tare weight; times = how many times to read the tare value
void HX711_tare(uint8 times);

// set the SCALE value; this value is used to convert the raw data to "human readable" data (measure units)
void HX711_set_scale(float32 scale);

// get the current SCALE
float32 HX711_get_scale(void);

// set OFFSET, the value that's subtracted from the actual reading (tare weight)
void HX711_set_offset(float64 offset);

// get the current OFFSET
float64 HX711_get_offset(void);

// puts the chip into power down mode
void HX711_power_down(void);

// wakes up the chip after power down mode
void HX711_power_up(void);

#endif /* HX711_H_ */
