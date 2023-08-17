#ifndef  _MOTOR_H
#define  _MOTOR_H

#include "sys.h" 

#define Ain1  PBout(12)
#define Ain2  PBout(13)

#define Bin1  PBout(14)
#define Bin2  PBout(15)

void Motor_Init(void);
void Limit(int *motoA,int *motoB);
int GFP_abs(int p);
void SETPWM(int motor_left, int motor_right);
u8 Turn_Off(float angle);
#endif

