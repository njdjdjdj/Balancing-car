#include "usart2.h"
#include "string.h"


void USART2_Init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE );
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART2, ENABLE);                    //使能串口 
}


void USART2_IRQHandler(void) 
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)//接收中断标志位拉高
	{
		
	}
	
}


int fputc(int ch, FILE *f)			//重定向c库函数printf到串口，重定向后可使用printf函数

{
		USART_SendData(USART2, (uint8_t) ch);		/* 发送一个字节数据到串口 */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);				/* 等待发送完毕 */
		return (ch);
}

int fgetc(FILE *f)				//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数

{
		while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);		/* 等待串口输入数据 */
		return (int)USART_ReceiveData(USART2);
}






