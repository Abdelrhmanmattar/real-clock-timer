/*
 * real clock_timer2.c
 *
 * Created: 5/18/2023 7:05:00 PM
 * Author : abdelrhman mattar
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "DIO.h"
#include "lcd.h"
#include "timer.h"
#include "7SEGMENT.h"
#include "keypad_driver.h"
#include "std_macros.h"
#define F_CPU 8000000ul
#include <util/delay.h>

volatile uint8_t second=0;
int8_t hours =0;
int8_t mint=0;
volatile char allow=1;
int main(void)
{
	DDRC = 0b00111111;
	keypad_vInit();
	seven_seg_vinit('D');
	timer2_ovf_init_();
	lcd_init();
	lcd_string("press 1 to set:");
	char x,Y;
	int8_t date[6]={0,0,0,0,0,0};
    while (1) 
    {
		x=keypad_u8check_press();
		if (x!=NOTPRESSED)
		{
			if(x=='1')
			{
				allow=0;
				PORTC=0b00111111;
				_delay_ms(250);
				Y=NOTPRESSED;
				lcd_cmd(clearscreen);
				_delay_ms(9);
				lcd_string("hours=");
				while(Y==NOTPRESSED)
				{
					Y=keypad_u8check_press();
				}
				lcd_char((char)Y);
				_delay_ms(250);
				hours=(Y-'0')*10;
				Y=NOTPRESSED;
				while(Y==NOTPRESSED)
				{
					Y=keypad_u8check_press();
				}
				lcd_char((char)Y);
				_delay_ms(250);
				hours+=(Y-'0');
				Y=NOTPRESSED;
				lcd_cmd(clearscreen);
				_delay_ms(9);
				lcd_string("min=");
				while(Y==NOTPRESSED)
				{
					Y=keypad_u8check_press();
				}
				lcd_char((char)Y);
				_delay_ms(250);
				mint=(Y-'0')*10;
				Y=NOTPRESSED;
				while(Y==NOTPRESSED)
				{
					Y=keypad_u8check_press();
				}
				lcd_char((char)Y);
				_delay_ms(250);
				mint+=(Y-'0');
				
				Y=NOTPRESSED;
				lcd_cmd(clearscreen);
				_delay_ms(9);
				lcd_string("sec=");
				while(Y==NOTPRESSED)
				{
					Y=keypad_u8check_press();
				}
				lcd_char((char)Y);
				_delay_ms(250);
				second=(Y-'0')*10;
				Y=NOTPRESSED;
				while(Y==NOTPRESSED)
				{
					Y=keypad_u8check_press();
				}
				lcd_char((char)Y);
				_delay_ms(250);
				second+=(Y-'0');
				allow=1;
			}
			else
			{
				lcd_cmd(clearscreen);
				_delay_ms(9);
				lcd_string("press wrong");
				_delay_ms(2000);
			}
		}
		if (second>59)
		{
			second=0;
			mint++;
		}
		if (mint>=60)
		{
			mint=0;
			hours++;
		}
		if (hours>=24)
		{
			hours=0;
			mint=0;
			second=0;
		}
		date[0]=second%10;
		date[1]=second/10;
		date[2]=mint%10;
		date[3]=mint/10;
		date[4]=hours%10;
		date[5]=hours/10;
		
		for (int8_t i=0;i<6;i++)
		{
			PORTC = PORTC | 0b00111111;
			CLR_BIT(PORTC,i);
			seven_seg_write('D',date[i]);
			_delay_ms(5);
		}
    }
}

ISR(TIMER2_OVF_vect)
{
	if (allow)
	{
		second++;
	}
}

