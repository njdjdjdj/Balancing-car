#include "usart.h"
#include "string.h"

////加入以下代码,支持printf函数,而不需要选择use MicroLIB
//#if 1
//#pragma import(__use_no_semihosting)             
////标准库需要的支持函数                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
////_sys_exit(int x) 
////{ 
////	x = x; 
////} 
////重定义fputc函数 
//int fputc(int ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
//#endif 

/*使用microLib的方法*/
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
 
u8 USART_RX_BUF[64];     //接收缓冲,最大64个字节.
//接收状态
//bit7，接收完成标志
//bit6，接收到0x0d
//bit5~0，接收到的有效字节数目
u8 USART_RX_STA=0;       //接收状态标记

u8 Usart1_Receive;

void uart1_init(u32 bound)
{
	//GPIO端口设置
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
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART1, ENABLE);                    //使能串口 
}

void USART1_IRQHandler(void) 
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//接收中断标志位拉高
	{
		static u8 usart1_receive;
		Usart1_Receive = usart1_receive;
		usart1_receive = USART_ReceiveData(USART1);
		switch(usart1_receive)
		{
			case 'Z':
			{
				Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=0,Flag_jingzhi = 1,Flag_Turn_jingzhi = 1;//刹车
			}break;
			case 'E':
			{
				Flag_front=1,Flag_back=0,Flag_Left=0,Flag_Right=0;//前
			}break;
			case 'A':
			{
				Flag_front=0,Flag_back=1,Flag_Left=0,Flag_Right=0;//后
			}break;
			case 'C':
			{
				Flag_front=0,Flag_back=0,Flag_Left=1,Flag_Right=0;  //左
			}break;
			case 'B':
			{
				Flag_front=0,Flag_back=0,Flag_Left=1,Flag_Right=0;  //左
			}break;
			case 'G':
			{
				Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=1;  //右
			}break;
			case 'H':
			{
				Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=1;  //右
			}break;
			case 'X':
			{
				Flag_front=0,Flag_back=0,Flag_Left=0,Flag_Right=0,Flag_Quick =1;  //加速
			}break;
			default :
				break;
			
		}
	}
	
}



