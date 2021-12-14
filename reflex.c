#include "reflex.h"

void initReflex(void)
{
	// INT0: rising edge
	EICRA = 0b00000000;
	EICRB = 0b00001100;	//Something wrong here. Reflex is not detected!!!
	// Enable extern interrupts INT0
	EIMSK |= 0b00100000;
	
}