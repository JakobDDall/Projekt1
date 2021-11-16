/*
 * Sound.c
 *
 * Created: 29/10/2021 16:47:53
 * Author : jakob og ham frederik har ogs� hjulpet
 */ 




#include "Speaker.h"



int main(void)
{
	initUART();         //Klarg�r kommunikation med SOMO-II.
	
	while(1)
	{	
		testSpeaker();
	}
}

