/*
 * Sound.c
 *
 * Created: 29/10/2021 16:47:53
 * Author : jakob og ham frederik har ogs� hjulpet
 */ 




#include "Speaker.h"



int main(void)
{
	PrepareComms(baudRate);         //Klarg�r kommunikation med SOMO-II. Baudrate inputtes, OG ANDET ????
				//Sender volMax kommando
	while(1)
	{	
		testSpeaker();
	}
}

