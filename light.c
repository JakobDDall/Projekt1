/*
 * Created: 19/11/2021 12.27.41
 * Author : Genku(M.T.A.)
 */ 

#include <avr/io.h>
#include "light.h"

void initLight()
{
	DDRE   = 0b00110000;
	TCCR3A = 0b00101001;
	TCCR3B = 0b00000100;
	TCCR3C = 0;
	OCR3B  = 0;
	OCR3C  = 0;
}

void frontLightState(unsigned char state)
{
	// PORTE = 0b001000000;
	
	switch (state)
	{
	case 0:
		OCR3C = 0;		//off (pwm 0%)
		break;
		
	case 1:
		OCR3C = 230;	//on  (pwm 90%)
		break;
	}
}

void backLightState(unsigned char state)
{
	// PORTE = 0b00010000;
	
	switch (state)
	{
	case 0:
		OCR3B = 0;		//off (pwm 0%)
		break;	
		
	case 1:
		OCR3B = 51;		//on  (pwm 20%)
		break;
		
	case 2:
		OCR3B = 255;	//on  (pwm 100%)
		break;
	}
}


void initTimer500ms()
{
	TCCR5A = 0b00000000; //Normal mode
	TCCR5B = 0b000000100; //Normal mode, 256 prescaler
	TCNT5 = 34286; //Overflow every 500ms
	TIMSK5 = 0b00000001; //Enable overflow interrupt	
}
