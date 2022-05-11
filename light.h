/*
 * Created: 19/11/2021 12.27.42
 * Author : Genku(M.T.A.)
 */ 

// uses timer 3 compare B-C
// uses port E pin 4-5

#ifndef LIGHT_H_
#define LIGHT_H_

void initLight(void);
void initTimer500ms(void);
void frontLightState(unsigned char state); //state = 0/1 = off/on
void backLightState(unsigned char state); //state = 0/1/2 = off/on/braking

#endif /* LIGHT_H_ */