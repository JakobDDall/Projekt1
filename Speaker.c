/*
 * CFile1.c
 *
 * Created: 01/11/2021 12:28:24
 *  Author: jakob
 */ 


#include "Speaker.h"

//Commands der kan bruges. Declare evt flere, hvis nødvendigt
unsigned char stop[ARRAYSIZE+1] = {0x7E,0x16,0x00,0x00,0x00,0xFF,0xEA,0xEF};		//Stopkommando. Stopper afspilning af fil. "7E 16 00 00 00 FF EA EF"
unsigned char volMax[ARRAYSIZE+1] = {0x7E,0x06,0x00,0x00,0x1E,0xFF,0xDC,0xEF};		//Volume max. "7E 06 00 00 1E FF DC EF"


void initUART()
{
	UBRR2 = F_CPU/(16*(long int)9600) - 1; // S�t baud rate af output
	UCSR2B = 0b00011000;
	UCSR2C = 0b00000110;

	sendCommand(volMax);
}


void sendCommand(unsigned char command[])
{
	for(int i = 0; i<ARRAYSIZE; i++)
	{
		while((UCSR2A & 0b00100000)==0)	 //Vent p� register er klar til at modtage byte
		{}
		UDR2 = command[i];
	}
	
	
}


void startSound()
{
	unsigned char startSound[ARRAYSIZE+1] = {0x7E,0x0F,0x01,0x01,0x01,0xFF,0xEE,0xEF};		//Startlyden ligger i mappe 01, er fil 001. "7E 0F 00 01 01 FF EF EF".
	sendCommand(startSound);
}


void reflexSound()
{
	unsigned char reflexSound[ARRAYSIZE+1] = {0x7E,0x0F,0x00,0x01,0x02,0xFF,0xEE,0xEF};		//Reflexlyden ligger i mappe 01, er fil 002. "7E 0F 00 01 02 FF EF EF".
	sendCommand(reflexSound);
}


void finishSound()
{
	unsigned char finishSound[ARRAYSIZE+1] = {0x7E,0x0F,0x00,0x01,0x03,0xFF,0xED,0xEF};		//F�rdiglyden ligger i mappe 01, er fil 003. "7E 0F 00 01 03 FF EF EF".
	sendCommand(finishSound);
}