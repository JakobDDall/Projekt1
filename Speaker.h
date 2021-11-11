/*
 * header.h
 *
 * Created: 01/11/2021 09:44:02
 *  Author: jakob
 */ 


#ifndef HEADER_H_
#define HEADER_H_


#define STARTOUT 1
#define REFLEXOUT 2
#define FINISHOUT 3
#define STOPOUT 4

#define	F_CPU 16000000

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdint.h>
#define ARRAYSIZE 8


int baudRate = 9600;



void PrepareComms(int baud);
void SendCommand(unsigned char command[]);
void testSpeaker();




	unsigned char startSound[ARRAYSIZE+1] = {0x7E,0x0F,0x01,0x01,0x01,0xFF,0xEE,0xEF};		//Startlyden ligger i mappe 01, er fil 001. "7E 0F 00 01 01 FF EF EF".
	unsigned char reflexSound[ARRAYSIZE+1] = {0x7E,0x0F,0x00,0x01,0x02,0xFF,0xEE,0xEF};		//Reflexlyden ligger i mappe 01, er fil 002. "7E 0F 00 01 02 FF EF EF".
	unsigned char finishSound[ARRAYSIZE+1] = {0x7E,0x0F,0x00,0x01,0x03,0xFF,0xED,0xEF};		//F�rdiglyden ligger i mappe 01, er fil 003. "7E 0F 00 01 03 FF EF EF".
	unsigned char stop[ARRAYSIZE+1] = {0x7E,0x16,0x00,0x00,0x00,0xFF,0xEA,0xEF};		//Stopkommando. Stopper afspilning af fil. "7E 16 00 00 00 FF EA EF"
	unsigned char volMax[ARRAYSIZE+1] = {0x7E,0x06,0x00,0x00,0x1E,0xFF,0xDC,0xEF};		//Volume max. "7E 06 00 00 1E FF DC EF"




#endif /* HEADER_H_ */