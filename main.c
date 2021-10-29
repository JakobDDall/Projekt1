/*
 * Projekt.c
 *
 * Created: 26/10/2021 13:22:31
 * Author : Frederik
 */ 

#include <avr/io.h>
#include <stdlib.h>
#define	F_CPU 16000000
#include <util/delay.h>
#include <stdint.h>

void SendInteger(uint64_t Tal);
void SendString(char *Streng);
void SendChar(char tegn);
void command();

struct somoMessages
{
	unsigned char start;
	unsigned char cmd;
	unsigned char feedback;
	unsigned char para1;
	unsigned char para2;
	unsigned char checksum1;
	unsigned char checksum2;
	unsigned char end;
} SomoMsg;

int main(void)
{
	//int i = 0;
	//int hejsa[8] = {0xEF, 0xEF, 0xFF, 0x01, 0x01, 0x00, 0x0F, 0x7E};



		
		
		UBRR2 = 103;//F_CPU/(16*9600) - 1;
		UCSR2B = 0b00011000;
		UCSR2C = 0b00000110;
		
		SomoMsg.start = 0x7E;
		SomoMsg.cmd = 0x06;
		SomoMsg.feedback = 0x00;
		SomoMsg.para1 = 0x00;
		SomoMsg.para2 = 0x1E;
		SomoMsg.checksum1 = 0xFF;
		SomoMsg.checksum2 = 0xDC;
		SomoMsg.end = 0xEF;
		
		
		command();
		
		SomoMsg.start = 0x7E;
		SomoMsg.cmd = 0x01;
		SomoMsg.feedback = 0x00;
		SomoMsg.para1 = 0x00;
		SomoMsg.para2 = 0x00;
		SomoMsg.checksum1 = 0xFF;
		SomoMsg.checksum2 = 0xFF;
		SomoMsg.end = 0xEF;
		
		//Det er som om nogle af bytesne er vendt om. F.eks. 0x0F ligner 0xF0 i waveforms
		
		while(1)
		{
			command();
			for (int i = 0; i < 10000000000000000; i++)
			{
				UDR2 = 0x00;
			}
			
			
		}
		
		
}


void command()
{
	while((UCSR2A & 0b00100000)==0)		//Venter på at data registeret er tomt
	{}
	UDR2 = SomoMsg.start;
	while((UCSR2A & 0b00100000)==0)		//Venter på at data registeret er tomt
	{}
	UDR2 = SomoMsg.cmd;
	while((UCSR2A & 0b00100000)==0)		//Venter på at data registeret er tomt
	{}
	UDR2 = (unsigned char)SomoMsg.feedback;
	while((UCSR2A & 0b00100000)==0)		//Venter på at data registeret er tomt
	{}
	UDR2 = SomoMsg.para1;
	while((UCSR2A & 0b00100000)==0)		//Venter på at data registeret er tomt
	{}
	UDR2 = SomoMsg.para2;
	while((UCSR2A & 0b00100000)==0)		//Venter på at data registeret er tomt
	{}
	UDR2 = SomoMsg.checksum1;
	while((UCSR2A & 0b00100000)==0)		//Venter på at data registeret er tomt
	{}
	UDR2 = SomoMsg.checksum2;
	while((UCSR2A & 0b00100000)==0)		//Venter på at data registeret er tomt
	{}
	UDR2 = SomoMsg.end;
}

void SendInteger(uint64_t Tal)
{
	char talarray[16];
	itoa(Tal,talarray,16);
	SendString(talarray);
	
}


void SendString(char *Streng)
{
	while(*Streng != 0)
	{
		SendChar(*Streng);
		Streng++;
	}
	
}


void SendChar(char tegn)
{
	_delay_ms(50);
	UDR2 = tegn;
}
