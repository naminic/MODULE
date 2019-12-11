#include "stm32f10x.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "joystick.h"


void JoystickInit(void)
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

