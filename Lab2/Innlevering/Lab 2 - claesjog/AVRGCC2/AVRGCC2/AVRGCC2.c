/*
 * AVRGCC2.c
 *
 * Created: 19.02.2018 10:16:51
 *  Author: claesjog
 */ 

#include <avr/io.h>
#define POSITION 0x8C
#define RATE_05HZ 0b00001011
#define RATE_1HZ 0b00001010
#define RATE_2HZ 0b00001001
#define RATE_4HZ 0b00001000
/*
int main(void)
{
	init_lcd();
	//uint8_t c = '9';
	//lcd_write_char(3);
	//lcd_write_char_pos(c, POSITION);
	//lcd_set_blink(RATE_1HZ);
	lcd_write_int(3);
	
	
    while(1)
    {
        //TODO:: Please write your application code 
	}
}*/