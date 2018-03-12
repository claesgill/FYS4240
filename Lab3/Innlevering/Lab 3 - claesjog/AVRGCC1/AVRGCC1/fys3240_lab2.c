//Author claesjog

#include <avr/io.h>
#include "fys3240_lcd.h"
#include "util/delay.h"
#include "fys3240_led.h"

#define POSITION_A0 0b10100100
#define POSITION_A1 0b10100000
#define POSITION_A2 0b10011100
#define POSITION_A3 0b10011000
#define POSITION_A4 0b10010100
#define POSITION_A5 0b10010000
#define POSITION_A6 0x8C //00001100

#define RATE_05HZ 0b00001011
#define RATE_1HZ 0b00001010
#define RATE_2HZ 0b00001001
#define RATE_4HZ 0b00001000

volatile long int count = 0; //Volatile - kan endres
uint8_t b_pressed;

/*
int main()
{
	oppgave1(); //Kjører test for oppgave 1
	
	//Del 2
	init_lcd();
	init_lcd_interrupts();
	init_buttons();
	
	while(1)
	{
		
	}
}*/


void oppgave1()
{
	/* Inits */
	init_lcd();
	
	//Kjører char, skriver CHAR over LCD
	lcd_write_char('C');
	_delay_ms(100);
	lcd_write_char('H');
	_delay_ms(100);
	lcd_write_char('A');
	_delay_ms(100);
	lcd_write_char('R');
	_delay_ms(100);
	lcd_clear();
	
	//Kjørere posisjon skriver POS på LCD
	lcd_write_char_pos('P', POSITION_A6);
	_delay_ms(100);
	lcd_write_char_pos('O', POSITION_A6);
	_delay_ms(100);
	lcd_write_char_pos('S', POSITION_A6);
	_delay_ms(100);
	lcd_clear();
	
	//Kjører blink med 2HZ frekvens
	lcd_set_blink(RATE_2HZ);
	blink();
	_delay_ms(500);
	lcd_set_blink(0x00);
	lcd_clear();
	
	//Printer DONE på skjermen når programmet er ferdig testet
	done();	
}

void done() //Printer DONE på LCD
{
	LCD.CTRLH = 'H';
	LCD.CTRLH = 'I';
	LCD.CTRLH = 'T';
	LCD.CTRLH = ' ';
	LCD.CTRLH = 'C';
	LCD.CTRLH = 'S';
	LCD.CTRLH = '1';
}


void blink() //Printer BLINK på LCD
{
	LCD.CTRLH = 'B';
	LCD.CTRLH = 'L';
	LCD.CTRLH = 'I';
	LCD.CTRLH = 'N';
	LCD.CTRLH = 'K';
}


void lcd_clear()
{
	LCD.CTRLA =	0b00000100; //Resetter LCD
	_delay_ms(100);
	init_lcd(); //Starter LCD på nytt
}

void lcd_set_blink(uint8_t rate)
{
	LCD.CTRLD = rate; //Setter en frekvens-rate for LCD
}

void lcd_write_char_pos(const uint8_t data, uint8_t pos) 
{
	LCD.CTRLG = pos; //Setter valgt posisjon
	LCD.CTRLH = data; //Setter valgt verdi
}


void lcd_write_char(const uint8_t data) 
{
	LCD.CTRLH = data; //Setter verdien data på LCD
}


void lcd_write_int(int i) 
{
	lcd_write_char(0x30 + i); //Putter inn verdien i med et offset tilsvarende '0'
}


void init_lcd(void)
{
	CLK.RTCCTRL = CLK_RTCEN_bm;	//Setter default klokke
	LCD.CTRLC =	0b00111111;		//Aktiverer alle pinner på LCD (ikke-jord)
	LCD.CTRLG =	0x8C;			//Starter segment og bruker 14-segment med 4 terminaler
	LCD.CTRLA =	0b10000010;		//Enabler LCD
}


//Del 2
void init_lcd_interrupts()
{
	LCD.CTRLB = 0b01110000;
	LCD.INTCTRL = 0b00011010; //Interrupt Enable Register
	PMIC.CTRL = 0b00000111;  //Setter globalt bit. Programmable Multi-level Interrupt Controller
	//LCD.INTFLAG = 0b00000001; //Setter på Interrupt Flag Register
	sei(); //Slår på interrupts
}


//Del 2
/*
ISR(LCD_INT_vect)
{
	//LCD.CTRLH = 'A';	
	lcd_callback_lab2();
}*/

//Del 2
void lcd_callback_lab2()
{	
	//Interrupt Service Routine
	b_pressed = getButtonInput();

	LCD.CTRLG = POSITION_A0; 
	
	if(b_pressed == 0b00001101) //Knapp CS1 teller oppover
	{
		count++;

		LCD.CTRLG = POSITION_A0;
		lcd_write_int(count%10); //Skriver 0-9 til posisjon A0 på display
		LCD.CTRLG = POSITION_A1;
		lcd_write_int(count%100/10); //Skriver 0-9 til posisjon A1 på display
		LCD.CTRLG = POSITION_A2;
		lcd_write_int(count%1000/100); //Skriver 0-9 til posisjon A2 på display
		LCD.CTRLG = POSITION_A3;
		lcd_write_int(count%10000/1000); //Skriver 0-9 til posisjon A3 på display
		LCD.CTRLG = POSITION_A4;
		lcd_write_int((count%100000/10000)); //Skriver 0-9 til posisjon A4 på display
		LCD.CTRLG = POSITION_A5;
		lcd_write_int((count%1000000/100000)); //Skriver 0-9 til posisjon A5 på display
		LCD.CTRLG = POSITION_A6;
		lcd_write_int((count%10000000/1000000)); //Skriver 0-9 til posisjon A6 på display
		
	}
		
	if(b_pressed == 0b00001110) //Knapp CS0 teller nedover
	{
		count--;
		
		LCD.CTRLG = POSITION_A0;
		lcd_write_int(count%10);
		LCD.CTRLG = POSITION_A1;
		lcd_write_int(count%100/10);
		LCD.CTRLG = POSITION_A2;
		lcd_write_int(count%1000/100);
		LCD.CTRLG = POSITION_A3;
		lcd_write_int(count%10000/1000);
		LCD.CTRLG = POSITION_A4;
		lcd_write_int((count%100000/10000));
		LCD.CTRLG = POSITION_A5;
		lcd_write_int((count%1000000/100000)); 
		LCD.CTRLG = POSITION_A6;
		lcd_write_int((count%10000000/1000000));
		
	}
	
}

