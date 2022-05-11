/*
 * Created: 19/11/2021 12.27.41
 * Author : Genku(M.T.A.)
 */ 

#include <avr/io.h>
#include "light.h"

void initLight(void)
{
	DDRE   = 0b00011010;
	TCCR3A = 0b10100001;	
	TCCR3B = 0b00000100;
	TCCR3C = 0;
	OCR3A  = 0;
	OCR3B  = 0;
}

void frontLightState(unsigned char state)
{
	
	switch (state)
	{
	case 0:
		OCR3B = 0;		//off (pwm 0%)
		break;
		
	case 1:
		OCR3B = 230;	//on  (pwm 90%)
		break;
	}
}

void backLightState(unsigned char state)
{
	// PORTE = 0b00010000;
	
	switch (state)
	{
	case 0:
		OCR3A = 0;		//off (pwm 0%)
		break;	
		
	case 1:
		OCR3A = 51;		//on  (pwm 20%)
		break;
		
	case 2:
		OCR3A = 255;	//on  (pwm 100%)
		break;
	}
}


