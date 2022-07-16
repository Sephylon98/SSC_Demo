 /******************************************************************************
 *
 * Module: HX711
 *
 * File Name: hx711.c
 *
 * Description: Source file for the HX711 AVR driver
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include "hx711.h"

/*******************************************************************************
*                              Functions Definitions                           *
*******************************************************************************/

// define clock and data pin, channel, and gain factor
// channel selection is made by passing the appropriate gain: 128 or 64 for channel A, 32 for channel B
// gain: 128 or 64 for channel A; channel B works with 32 gain factor only
void HX711_init(uint8 gain)
{
    PD_SCK_SET_OUTPUT;
    DOUT_SET_INPUT;

    HX711_set_gain(gain);
}

// check if HX711 is ready
// from the datasheet: When output data is not ready for retrieval, digital output pin DOUT is high. Serial clock
// input PD_SCK should be low. When DOUT goes to low, it indicates data is ready for retrieval.
int HX711_is_ready(void)
{
    return (DOUT_INPUT & (1 << DOUT_PIN)) == 0;
}

// set the gain factor; takes effect only after a call to read()
// channel A can be set for a 128 or 64 gain; channel B has a fixed 32 gain
// depending on the parameter, the channel is also set to either A or B
void HX711_set_gain(uint8 gain)
{
	switch (gain)
	{
		case 128:		// channel A, gain factor 128
			GAIN = 1;
			break;
		case 64:		// channel A, gain factor 64
			GAIN = 3;
			break;
		case 32:		// channel B, gain factor 32
			GAIN = 2;
			break;
	}

	PD_SCK_SET_LOW;
	HX711_read();
}

// waits for the chip to be ready and returns a reading
uint32 HX711_read(void)
{
	// wait for the chip to become ready
	while (!HX711_is_ready());

    uint32 count;
    uint8 i;

    DOUT_SET_HIGH;

    _delay_us(1);

    PD_SCK_SET_LOW;
    _delay_us(1);

    count=0;
    while(DOUT_READ);
    for(i=0;i<24;i++)
    {
        PD_SCK_SET_HIGH;
        _delay_us(1);
        count=count<<1;
        PD_SCK_SET_LOW;
        _delay_us(1);
        if(DOUT_READ)
            count++;
    }
    count = count>>6;
    PD_SCK_SET_HIGH;
    _delay_us(1);
    PD_SCK_SET_LOW;
    _delay_us(1);
    count ^= 0x800000;
    return(count);
}

// returns an average reading; times = how many times to read
uint32 HX711_read_average(uint8 times)
{
	uint32 sum = 0;
	for (uint8 i = 0; i < times; i++)
	{
		sum += HX711_read();
	}
	return sum / times;
}

// returns (read_average() - OFFSET), that is the current value without the tare weight; times = how many readings to do
float64 HX711_get_value(uint8 times)
{
	return HX711_read_average(times) - OFFSET;
}

// returns get_value() divided by SCALE, that is the raw value divided by a value obtained via calibration
// times = how many readings to do
float32 HX711_get_units(uint8 times)
{
	return HX711_get_value(times) /  SCALE;
}

// set the OFFSET value for tare weight; times = how many times to read the tare value
void HX711_tare(uint8 times)
{
	float64 sum = HX711_read_average(times);
	HX711_set_offset(sum);
}

// set the SCALE value; this value is used to convert the raw data to "human readable" data (measure units)
void HX711_set_scale(float32 scale)
{
	SCALE = scale;
}

// get the current SCALE
float32 HX711_get_scale(void)
{
	return SCALE;
}

// set OFFSET, the value that's subtracted from the actual reading (tare weight)
void HX711_set_offset(float64 offset)
{
    OFFSET = offset;
}

// get the current OFFSET
float64 HX711_get_offset(void)
{
	return OFFSET;
}

// puts the chip into power down mode
void HX711_power_down(void)
{
	PD_SCK_SET_LOW;
	PD_SCK_SET_HIGH;
	_delay_us(70);
}

// wakes up the chip after power down mode
void HX711_power_up(void)
{
	PD_SCK_SET_LOW;
}
