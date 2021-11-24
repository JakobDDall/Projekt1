#include "reflex.h"

void initRefleks()
{
	// INT0 og INT1: rising edge
	EICRA = 0b00001111;
	// Enable extern interrupts INT0 og INT1
	EIMSK = 0b00000011;
	
}