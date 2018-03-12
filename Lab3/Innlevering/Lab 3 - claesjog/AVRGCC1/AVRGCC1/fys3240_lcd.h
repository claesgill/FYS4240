/* 
Author       : Bent Furevik
Company      : University of Oslo
File name    : fys3240_lcd.c
Date         : 23.12.2011
Project      : FYS3240 Lab1
Function     : Precode for the methods used to interface the LCD on the XMEGA-board
*/
//#define F_CPU 32000000
//#include "fys3240_led.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//! 14-segment with 4 commons terminals, start segment
#define START_14SEG_4C 12

//Definer disse makroene:
#define LCD_HOME  //Setter segmentadressen til begynnelsen av linjen 
#define LCD_CLEAR  //BIT i et av registrene
#define LCD_BACKLIGHT_TOGGLE (PORTE.OUT ^= (1 << 5))


void lcd_set_blink(uint8_t rate);
void lcd_write_char_pos(const uint8_t data, uint8_t pos) ;
void lcd_write_char(const uint8_t data) ;
void lcd_write_int(int i) ;
void init_lcd(void);
