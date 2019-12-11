
#include "bsp.h"
#include "stm32f10x_usart.h"
#include "stdio.h"

//printf init
struct __FILE { int handle;} ;

FILE __stdout;
FILE __stdin;
FILE __stderr;

int fputc(int ch, FILE *f)  
{
	while(!USART_GetFlagStatus(COM1,USART_FLAG_TXE));	 
														 
	USART_SendData(COM1,ch);						  
	   
	return ch;	
}
//iniit serial to usb
void COM1_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;
	
	
	RCC_APB2PeriphClockCmd(COM1_CLK_PORT | COM1_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = COM1_TXD_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(COM1_PORT,&GPIO_InitStruct); //TX	

	GPIO_InitStruct.GPIO_Pin = COM1_RXD_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_Init(COM1_PORT,&GPIO_InitStruct); //RX	
	
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(COM1,&USART_InitStructure);
	
	USART_Cmd(COM1,ENABLE);

}