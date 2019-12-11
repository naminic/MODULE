#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
#include "bsp.h"
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
  
/***************************************************************/
//               ADC_Configuration
/***************************************************************/
void ADC_Configuration(void)
{
	ADC_InitTypeDef  ADC_InitStructure;
	    //--Enable ADC1 and GPIOA--
  GPIO_InitTypeDef GPIO_InitStructure; //Variable used to setup the GPIO pins
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);
  //==Configure ADC pins (PA0 -> Channel 0 to PA7 -> Channel 7) as analog inputs==
  GPIO_StructInit(&GPIO_InitStructure); // Reset init structure, if not it can cause issues...
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  /* PCLK2 is the APB2 clock */
  /* ADCCLK = PCLK2/6 = 72/6 = 12MHz*/
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);

  /* Enable ADC1 clock so that we can talk to it */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  /* Put everything back to power-on defaults */
  ADC_DeInit(ADC1);

  /* ADC1 Configuration ------------------------------------------------------*/
  /* ADC1 and ADC2 operate independently */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  /* Disable the scan conversion so we do one at a time */
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  /* Don't do contimuous conversions - do them on demand */
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  /* Start conversin by software, not an external trigger */
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  /* Conversions are 12 bit - put them in the lower 12 bits of the result */
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  /* Say how many channels would be used by the sequencer */
  ADC_InitStructure.ADC_NbrOfChannel = 1;

  /* Now do the setup */
  ADC_Init(ADC1, &ADC_InitStructure);
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibaration register */
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));
  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
}


/***************************************************************/
//                  readADC1
/***************************************************************/
u16 readADC1(u8 channel)
{
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_1Cycles5);
  // Start the conversion
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  // Wait until conversion completion
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  return ADC_GetConversionValue(ADC1);
}

/***************************************************************/
//                  get_state_xy
/***************************************************************/
#define minmeddle  1700
#define maxmeddle  2400
#define max        4096
#define div        400  
int getstatexy(unsigned char xy)
{
	 unsigned int val;	
	if(xy)
	 val = readADC1(8);
	else
	 val = readADC1(9);
//no change
 	if( val > minmeddle && val < maxmeddle)
		return 0;
//up change	
	if( val < minmeddle )
	{
		val = val / div ;
			return 5 - val;		
	}
	
//down change	
	if(val > maxmeddle)
	{
		val = (val - max) * (-1);
		val = val / div;	
			return (5 - val) * -1;	
	}	
	
	return 0;
}
/***************************************************************/
//                          main
/***************************************************************/
#define speed 2
int main(void)
{
	unsigned short int x = 1,y =	 1;
 ADC_Configuration();

	/*********************** Intial the clock and perpherals **********************/
  RCC_Configuration();
  GPIO_Configuration();
  Com1_Intial();  //usb to serial 
  Com2_Intial();  //COM PORT
  delay_intial();
  printf("Naminic STM32 evaluation board\n");
while (1)
{	
	if(getstatexy(0) || getstatexy(1))
	{
		printf("The X :%d\r\n", getstatexy(1));
		printf("The Y :%d\r\n", getstatexy(0));
		delayMs(500);
		//x = x + speed * getstatexy(1);
		//y = y + speed * getstatexy(0);
	
	  //if( x == 0 ) x = 1;
	  //if( y == 0 ) y = 1;
    //if( x > 800 ) x = 800 -20;
	  //if( y > 600 ) y = 600 - 20;
	}
}	
return 0;
}