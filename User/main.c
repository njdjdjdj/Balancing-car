#include "sys.h" 

float Target_Speed = 0;						//期望速度
short gyrox,gyroy,gyroz;					//角速度
float Pitch,Roll,Yaw;						//角度
int Encoder_Left,Encoder_Right;				//编码器速度
u8 Flag_Stop = 0;
u8 Flag_jingzhi,Flag_front,Flag_back,Flag_Left,Flag_Right,Flag_Turn_jingzhi,Flag_Quick; //蓝牙遥控相关的变量


int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//4级抢占,4级响应。
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
	printf("完成初始化\n");
	while(1)
	{
		OLED_Float(0,0,Pitch,1);
		OLED_Float(50,50,Encoder_Right,1);
	}
}
