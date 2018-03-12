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
#include "util/delay.h"

void init_32M_clock(void)
{	
	OSC.CTRL = 0b00000010;
	
	while(OSC.STATUS & 0b00010 != 0b00010); //Masker status og fjerner bit vi ikke er interessert i. While for å kjøre helt til vi får flag.
	
	CCP = CCP_IOREG_gc; //Låser opp mux
	
	CLK.CTRL = CLK_SCLKSEL_RC32K_gc; //Endrer inngang
	//Låses automatisk
}


void put_on_leds(uint8_t value)
{
	PORTB_OUT = value << 4;	//Shifter 4 bit mot venstre for å lese av riktige bits
}

uint8_t getButtonInput(void)
{
	uint8_t brytere;
	brytere = PORTE_IN & 0b00001111; //Masker for å oppnå ønsket bits
	return brytere; //Returnerer knappen vi trykket på
}


void flash_on_keypress(void)
{
	put_on_leds(getButtonInput());
}

void led_counter(void)
{
	uint8_t count = 0;
	uint8_t b_pressed;
	
	while(1) 
	{	
		b_pressed = getButtonInput(); 
		
		if(b_pressed == 0b00001110) //Knapp CS0 teller oppover
		{
			_delay_ms(25); //Delay på 25ms
			count++;
		}
		
		if(b_pressed == 0b00001101) //Knapp CS1 teller nedover
		{
			--count;
			_delay_ms(25);
		}
		
		if(b_pressed == 0b00000111) //Knapp CS3 avbryter løkka
		{
			break;
		}
		
		put_on_leds(~count); //Slår av/på LED, ~ gjør om til binær telling
		_delay_ms(25);
	}
}

void init_buttons(void)
{
	/* Initialize configuration of buttons */
	PORTE.DIR = 0b00000000; //Deklarerer som innganger
	PORTE.PIN0CTRL = 0b00011000; //Gjør pinnene til pull-up
	PORTE.PIN1CTRL = 0b00011000; 
	PORTE.PIN2CTRL = 0b00011000;
	PORTE.PIN3CTRL = 0b00011000;
}

void init_leds(void)
{
	/* Initialize configuration of LEDs */
	PORTB.DIR = 0b11110000; //Deklarerer 
}

void init_buttons_and_leds(void)
{
	init_buttons();
	init_leds();
}