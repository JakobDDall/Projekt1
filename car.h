/*
 * car.h
 *
 * Created: 25/11/2021 09:55:54
 *  Author: jakob
 */ 

#include "lights.h"
#include "Motordriver.h"
#include "Speaker.h"
#include "reflex.h"
#include "led.h"

#ifndef CAR_H_
#define CAR_H_

//Values
#define FORWARD_SPEED 100
#define BACKWARD_SPEED -100




void initCar(void);
void startCar(void);
void reflexReactions(int nReflex);
void n50msTimer(void);

#endif /* CAR_H_ */