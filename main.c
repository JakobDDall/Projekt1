/*
 * Samlet_projekt.cpp
 *
 * Created: 22/11/2021 12:46:26
 * Author : jakob
 */ 

#include "Speaker.h"
#include "Motordriver.h"


int main(void)
{
    //-------------------------------------------- Initialisering --------------------------------------------
	
	//---------------Lyd-----------
	initUART();
	
	//--------------Motor----------
	InitEngine();
	
	//---------------Lys-----------
	
	
	//--------------Refleks-----------
	
	
	
	DDRA = 0;
	int reflexCount = 0;
	
	
	// ------------- Start bil ------------------
	while ((PINA & 1) != 0)
	{
		UDR2 = 0;
	}
	EngineControl(100);
	//KØRELYS
	StartLyd();
	_delay_ms(400);
	// -------------------------------------- Main program loop ---------------------------------------------
	while(1)
	{
		while ((PINA & 1) != 0)
		{
			UDR2 = 0;
		}
		reflexCount++;
		
		
		if(reflexCount == 6)
		{
			EngineControl(-100);
			//BAKLYS
			RefleksLyd();
		}
		else if(reflexCount == 8)
		{
			EngineControl(100);
			//KØRELYS
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
		
		_delay_ms(200);
	}
	
}

