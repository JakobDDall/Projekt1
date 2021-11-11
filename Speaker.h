/*
 * header.h
 *
 * Created: 01/11/2021 09:44:02
 *  Author: jakob
 */ 


#ifndef HEADER_H_
#define HEADER_H_

//Libraries
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdint.h>


//Outputstates af switch til lyd. Givet navne for readability
#define STARTOUT 1
#define REFLEXOUT 2
#define FINISHOUT 3
#define STOPOUT 4

//CPU frekvens
#define	F_CPU 16000000

//Arraysize af kommandoer
#define ARRAYSIZE 8



void PrepareComms();
void SendCommand(unsigned char command[]);
void testSpeaker();






#endif /* HEADER_H_ */