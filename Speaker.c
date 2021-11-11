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
	
	//Commands der kan bruges. Declare evt flere, hvis nødvendigt
	unsigned char startSound[ARRAYSIZE+1] = {0x7E,0x0F,0x01,0x01,0x01,0xFF,0xEE,0xEF};		//Startlyden ligger i mappe 01, er fil 001. "7E 0F 00 01 01 FF EF EF".
	unsigned char reflexSound[ARRAYSIZE+1] = {0x7E,0x0F,0x00,0x01,0x02,0xFF,0xEE,0xEF};		//Reflexlyden ligger i mappe 01, er fil 002. "7E 0F 00 01 02 FF EF EF".
	unsigned char finishSound[ARRAYSIZE+1] = {0x7E,0x0F,0x00,0x01,0x03,0xFF,0xED,0xEF};		//F�rdiglyden ligger i mappe 01, er fil 003. "7E 0F 00 01 03 FF EF EF".
	unsigned char stop[ARRAYSIZE+1] = {0x7E,0x16,0x00,0x00,0x00,0xFF,0xEA,0xEF};		//Stopkommando. Stopper afspilning af fil. "7E 16 00 00 00 FF EA EF"


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


void PrepareComms()
{
	UBRR2 = F_CPU/(16*(long int)9600) - 1; // S�t baud rate af output
	UCSR2B = 0b00011000;
	UCSR2C = 0b00000110;
	DDRA = 0;


	unsigned char volMax[ARRAYSIZE+1] = {0x7E,0x06,0x00,0x00,0x1E,0xFF,0xDC,0xEF};		//Volume max. "7E 06 00 00 1E FF DC EF"
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