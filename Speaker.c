/*
 * CFile1.c
 *
 * Created: 01/11/2021 12:28:24
 *  Author: jakob
 */ 


#include "Speaker.h"




void testSpeaker()
{
	int outputState;
	
	if ((PINA & 1) == 0)
		{
			outputState = STARTOUT;
		}
		else if ((PINA & 1<<1) == 0)
		{
			outputState = REFLEXOUT;
		}
		else if ((PINA & 1<<2) == 0)
		{
			outputState = FINISHOUT;
		}
		else if ((PINA & 1<<3) == 0)
		{
			outputState = STOPOUT;
		}
		else
		{
			outputState = 0;
		}


	switch (outputState)     //Send kommando alt efter outputState. Hvis det ikke matcher cases, bruges default.
		{
			
			case STARTOUT:
				SendCommand(startSound);
				break;
			case REFLEXOUT:
				SendCommand(reflexSound);
				break;
			case FINISHOUT:
				SendCommand(finishSound);
				break;
			case STOPOUT:
				SendCommand(stop);
				break;
			default:
				UDR2 = 0;      // SPAM output med nuller, hvis en kommando ikke skal sendes. S� kommer der ikke st�j.
		}
}





void PrepareComms(int baud)
{
	UBRR2 = F_CPU/(16*(long int)baud) - 1; // S�t baud rate af output
	UCSR2B = 0b00011000;
	UCSR2C = 0b00000110;
	DDRA = 0;

	SendCommand(volMax);
}


void SendCommand(unsigned char command[])
{
	for(int i = 0; i<ARRAYSIZE; i++)
	{
		while((UCSR2A & 0b00100000)==0)	 //Vent p� register er klar til at modtage byte
		{}
		UDR2 = command[i];
	}
	
	
}