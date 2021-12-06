#include "lights.h"
#include "motordriver.h"
#include "speaker.h"
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