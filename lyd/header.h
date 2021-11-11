#define STARTOUT 1
#define REFLEXOUT 2
#define FINISHOUT 3
#define STOPOUT 4

#define	F_CPU 16000000

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include <stdint.h>

void PrepareComms(int baud);


int SendCommand(struct Output command);

