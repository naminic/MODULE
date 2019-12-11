
#include "stm32f10x.h"
#include "delay.h"
#include "bsp.h"
#include "tm_stm32f4_hd44780.h"
#include <stdio.h>


GPIO_InitTypeDef GPIO_Ins ;

int main(void){
	
	int i = 0;
	//config system
	RCC_Configuration();
  GPIO_Configuration();
	delay_intial();
	
	TM_HD44780_Init(16, 2);
  TM_HD44780_Puts(0, 0, "hello");
	delayMs(100);
	TM_HD44780_Clear();
	
	for (i =0 ; i<16 ; i++){
		TM_HD44780_Puts(i, 0, "naminic");
		delayMs(1000);
		TM_HD44780_Clear();
	}
	
	while(1) {
		
		}
}

