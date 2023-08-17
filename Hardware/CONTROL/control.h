#ifndef __CONTROL_H
#define __CONTROL_H

#include "sys.h"

int Vertical_PID(float measure, float Gyro);
int Velocity_PI(int Speed_measure);
void I_xianfu(int max);
int Turn(int gyro_Z);
void EXTI9_5_IRQHandler(void);



#endif

