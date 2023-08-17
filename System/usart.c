#include "usart.h"
#include "string.h"

////�������´���,֧��printf����,������Ҫѡ��use MicroLIB
//#if 1
//#pragma import(__use_no_semihosting)             
////��׼����Ҫ��֧�ֺ���                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////����_sys_exit()�Ա���ʹ�ð�����ģʽ    
////_sys_exit(int x) 
////{ 
////	x = x; 
////} 
////�ض���fputc���� 
//int fputc(int ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
//#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
u8 USART_RX_BUF[64];     //���ջ���,���64���ֽ�.
//����״̬
//bit7��������ɱ�־
//bit6�����յ�0x0d
//bit5~0�����յ�����Ч�ֽ���Ŀ
u8 USART_RX_STA=0;       //����״̬���

u8 Usart1_Receive;

void uart1_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
}

void USART1_IRQHandler(void) 
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//�����жϱ�־λ����
	{
		static u8 usart1_receive;
		Usart1_Receive = usart1_receive;
		usart1_receive = USART_ReceiveData(USART1);
		switch(usart1_receive)
		{
			case 'Z':
			{
				Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=0,Flag_jingzhi = 1,Flag_Turn_jingzhi = 1;//ɲ��
			}break;
			case 'E':
			{
				Flag_front=1,Flag_back=0,Flag_Left=0,Flag_Right=0;//ǰ
			}break;
			case 'A':
			{
				Flag_front=0,Flag_back=1,Flag_Left=0,Flag_Right=0;//��
			}break;
			case 'C':
			{
				Flag_front=0,Flag_back=0,Flag_Left=1,Flag_Right=0;  //��
			}break;
			case 'B':
			{
				Flag_front=0,Flag_back=0,Flag_Left=1,Flag_Right=0;  //��
			}break;
			case 'G':
			{
				Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=1;  //��
			}break;
			case 'H':
			{
				Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=1;  //��
			}break;
			case 'X':
			{
				Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=0,Flag_Quick =1;  //����
			}break;
			default :
				break;
			
		}
	}
	
}



