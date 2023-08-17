#include "encoder.h"

void Encoder_TIM2_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	
	TIM_ICInitTypeDef TIM_ICInitStruct; 
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter = 10;
	TIM_ICInit(TIM2, &TIM_ICInitStruct);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM2, 0);
	
	TIM_Cmd(TIM2, ENABLE);
}

void Encoder_TIM4_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	
	TIM_ICInitTypeDef TIM_ICInitStruct; 
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter = 10;
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	TIM_SetCounter(TIM4, 0);
	
	TIM_Cmd(TIM4, ENABLE);
}

int Read_Spead(int TIMx)
{
	int value_1;
	switch(TIMx)
	{
		case 2:value_1 = (short)TIM_GetCounter(TIM2);TIM_SetCounter(TIM2, 0);break;
		case 4:value_1 = (short)TIM_GetCounter(TIM4);TIM_SetCounter(TIM4, 0);break;
		default:value_1 = 0;
	}
	return value_1;
}

void TIM2_IRQHander(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == 1)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}

void TIM4_IRQHander(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) == 1)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}


















