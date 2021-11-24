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
//Her mangler lights


//Globale varable
volatile int reflexCount = 0;		//Antal passerede reflekser. Styrer bilens opførsel
volatile int n50ms = 0;				//Antallet af 50ms sekunder passeret siden start af timer
volatile int lastReflex = -10;		//Variabel til at gemme hvornår sidste refleks blev passeret.


//TEMPORARY -- declarations ---
void n50msTimer(void);
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
	
	//-------------50msTimer----------
	n50msTimer();
	
	// ---------MEGA2560 LEDs---------
	initLEDport();
	
	//--------PORTA as input--------
	DDRA = 0;
	
	
	// ------------------------ Start bil -----------------------------
	while ((PINA & 1) != 0)		//Bliv her indtil indtil knap 0 trykkes
	{
		UDR2 = 0;				//Sender LOW til SOMO-II. Forhindrer støj/kliklyde. Måske findes et andet fix?
	}
	EngineControl(100);			//Start motor. Max speed
	//K?RELYS
	StartLyd();
	// -------------------------------------- Main program loop ---------------------------------------------
	while(1)
	{
		
		if(reflexCount % 2 == 0)	//Til test af reflexCount. Hvis lige antal lyser Led 7
			turnOnLED(7);
		else
			turnOffLED(7);
	
	}
	
}



ISR(INT0_vect)	//REFLEX1 interrupt rutine. Køres kun hvis tid siden sidste refleks > 500ms 
{
	if(n50ms - lastReflex > 10)
	{
		lastReflex = n50ms; //Gem tiden
		reflexCount++;		//Increment counter
		reflexReactions();	//Få bilen til at reagere
	}
}


ISR(INT1_vect)		//REFLEX2 interrupt rutine. Køres kun hvis tid siden sidste refleks > 500ms 
{
	if(n50ms - lastReflex > 10)
	{
		lastReflex = n50ms;	//Gem tiden
		reflexCount++;		//Increment counter
		reflexReactions();	//Få bilen til at reagere
	}
}

ISR(TIMER4_COMPA_vect)			//50msTimer tæller op ved compare match
{
	n50ms++;
}




void reflexReactions(void)		//Hvordan bilen skal reagere på reflekser
{
			if(reflexCount == 6)
			{
				EngineControl(-100); //Bak
				//BAKLYS
				RefleksLyd();
			}
			else if(reflexCount == 8)
			{
				EngineControl(100); //Frem
				//K?RELYS
				RefleksLyd();
			}
			else if(reflexCount == 11)
			{
				EngineControl(0); //Stop
				//SLUK LYS
				SlutLyd();
			}
			else if(reflexCount > 0)
			{
				RefleksLyd();
			}
	}
	
	
void n50msTimer(void)	//Initialiser 50msTimer
{
	OCR4A = 49999;			//Passende compare value for et compare match hvert 50. ms, med prescaler på __
	TCCR4A = 0b00000000;	//beskriv lige. gad ikke finde datablad
	TCCR4B = 0b00001010;	//beskriv lige. gad ikke finde datablad
	TIMSK4 = 0b00000010;	//beskriv lige. gad ikke finde datablad
	}