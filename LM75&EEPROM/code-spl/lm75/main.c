#include "stm32f10x.h"
#include <stdio.h>
#include "bsp.h"
#include "lm75.h"
#include "delay.h"
//printf init
struct __FILE { int handle;} ;

FILE __stdout;
FILE __stdin;
FILE __stderr;

int fputc(int ch, FILE *f)  
{
	while(!USART_GetFlagStatus(COM1,USART_FLAG_TXE));	 
														 
	USART_SendData(COM1,ch);	

	while(!USART_GetFlagStatus(COM2,USART_FLAG_TXE));	 
														 
	USART_SendData(COM2,ch);	
	   
	return ch;	
}
  

int16_t temp ;
int main(void)
{
	delay_intial();
	RCC_Configuration();
  GPIO_Configuration();
  Com1_Intial();  //usb to serial 
  Com2_Intial();  //COM PORT
	printf("\nSTM32F107 is online.\n");

	printf("I2C init ... ");
	if (!LM75_Init(100000)) printf("ready.\n"); else {
		printf("fail.\n");
		printf("MCU halted now.\n");
		while(1);
	}
    LM75_Shutdown(DISABLE);
    temp = LM75_Temperature();
    while(1){
			delayMs(500);
	    temp = LM75_Temperature()/10;
			printf("The Temperature is :%d \n",temp);
		}
}