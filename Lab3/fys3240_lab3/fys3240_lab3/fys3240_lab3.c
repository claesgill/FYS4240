/* 
Author       : Bent Furevik
Company      : University of Oslo
File name    : fys3240_lab3.c
Date         : 23.12.2011
Project      : FYS3240 Lab3
Function     : Precode for a microcontrollerprogram interfacing the ADC
*/



#include "fys3240_adcb.h"


/* ISR's here */

volatile uint8_t val;

int main(void)
{
	/* Test application here. */
    while(1){
	
	}
}



void ADCBInit(void) 
{
	/* Code for initializing ADCB here */
}

void adcb_callback(void)
{
	/* Code for the callback function for adc-interrupts here. */
}

void lcd_for_adc_callback(void)
{
	/* Code for the callback function for lcd-interrupts here. */
}

static uint8_t conv_ascii(uint8_t val)
{
	/* Make this return an ascii-character of the number. */
	return 0;
}

void show_value(uint8_t val){
	/* Show value on LCD-screen. */
}