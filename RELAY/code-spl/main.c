#include "bsp.h"
#include "delay.h"

int main(){
	RCC_Configuration();
	GPIO_Configuration();
	delay_intial();
	delayMs(1000);
	GPIO_SetBits(Relay1_GPIO_PORT,Relay1_PIN);	
	delayMs(1000);
  GPIO_SetBits(Relay2_GPIO_PORT,Relay2_PIN);
	delayMs(1000);
  GPIO_SetBits(Relay3_GPIO_PORT,Relay3_PIN);
	delayMs(1000);
  GPIO_SetBits(Relay4_GPIO_PORT,Relay4_PIN);
	delayMs(1000);
while(1){
		if(GPIO_ReadInputDataBit(DInput1_GPIO_PORT,DInput1_PIN) == 0){
			GPIO_SetBits(Relay1_GPIO_PORT,Relay1_PIN);	
		}
		else if (GPIO_ReadInputDataBit(DInput1_GPIO_PORT,DInput1_PIN) == 1)
			GPIO_ResetBits(Relay1_GPIO_PORT,Relay1_PIN);	
   //----------------------------------------------------------
		if(GPIO_ReadInputDataBit(DInput2_GPIO_PORT,DInput2_PIN) == 0){
			GPIO_SetBits(Relay2_GPIO_PORT,Relay2_PIN);	
		}
		else if (GPIO_ReadInputDataBit(DInput2_GPIO_PORT,DInput2_PIN) == 1)
			GPIO_ResetBits(Relay2_GPIO_PORT,Relay2_PIN);			
   //----------------------------------------------------------
		if(GPIO_ReadInputDataBit(DInput3_GPIO_PORT,DInput3_PIN) == 0){
			GPIO_SetBits(Relay3_GPIO_PORT,Relay3_PIN);	
		}
		else if (GPIO_ReadInputDataBit(DInput3_GPIO_PORT,DInput3_PIN) == 1)
			GPIO_ResetBits(Relay3_GPIO_PORT,Relay3_PIN);	
   //----------------------------------------------------------
		if(GPIO_ReadInputDataBit(DInput4_GPIO_PORT,DInput4_PIN) == 0){
			GPIO_SetBits(Relay4_GPIO_PORT,Relay4_PIN);	
		}
		else if (GPIO_ReadInputDataBit(DInput4_GPIO_PORT,DInput4_PIN) == 1)
			GPIO_ResetBits(Relay4_GPIO_PORT,Relay4_PIN);	
}

}