/*
 * Samlet_projekt.cpp
 *
 * Created: 22/11/2021 12:46:26
 * Author : Jakob, Anders og Frederik
 */ 

#include "car.h"
//Globale variable
volatile int reflexCount = 0;		//Antal passerede reflekser. Styrer bilens opf�rsel
volatile int n50ms = 0;				//Antallet af 50ms sekunder passeret siden start af timer
volatile int lastReflex = -10;		//Variabel til at gemme hvorn�r sidste refleks blev passeret.



#define REFLEX_DELAY 6 // Ganges med 50. Antal millisekunder, hvor ny refleks ikke man m�les.
int main(void)
{
	// ------------------------ Initialize ---------------------------
	initCar();
	// ------------------------ Start bil -----------------------------
	startCar();
	// -------------------------------------- Main program loop ---------------------------------------------
	
	int currentTime = 0;	//Variable for keeping brakelights on for 500ms
	while(1)
	{
		if(reflexCount == 8 && (n50ms - currentTime) > 10)	//Til test af reflexCount. Hvis lige antal lyser Led 7
		{
			currentTime = n50ms;
		}
		else if(reflexCount == 11 && (n50ms - currentTime) > 10)
		{
			currentTime = n50ms;
		}
		
		if((n50ms - currentTime) > 9 && reflexCount >= 8 && reflexCount <= 10)
		{
			backLightState(BACK_LIGHT_NORMAL);
		}
		else if((n50ms - currentTime) > 9 && reflexCount >= 11)
		{
			backLightState(BACK_LIGHT_OFF);
		}
		
		
	}
	
	return 0;
}

ISR(INT5_vect)	//REFLEX1 interrupt rutine. Kommandoer kun hvis tid siden sidste refleks > 500ms 
{
	if(n50ms - lastReflex > REFLEX_DELAY)
	{
		lastReflex = n50ms; //Gem tiden
		reflexCount++;		//Increment counter
		reflexReactions(reflexCount);	//F� bilen til at reagere
	}
}

ISR(TIMER4_COMPA_vect)			//50msTimer t�ller op ved compare match
{
	n50ms++;
}
