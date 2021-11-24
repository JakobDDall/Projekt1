/*
 * Samlet_projekt.cpp
 *
 * Created: 22/11/2021 12:46:26
 * Author : jakob
 */ 

#include "Speaker.h"
#include "Motordriver.h"
#include "reflex.h"
#include "led.h"

volatile int reflexCount = 0;
volatile int n50ms = 0;
volatile int lastReflex = -10;

void enableTimer4Interrupts(void);
void reflexReactions(void);

int main(void)
{
	sei();
    //-------------------------------------------- Initialisering --------------------------------------------
	
	//---------------Lyd-----------
	initUART();
	
	//--------------Motor----------
	InitEngine();
	
	//---------------Lys-----------
	
	
	//--------------Refleks-----------
	initRefleks();
	
	
	enableTimer4Interrupts();
	initLEDport();
	
	
	DDRA = 0;
	
	
	// ------------- Start bil ------------------
	while ((PINA & 1) != 0)
	{
		UDR2 = 0;
	}
	EngineControl(100);
	//K?RELYS
	StartLyd();
	// -------------------------------------- Main program loop ---------------------------------------------
	while(1)
	{
		
		if(reflexCount % 2 == 0)
			turnOnLED(7);
		else
			turnOffLED(7);
	
	}
	
}



ISR(INT0_vect)
{
	if(n50ms - lastReflex > 10)
	{
		lastReflex = n50ms;
		reflexCount++;
		reflexReactions();
	}
}


ISR(INT1_vect)
{
	if(n50ms - lastReflex > 10)
	{
		lastReflex = n50ms;
		reflexCount++;
		reflexReactions();
	}
}

ISR(TIMER4_COMPA_vect)
{
	n50ms++;
}




void reflexReactions(void)
{
			if(reflexCount == 6)
			{
				EngineControl(-100);
				//BAKLYS
				RefleksLyd();
			}
			else if(reflexCount == 8)
			{
				EngineControl(100);
				//K?RELYS
				RefleksLyd();
			}
			else if(reflexCount == 11)
			{
				EngineControl(0);
				//SLUK LYS
				SlutLyd();
			}
			else if(reflexCount > 0)
			{
				RefleksLyd();
			}
	}
	
	
void enableTimer4Interrupts(void)
{
	OCR4A = 49999;
	TCCR4A = 0b00000000;
	TCCR4B = 0b00001010;
	TIMSK4 = 0b00000010;
	}