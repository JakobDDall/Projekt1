/*
 * car.c
 *
 * Created: 25/11/2021 09:56:01
 *  Author: Jakob and Frederik
 */ 
#include "car.h"


#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>



void initCar(void)
{
		sei();
		//-------------------------------------------- Initialization --------------------------------------------
		
		//---------------Sound-----------
		initUART();
		
		//--------------Motor----------
		initEngine();
		
		//---------------Light-----------
		initLight();
		
		//--------------Reflex-----------
		initReflex();
		
		//-------------50msTimer----------
		n50msTimer();
		
		// ---------MEGA2560 LEDs---------
		initLEDport();
		
		//--------PORTA as input--------
		DDRA = 0;
}



void startCar(void) 
{
		while ((PINA & 1) != 0)		//Stay until button is pressed
		{
			UDR2 = 0;				//Sens LOW to SOMO-II. Prevents noice/clicking sound. Maybe other fix?
		}
					
		frontLightState(FRONT_LIGHT_ON);
		backLightState(BACK_LIGHT_NORMAL);
		startSound();
		_delay_ms(650);	//Delay for perfect match with the start sound
		engineControl(FORWARD_SPEED); //Start motor. Max speed
}

void reflexReactions(int nReflex)		//How the car reacts on reflexes
{
	if(nReflex == 6)
	{
		engineControl(BACKWARD_SPEED); //Reverse
		backLightState(BACK_LIGHT_BRAKE); //Brakelight
		reflexSound();
	}
	else if(nReflex == 8)
	{
		engineControl(FORWARD_SPEED); //Forward
		reflexSound();
	}
	else if(nReflex == 11)
	{
		engineControl(0); //Stop
		frontLightState(FRONT_LIGHT_OFF);
		finishSound();
	}
	else if(nReflex > 0)
	{
		reflexSound();
	}
}


void n50msTimer(void)	//Initialize 50msTimer
{
	OCR4A = 49999;			//Appropriate compare value for a compare match every 50th ms, with prescaler on 8
	TCCR4A = 0b00000000;	//bit 7-2: compare output mode for channel A-B-C. All are disconnected. Bit 0-1 are bit 0 and 1 of waveform generation mode.
	TCCR4B = 0b00001010;	//Bit 3-4 are bit 2 and 3 of waveform generation mode. Bit 0-2 sets prescaler.
	TIMSK4 = 0b00000010;	//Bit 1-3: Compare match interrupt enable.
}