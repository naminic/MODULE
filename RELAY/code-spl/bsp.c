#include "bsp.h"

/******************************************************************************
            Initial RCC
  * @brief  Configures different system clocks
  * @param  None
  * @retval None                           
******************************************************************************/
void RCC_Configuration(){

		/*-----------------Relays---------------------*/
	RCC_APB2PeriphClockCmd(Relays_GPIO_CLK,ENABLE);	
}
/******************************************************************************
           Initial GPIO
  * @brief  Configure GPIO Pins
  * @param  None
  * @retval None
******************************************************************************/
void GPIO_Configuration(){
	
  GPIO_InitTypeDef GPIO_InitStructure;	
	/*-----------------Relays---------------------*/
	  /* Configure PA3 and PA4 and PA5 and PA6 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = Relay1_PIN | Relay2_PIN|Relay3_PIN|Relay4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(Relays_GPIO_PORT, &GPIO_InitStructure);
	  //-----------------------------------------------------
	  /* Configure Digital Inputs */

		/* Configure INPUT1  in input pullup mode */
	GPIO_InitStructure.GPIO_Pin = DInput1_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(DInput1_GPIO_PORT, &GPIO_InitStructure);	
		/* Configure INPUT2  in input pullup mode */
	GPIO_InitStructure.GPIO_Pin = DInput2_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(DInput2_GPIO_PORT, &GPIO_InitStructure);	
		/* Configure INPUT3  in input pullup mode */
	GPIO_InitStructure.GPIO_Pin = DInput3_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(DInput3_GPIO_PORT, &GPIO_InitStructure);	
		/* Configure INPUT4  in input pullup mode */
	GPIO_InitStructure.GPIO_Pin = DInput4_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(DInput4_GPIO_PORT, &GPIO_InitStructure);	
}

