/* 
Author       : Bent Furevik/Snorre Bjørnstad
Company      : University of Oslo
File name    : fys3240_lab1.h
Date         : 23.12.2011
Revised		 : 02.02.2015
Project      : FYS3240 Lab1 
Function     : Code for a microcontrollerprogram flashing leds according to pushbuttons 
*/


#include "fys3240_led.h"


void init_32M_clock(void)
{
	/* Your code here! */
}

void put_on_leds(uint8_t value)
{
	/* Your code here! */
}

uint8_t getButtonInput(void)
{
	/* Your code here. Remember to ignore the 4 most significant bits since the buttons are on the 4 LSB. */
}

void flash_on_keypress(void)
{
	put_on_leds(getButtonInput());
}

void led_counter(void)
{
	while(1) {
		/* Code for counter here */
		put_on_leds(count);
		/* remember delay */
	}
}

void init_buttons(void)
{
	/* Initialize configuration of buttons */
}

void init_leds(void)
{
	/* Initialize configuration of LEDs */
	PORTB.DIR = 0b11110000; //Deklarerer som inngang
	
}

void init_buttons_and_leds(void)
{
	init_buttons();
	init_leds();
}