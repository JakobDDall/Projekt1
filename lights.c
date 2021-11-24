/*
 * Created: 19/11/2021 12.27.41
 * Author : Genku(M.T.A.)
 */ 

#include <avr/io.h>
#include "led.h"

void initLight()
{
	//		 0b00000000
	DDRE   = 0b00001000; // (can be pin 3=OC3A 4=OC3B 5=OC3C)
	TCCR3A = 0b10000001;
	TCCR3B = 0b00000100;
	TCCR3C = 0b00000000;
	OCR3A  = 0b00000000;
	
}

void frontLightState(int state)
{
	switch (state)
	{
	case 0:
		PORTE = (PINE & ~0b00000100); //off
		break;
	case 1:
		PORTE = (PINE | 0b00000100); //on
		break;
	}
}

void backLightState(int state)
{
	// PORTE = 0b00001000
	switch (state)
	{
	case 0:
		OCR3A = 0;			//off (pwm 0%)
		break;
	case 1:
		OCR3A = 255 / 5;	//on (pwm 20%)
		break;
	case 2:
		OCR3A = 255;		//on (pwm 100%)
		break;
	}
}





