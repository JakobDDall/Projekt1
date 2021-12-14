/*
 * Samlet_projekt.cpp
 *
 * Created: 22/11/2021 12:46:26
 * Author : Jakob, Anders og Frederik
 */ 

#include "car.h"
//Globale variable
volatile int reflexCount = 0;		//Antal passerede reflekser. Styrer bilens opførsel
volatile int n50ms = 0;				//Antallet af 50ms sekunder passeret siden start af timer
volatile int lastReflex = -10;		//Variabel til at gemme hvornår sidste refleks blev passeret.



#define REFLEX_DELAY 6 // Ganges med 50. Antal millisekunder, hvor ny refleks ikke man måles.
int main(void)
{
	// ------------------------ Initialize ---------------------------
	initCar();
	// ------------------------ Start bil -----------------------------
	startCar();
	// -------------------------------------- Main program loop ---------------------------------------------
	while(1)
	{
		
		if(reflexCount % 2 == 0)	//Til test af reflexCount. Hvis lige antal lyser Led 7
			turnOnLED(7);
		else
			turnOffLED(7);
	}
	
	return 0;
}

ISR(INT4_vect)	//REFLEX1 interrupt rutine. Kommandoer kun hvis tid siden sidste refleks > 500ms 
{
	if(n50ms - lastReflex > REFLEX_DELAY)
	{
		lastReflex = n50ms; //Gem tiden
		reflexCount++;		//Increment counter
		reflexReactions(reflexCount);	//Få bilen til at reagere
	}
}

ISR(TIMER4_COMPA_vect)			//50msTimer tæller op ved compare match
{
	n50ms++;
}

ISR(TIMER5_OVF_vect)		//500ms after 
{
	if (reflexCount >= 8 || reflexCount <= 10)
	{
		backLightState(BACK_LIGHT_NORMAL);	
	}
	else if (reflexCount >= 11)
	{
		backLightState(BACK_LIGHT_OFF);
	}
	TCCR5B = 0x00; //Disable timer
}