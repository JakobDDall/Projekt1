/*
 * CFile1.c
 *
 * Created: 01/11/2021 12:28:24
 *  Author: jakob
 */ 


#include "Speaker.h"

void PrepareComms(int baud)
{
	UBRR2 = F_CPU/(16*(long int)baud) - 1; // Sæt baud rate af output
	UCSR2B = 0b00011000;
	UCSR2C = 0b00000110;
	DDRA = 0;
}


void SendCommand(unsigned char command[])
{
	for(int i = 0; i<ARRAYSIZE; i++)
	{
		while((UCSR2A & 0b00100000)==0)	 //Vent på register er klar til at modtage byte
		{}
		UDR2 = command[i];
	}
	
	
}