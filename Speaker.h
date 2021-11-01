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

void PrepareComms(int baud);
void SendCommand(unsigned char command[]);




#endif /* HEADER_H_ */