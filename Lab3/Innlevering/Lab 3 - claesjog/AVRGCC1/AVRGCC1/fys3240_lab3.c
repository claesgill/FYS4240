/* 
Author       : Bent Furevik
Company      : University of Oslo
File name    : fys3240_lab3.c
Date         : 23.12.2011
Project      : FYS3240 Lab3
Function     : Precode for a microcontrollerprogram interfacing the ADC
*/



#include "fys3240_adcb.h"
#include "fys3240_lcd.h"
#include "fys3240_led.h"
#include <util/delay.h>

#define POSITION_A0 0b10100100
#define POSITION_A1 0b10100000
#define POSITION_A2 0b10011100
#define POSITION_A3 0b10011000
#define POSITION_A4 0b10010100
#define POSITION_A5 0b10010000
#define POSITION_A6 0x8C //00001100


/* ISR's here */
ISR(ADCB_CH0_vect)
{
	adcb_callback();
}


ISR(LCD_INT_vect)
{	
	lcd_for_adc_callback();
}


volatile uint8_t val;
uint8_t b_pressed;
int run = 1;

int main(void)
{
	/* Test application here. */
	ADCBInit();
	init_buttons();
	init_lcd();
	init_lcd_interrupts();
	
    while(1)
	{
	
	}
}



void ADCBInit(void) 
{
	/* Code for initializing ADCB here */
	ADCB.CH0.CTRL = 0b00000001;		 //Singelended
	ADCB.CTRLA = 0b01;				 //Enabler ADC
	ADCB.CTRLB = 0b00001100;		 //Setter Freerunmode - kjøres kontinuerlig
	ADCB.CH0.MUXCTRL = 0b00001000;	 //Konfigurerer PIN1, enabler potentiometeret
	ADCB.PRESCALER = 0b00000100;	 //Setter klokke til 64
	ADCB.REFCTRL = 0b00010001;		 //Setter TEMPERATUR sensor og setter Vcc til 1.1V
	ADCB.CH0.INTCTRL = 0b00000011;	 //	
	ADCB.CTRLA = 0b00000101;		 //Starter 
	
}

void adcb_callback(void)
{
	/* Code for the callback function for adc-interrupts here. */
	b_pressed = getButtonInput();
	
	if(run == 1)
	{
		lcd_write_char_pos('0', POSITION_A0);
		lcd_write_char_pos('0', POSITION_A1);
		lcd_write_char_pos('0', POSITION_A2);
	}	
	
	if(b_pressed == 0b00001110) //Knapp CS0, potentiometer
	{
		lcd_write_char_pos('P', POSITION_A6);
		lcd_write_char_pos('O', POSITION_A5);
		lcd_write_char_pos('S', POSITION_A4);
		ADCB.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN1_gc;
		run = 0;
	}
	
	if(b_pressed == 0b00001101) //Knapp CS1, lyssensor
	{
		lcd_write_char_pos('L', POSITION_A6);
		lcd_write_char_pos('Y', POSITION_A5);
		lcd_write_char_pos('S', POSITION_A4);
		ADCB.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN2_gc;
		run = 0;
	}	
	
	if(b_pressed == 0b00001011) //Knapp CS2, temperatur sensor
	{
		lcd_write_char_pos('T', POSITION_A6);
		lcd_write_char_pos('M', POSITION_A5);
		lcd_write_char_pos('P', POSITION_A4);
		ADCB.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN0_gc;
		run = 0;
	}	

	val = ADCB_CH0_RES;	//Setter 
}

void lcd_for_adc_callback(void)
{
	/* Code for the callback function for lcd-interrupts here. */
	show_value(val);
}

static uint8_t conv_ascii(uint8_t val)
{
	/* Make this return an ascii-character of the number. */
	return 0;
}

void show_value(uint8_t val){
	/* Show value on LCD-screen. */
	
	LCD.CTRLG = POSITION_A0;
	lcd_write_int(val%10); //Skriver 0-9 til posisjon A0 på display
	LCD.CTRLG = POSITION_A1;
	lcd_write_int(val%100/10); //Skriver 0-9 til posisjon A1 på display
	LCD.CTRLG = POSITION_A2;
	lcd_write_int(val%1000/100); //Skriver 0-9 til posisjon A2 på display
}