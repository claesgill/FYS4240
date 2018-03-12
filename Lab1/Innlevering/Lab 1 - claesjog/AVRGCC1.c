/*
 * AVRGCC1.c
 *
 * Created: 12.02.2018 10:35:31
 *  Author: claesjog
 */ 

#include <avr/io.h>
#include "util/delay.h"

int main(void)
{
	init_32M_clock(); //Inisialiserer 32MHz klokke
	init_buttons_and_leds(); //Inisialiserer knapper og leds
	
    led_counter(); //Sjekker etter knapper om den skal telle opp eller ned

	uint8_t bryt;
	
	while(bryt != 0b00000111)
	{		
		_delay_ms(200);
		flash_on_keypress();
		bryt = getButtonInput();
		
	}
	
	while(1)
	{
		put_on_leds(0b00000111); //Siden den bit-shifter mot venstre må led-bitsene settes på samme måte som buttons-bit
	}
	
}

