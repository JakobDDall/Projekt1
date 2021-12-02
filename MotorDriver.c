/*
 * MotorDriver.c
 *
 * Created: 04-11-2021 10:58:45
 *  Author: Nephim
 */ 

#include <avr/io.h>

void initEngine(void){
	DDRB = 0xFF; //port B as output
	PORTB = 0; //clear
	TCCR1A = 0b10100011; //PIN A og PIN B
	TCCR1B = 0b00000010; // 1kHz
	
}


void engineControl(int Speed){
	
	if(Speed > 0){
		OCR1B = 0;
		OCR1A = (Speed * 10) + 23;
	} else if (Speed < 0){
		OCR1A = 0;
		OCR1B = (Speed * -10) + 23;
	} else if (Speed == 0){
		OCR1A = 0;
		OCR1B = 0;
	}
	
}
