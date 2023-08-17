#include "control.h"

float Med_Angle = -10.5;						//��е��ֵ
float Vertical_Kp = -330,		//ֱ����Kp
	  Vertical_Kd = -2.2;		//ֱ����Kd

float Velocity_Kp = 110,		//�ٶȻ�Kp
	  Velocity_Ki = 0.55;			//�ٶȻ�Kd

float Turn_Kp = 40,
	  Turn_Kd = 0;

int Vertical_out,Velocity_out,Turn_out;		//�������

extern float Med_Angle;						//��е��ֵ
int measure;								//�������ٶȲ���ֵ
int motor1, motor2;

int Vertical_PD(float measure, float Gyro);
int Velocity_PI(int Speed_measure);
int Turn(int gyro_Z);


void EXTI9_5_IRQHandler(void)
{
	int PWM_out;
	if(EXTI_GetITStatus(EXTI_Line5)!=0)
	{
		if(PBin(5) == 0)
		{
			EXTI_ClearITPendingBit(EXTI_Line5);
			Encoder_Left = Read_Spead(2);						//�ɼ��������ٶ�
			Encoder_Right = -Read_Spead(4);
			measure = (Encoder_Left + Encoder_Right);		//���������ٶȸ�����ֵ
			mpu_dmp_get_data(&Pitch, &Roll, &Yaw);				//�Ƕ�
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);			//���ٶ�
			Vertical_out = Vertical_PD(Pitch, gyroy);				//ֱ��������
			Velocity_out = Velocity_PI(measure);				//�ٶȻ�����
			Turn_out = Turn(gyroz);
			
			PWM_out = Vertical_out + Velocity_out;				//PWM���
			motor1 = PWM_out - Turn_out;
			motor2 = PWM_out + Turn_out;
			Limit(&motor1, &motor2);							//PWM�޷�
			if(Turn_Off(Pitch) == 0)
			SETPWM(motor1,motor2);								//����PWM�����
		}
	}
}



//ֱ����PD

int Vertical_PD(float measure, float Gyro)
{
	int PWM_out;
	
	PWM_out = Vertical_Kp*(measure - Med_Angle) + Vertical_Kd*Gyro;
	return PWM_out;
}

//�ٶȻ�PI
int Velocity_PI(int Speed_measure)
{
	static int Encoder_err, Encoder_err_low, Encoder_err_low_last, Encoder_sum, Movement;
	static int PWM_out;
	static float Target_Velocity = 200;
	
	if(Flag_front == 1)			Movement = Target_Velocity / 2;
	else if(Flag_back == 1)    	Movement = -Target_Velocity / 2;
	else if(Flag_jingzhi == 1)	Movement = 0;
	else if(1 == Flag_Quick)	Movement = Target_Velocity;

	else Movement = 0;
	
	Encoder_err = 0 - Speed_measure;
	Encoder_err_low = 0.3 * Encoder_err + 0.7 * Encoder_err_low_last;
	Encoder_err_low_last = Encoder_err_low;
	Encoder_sum += Encoder_err_low;
	Encoder_sum = Encoder_sum + Movement;
	if(Encoder_sum > 10000) Encoder_sum = 10000;
	if(Encoder_sum < -10000) Encoder_sum = -10000;
	
	PWM_out = Velocity_Kp*Encoder_err + Velocity_Ki*Encoder_sum;
	
	if(Turn_Off(Pitch) == 1) Encoder_sum = 0;
		
	return PWM_out;
}

//ת��
int Turn(int gyro_Z)
{
	int PWM_out;
	static float Turn_Target, Turn_Amplitude=40;
	float Kp = Turn_Kp,Kd;			
	
	if(1 == Flag_Left)	        Turn_Target = -Turn_Amplitude/2;
	else if(1 == Flag_Right)	  Turn_Target = Turn_Amplitude/2;
	else if(1 == Flag_Turn_jingzhi)	 Turn_Target = 0;
	else Turn_Target = 0;
	
	if(1 == Flag_front || 1 == Flag_back)  Kd = Turn_Kd;        
	else Kd = 0;   
	
	PWM_out = Turn_Target * Kp + gyro_Z * Kd;
	
	return PWM_out;
}


