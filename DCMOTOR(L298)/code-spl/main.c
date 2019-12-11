#include "stm32f10x.h"
#include "dcmotor.h"
#include "delay.h"

int main(void)
{
	delay_intial();
  Motor_Initial();
	while (1)
		{
			Motor_Rotate(Motor2,Left);
			Motor_Changespeed(Motor2,500);
			delayMs(2000);
			Motor_Stop(Motor2);
			delayMs(2000);
		}
			
}

