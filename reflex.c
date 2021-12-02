#include "reflex.h"

void initReflex()
{
	// INT0: rising edge
	EICRA = 0b00000011;
	// Enable extern interrupts INT0
	EIMSK = 0b00000001;
	
}