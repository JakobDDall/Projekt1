#ifndef SPEAKER_H_
#define SPEAKER_H_


//CPU frekvens
#define	F_CPU 16000000


//Libraries
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdint.h>


////Outputstates af switch til lyd. Givet navne for readability
//#define STARTOUT 1
//#define REFLEXOUT 2
//#define FINISHOUT 3
//#define STOPOUT 4



//Arraysize af kommandoer
#define ARRAYSIZE 8

void initUART(void);
void sendCommand(unsigned char command[]);
void startSound(void);
void reflexSound(void);
void finishSound(void);



#endif /* SPEAKER_H_ */