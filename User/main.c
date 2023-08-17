#include "sys.h" 

float Target_Speed = 0;						//�����ٶ�
short gyrox,gyroy,gyroz;					//���ٶ�
float Pitch,Roll,Yaw;						//�Ƕ�
int Encoder_Left,Encoder_Right;				//�������ٶ�
u8 Flag_Stop = 0;
u8 Flag_jingzhi,Flag_front,Flag_back,Flag_Left,Flag_Right,Flag_Turn_jingzhi,Flag_Quick; //����ң����صı���


int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//4����ռ,4����Ӧ��
	uart1_init(9600);
	USART2_Init(9600);
	
	delay_init();
	NVIC_Config();
	
	OLED_Init();
	OLED_Clear();
	
	MPU_Init();
	mpu_dmp_init();
	
	Encoder_TIM2_Init();
	Encoder_TIM4_Init();
	Motor_Init();
	PWM_Init_TIM1(7199,0);
	
	MPU6050_EXTI_Init();
	printf("��ɳ�ʼ��\n");
	while(1)
	{
		OLED_Float(0,0,Pitch,1);
		OLED_Float(50,50,Encoder_Right,1);
	}
}
