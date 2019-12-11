#include "7segment.h"
#include "delay.h"
//const unsigned char digit[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
//const unsigned char digit[10]= {0x40,0xF9,0x24,0x30,0x19,0x12,0x02,0xF8,0xE0,0x10}; //COMMON ANODE
const unsigned char digit[10]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};  //COMMON ANODE

GPIO_InitTypeDef GPIO_InitStructure;
void SevenSegment_Init(void)
{
	//Enable Port clock
	RCC_APB2PeriphClockCmd(SEGMENT_RCC, ENABLE);
	//Initiliaze seven segmnet data pins
	GPIO_InitStructure.GPIO_Pin = SEGMENT_PIN_0 | SEGMENT_PIN_1 | SEGMENT_PIN_2 | SEGMENT_PIN_3 | SEGMENT_PIN_4 | SEGMENT_PIN_5 | SEGMENT_PIN_6|
	                                                      SEGMENT_PIN_7|SEGMENT_ANODE_D1|SEGMENT_ANODE_D2|SEGMENT_ANODE_D3|SEGMENT_ANODE_D4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SEGMENT_PORT, &GPIO_InitStructure);

	//GPIO_Write(SEGMENT_PORT, GPIO_ReadOutputData(SEGMENT_PORT) & 0xFF80);
}

void Segment_WriteData(uint16_t input)
{ 
	
	int data_0 , data_1 , data_2 ,data_3 = 0;
	uint16_t a,b,c,d;
	int time = 5;
	//int z=0;
	data_0 = input % 10 ;
	data_1 = (input % 100 - data_0) /10 ;
	data_2 = (input % 1000 - (data_1*10)-data_0) /100 ;
	data_3 = (input % 10000 - (data_2*100)-(data_1*10)-data_0) /1000 ;
	a=((uint16_t) digit[data_0]) + segment0_en;
	b = (((uint16_t) digit[data_1]) + segment1_en);
	c = (((uint16_t) digit[data_2]) + segment2_en);
	d = (((uint16_t) digit[data_3]) + segment3_en);
	//enable delay 
	delay_intial();
	GPIO_Write(SEGMENT_PORT, a);
	 
	 delayMs(time);
	GPIO_Write(SEGMENT_PORT, b);
	
  delayMs(time);
	GPIO_Write(SEGMENT_PORT, c);
	
  delayMs(time);
	GPIO_Write(SEGMENT_PORT, d);
	
  delayMs(time);

}
