#ifndef __STM32F0XX_7SEGMENT_H__
#define __STM32F0XX_7SEGMENT_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define SEGMENT_PORT  	GPIOE
#define SEGMENT_RCC		  RCC_APB2Periph_GPIOE
#define SEGMENT_PIN_0	  GPIO_Pin_0
#define SEGMENT_PIN_1	  GPIO_Pin_1
#define SEGMENT_PIN_2	  GPIO_Pin_2
#define SEGMENT_PIN_3	  GPIO_Pin_3
#define SEGMENT_PIN_4	  GPIO_Pin_4
#define SEGMENT_PIN_5	  GPIO_Pin_5
#define SEGMENT_PIN_6	  GPIO_Pin_6
#define SEGMENT_PIN_7	  GPIO_Pin_7

#define SEGMENT_ANODE_D1 	  GPIO_Pin_8
#define SEGMENT_ANODE_D2  	GPIO_Pin_9
#define SEGMENT_ANODE_D3	  GPIO_Pin_10
#define SEGMENT_ANODE_D4	  GPIO_Pin_11

#define segment0_en					0xfe00		//enable0
#define segment1_en					0xfb00		//enable1
#define segment2_en					0xfd00		//enable2
#define segment3_en					0xf700		//enable3

void SevenSegment_Init(void);
void Segment_WriteData(uint16_t );
#endif 	//__STM32F0XX_7SEGMENT_H__
