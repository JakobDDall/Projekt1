#include "reflex.h"

void initReflex(void)
{
	// INT0: rising edge
	EICRA = 0b00000000;
	EICRB = 0b00001100;	// Enable extern interrupts INT5
	EIMSK |= 0b00100000;
	
}