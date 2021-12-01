/*
 * car.c
 *
 * Created: 25/11/2021 09:56:01
 *  Author: jakob
 */ 
#include "car.h"

#define ACC_DELAY 5000

#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>



void initCar(void)
{
		sei();
		//-------------------------------------------- Initialisering --------------------------------------------
		
		//---------------Lyd-----------
		initUART();
		
		//--------------Motor----------
		initEngine();
		
		//---------------Lys-----------
		
		
		//--------------Refleks-----------
		initRefleks();
		
		//-------------50msTimer----------
		n50msTimer();
		
		// ---------MEGA2560 LEDs---------
		initLEDport();
		
		//--------PORTA as input--------
		DDRA = 0;
}



void startCar(void) 
{
		while ((PINA & 1) != 0)		//Bliv her indtil indtil knap 0 trykkes
		{
			UDR2 = 0;				//Sender LOW til SOMO-II. Forhindrer støj/kliklyde. Måske findes et andet fix?
		}
		//_delay_ms(500);
		for (int i = 50; i <= 100; i++){
			engineControl(i);
			_delay_us(ACC_DELAY + 1000);
		}
		//engineControl(FORWARD_SPEED);			//Start motor. Max speed
		//K?RELYS
		startLyd();
}

void reflexReactions(int nReflex)		//Hvordan bilen skal reagere på reflekser
{
	if(nReflex == 6)
	{
		//engineControl(BACKWARD_SPEED); //Bak
			for (int i = 100; i >= 50; i--){
				engineControl(i);
				_delay_us(ACC_DELAY);
			}
			engineControl(0);
			_delay_us(ACC_DELAY*5);
			for (int i = 50; i <= 100; i++){
				engineControl(-i);
				_delay_us(ACC_DELAY);
			}
		//BAKLYS
		refleksLyd();
	}
	else if(nReflex == 8)
	{
		//engineControl(FORWARD_SPEED); //Frem
		for (int i = 100; i >= 50; i--){
			engineControl(-i);
			_delay_us(ACC_DELAY);
		}
		engineControl(0);
		_delay_us(ACC_DELAY*5);
		for (int i = 50; i <= 100; i++){
			engineControl(i);
			_delay_us(ACC_DELAY);
		}
		//K?RELYS
		refleksLyd();
	}
	else if(nReflex == 11)
	{
		for (int i = 100; i >= 50; i--){
			engineControl(i);
			_delay_us(ACC_DELAY);
		}
		engineControl(0);
		
		//engineControl(0); //Stop
		//SLUK LYS
		slutLyd();
	}
	else if(nReflex > 0)
	{
		refleksLyd();
	}
}


void n50msTimer(void)	//Initialiser 50msTimer
{
	OCR4A = 49999;			//Passende compare value for et compare match hvert 50. ms, med prescaler på 8
	TCCR4A = 0b00000000;	//bit 7-2: compare output mode for channel A-B-C. Her er alle disconnected. Bit 0-1 er bit 0 og 1 af waveform generation mode.
	TCCR4B = 0b00001010;	//Bit 3-4 er bit 2 og 3 af waveform generation mode. Bit 0-2 sætter prescaler.
	TIMSK4 = 0b00000010;	//Bit 1-3: Compare match interrupt enable.
}