#include "usart2.h"
#include "string.h"


void USART2_Init(u32 bound)
{
	//GPIO�˿�����
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
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
}


void USART2_IRQHandler(void) 
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)//�����жϱ�־λ����
	{
		
	}
	
}


int fputc(int ch, FILE *f)			//�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����

{
		USART_SendData(USART2, (uint8_t) ch);		/* ����һ���ֽ����ݵ����� */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);				/* �ȴ�������� */
		return (ch);
}

int fgetc(FILE *f)				//�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���

{
		while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);		/* �ȴ������������� */
		return (int)USART_ReceiveData(USART2);
}






