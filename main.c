/*
 * Sound.c
 *
 * Created: 29/10/2021 16:47:53
 * Author : jakob og ham frederik har også hjulpet
 */ 




#include "Speaker.h"

int baudRate = 9600;
int outputState = 0;

int main(void)
{
		
	unsigned char startSound[ARRAYSIZE+1] = {0x7E,0x0F,0x01,0x01,0x01,0xFF,0xEE,0xEF};		//Startlyden ligger i mappe 01, er fil 001. "7E 0F 00 01 01 FF EF EF".
	unsigned char reflexSound[ARRAYSIZE+1] = {0x7E,0x0F,0x00,0x01,0x02,0xFF,0xEE,0xEF};		//Reflexlyden ligger i mappe 01, er fil 002. "7E 0F 00 01 02 FF EF EF".
	unsigned char finishSound[ARRAYSIZE+1] = {0x7E,0x0F,0x00,0x01,0x03,0xFF,0xED,0xEF};		//Færdiglyden ligger i mappe 01, er fil 003. "7E 0F 00 01 03 FF EF EF".
	unsigned char stop[ARRAYSIZE+1] = {0x7E,0x16,0x00,0x00,0x00,0xFF,0xEA,0xEF};		//Stopkommando. Stopper afspilning af fil. "7E 16 00 00 00 FF EA EF"
	unsigned char volMax[ARRAYSIZE+1] = {0x7E,0x06,0x00,0x00,0x1E,0xFF,0xDC,0xEF};		//Volume max. "7E 06 00 00 1E FF DC EF"

	PrepareComms(baudRate);         //Klargør kommunikation med SOMO-II. Baudrate inputtes, OG ANDET ????
	SendCommand(volMax);			//Sender volMax kommando


	while(1)
	{	
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
				UDR2 = 0;      // SPAM output med nuller, hvis en kommando ikke skal sendes. Så kommer der ikke støj.
		}
	}
}

