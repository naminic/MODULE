#include "dcmotor.h"
#include "stm32f10x_usart.h"
#include <stdio.h>

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 100, Channel2Pulse = 100,Channel3Pulse = 100;
/******************************************************************************
                               Initial RCC
  * @brief  Configures different system clocks.
  * @param  None
  * @retval None
******************************************************************************/
void RCC_Configuration(){
  /* TIM4, GPIOA, GPIOB, GPIOE and AFIO clocks enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | LED_CLK | RCC_APB2Periph_GPIOD  |RCC_APB2Periph_AFIO, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
}

/******************************************************************************
                                  Initial GPIO
  * @brief  Configure GPIO Pins.
  * @param  None
  * @retval None
******************************************************************************/
void GPIO_Configuration(void){
	
	GPIO_InitTypeDef GPIO_InitStructure_A; 
	GPIO_InitTypeDef GPIO_InitStructure_B;
	GPIO_InitTypeDef GPIO_InitStructure_C;
	GPIO_InitTypeDef GPIO_InitStructure_D;
	
  
	 /* GPIOA Configuration: Channel 1/1N, 2/2N, 3/3N and 4 as alternate function push-pull */
  GPIO_InitStructure_A.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3 ;
  GPIO_InitStructure_A.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure_A.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure_A);
	
	
	 /* GPIOB Configuration: Channel 1/1N, 2/2N, 3/3N and 4 as alternate function push-pull */
  GPIO_InitStructure_B.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 ;
  GPIO_InitStructure_B.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure_B.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure_B);
	
	//LEDs ON GPIOC
	GPIO_InitStructure_C.GPIO_Pin = LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin ;
  GPIO_InitStructure_C.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure_C.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOC, &GPIO_InitStructure_C);
	
	/* GPIOD Configuration: Channel 1/1N, 2/2N, 3/3N and 4 as alternate function push-pull */
  GPIO_InitStructure_D.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure_D.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure_D.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOD, &GPIO_InitStructure_D);

  /* TIM4 Full remapping pins */
  GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE); 
}

/******************************************************************************
                                  Initial PWM
  * @brief  Configure PWM.
  * @param  None
  * @retval None
******************************************************************************/
void PWM_Intial(void){
/* TIM4 Configuration ---------------------------------------------------
   Generate 7 PWM signals with 4 different duty cycles:
   TIM4CLK = SystemCoreClock, Prescaler = 0, TIM4 counter clock = SystemCoreClock
   SystemCoreClock is set to 72 MHz for Low-density, Medium-density, High-density
   and Connectivity line devices and to 24 MHz for Low-Density Value line and
   Medium-Density Value line devices
   
   The objective is to generate 7 PWM signal at 17.57 KHz:
     - TIM4_Period = (SystemCoreClock / 17570) - 1
   The channel 1 and channel 1N duty cycle is set to 10%
   The channel 2 and channel 2N duty cycle is set to 10%
   The channel 3 and channel 3N duty cycle is set to 10%
   The channel 4 duty cycle is set to 12.5%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM4_Period - 1) / 100
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  TimerPeriod = (SystemCoreClock / 20000 ) - 1;
  /* Compute CCR1 value to generate a duty cycle at 10% for channel 1 and 1N */
  Channel1Pulse = (uint16_t) (((uint32_t) 100 * (TimerPeriod - 1)) / 1000);
  /* Compute CCR2 value to generate a duty cycle at 10%  for channel 2 and 2N */
  Channel2Pulse = (uint16_t) (((uint32_t) 100 * (TimerPeriod - 1)) / 1000);
	/* Compute CCR2 value to generate a duty cycle at 10%  for channel 3 and 3N */
	Channel3Pulse = (uint16_t) (((uint32_t) 100 * (TimerPeriod - 1)) / 1000);
  
  
	/* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM_OC1Init(TIM4, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);

  /* TIM4 counter enable */
  TIM_Cmd(TIM4, ENABLE);

  /* TIM4 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM4, ENABLE);
}
/******************************************************************************
                               Motor_Initial
  * @brief  initialize CLK,GPIO,PWM for driving motor DC
	* @param 	None
  * @retval None
******************************************************************************/
void Motor_Initial(void)
{	
	//CLK_config
	RCC_Configuration();
	//GPIO_config
	GPIO_Configuration();
	//PWM_config
	PWM_Intial();
}
/******************************************************************************
                               Motor_Rotate
  * @brief  Initialize DC motor 1 or 2 to move clockwise or counter clock wise
  * @param  motor specifies which of motor 1 or 2 initialize	
			@arg		motor1 : motor 1 initialize
			@arg    motor2 : motor 2 initialize
	* @param	position sets the rotation to left ro right
			@arg Right : sets the rotation to right
			@arg Left : sets the rotation to left
  * @retval None
******************************************************************************/
void Motor_Rotate(Motor motor,position direction)
{
	assert_param(IS_Motor(motor));
	assert_param(IS_position(direction));
	
		if (motor == Motor1)
		{
			if(direction == Right )
			{
				GPIO_ResetBits(INPUT1_PORT,INPUT1_Pin);			 // INPUT1 = 0
				GPIO_ResetBits(LED1_PORT,LED1_Pin);					 // INPUT1 ON LED1
				GPIO_SetBits(INPUT2_PORT,INPUT2_Pin);   	   // INPUT2 = 1
				GPIO_SetBits(LED2_PORT,LED2_Pin);					   // INPUT2 ON LED2
			}
			else if(direction == Left)
			{
				GPIO_WriteBit(INPUT1_PORT,INPUT1_Pin,Bit_SET);			   // INPUT1 = 1
				GPIO_SetBits(LED1_PORT,LED1_Pin);						 // INPUT1 ON LED1
				GPIO_ResetBits(INPUT2_PORT,INPUT2_Pin);   	 // INPUT2 = 0
				GPIO_ResetBits(LED2_PORT,LED2_Pin);					 // INPUT2 ON LED2
			}
		}
		else if(motor == Motor2)
		{
			if(direction == Right )
			{
				GPIO_ResetBits(INPUT3_PORT,INPUT3_Pin);			 // INPUT3 = 0
				GPIO_ResetBits(LED3_PORT,LED3_Pin);					 // INPUT3 ON LED3
				GPIO_SetBits(INPUT4_PORT,INPUT4_Pin);   	   // INPUT4 = 1
				GPIO_SetBits(LED4_PORT,LED4_Pin);					   // INPUT4 ON LED4
			}
			else if(direction == Left)
			{
				GPIO_SetBits(INPUT3_PORT,INPUT3_Pin);			   // INPUT3 = 1
				GPIO_SetBits(LED3_PORT,LED3_Pin);						 // INPUT3 ON LED3
				GPIO_ResetBits(INPUT4_PORT,INPUT4_Pin);   	 // INPUT4 = 0
				GPIO_ResetBits(LED4_PORT,LED4_Pin);					 // INPUT4 ON LED4
			}
		}
}

/******************************************************************************
                             Motor_Changespeed  
  * @brief  changes the spped of motor 
  * @param  motor specifies which of motor 1 or 2 	
			@arg		motor1 : motor 1 changes speed
			@arg    motor2 : motor 2 changes speed
	* @param	speed sets the RPM of motor
			@arg speed : integer between [0,500] RPM
  * @retval None
******************************************************************************/
void Motor_Changespeed(Motor motor,uint16_t speed)
{
	assert_param(IS_Motor(motor));
		if (motor==Motor1)
		{
			if(speed >= 500 ) 
			{	
				Channel3Pulse = (uint16_t) (((uint32_t) 1000 * (TimerPeriod - 1)) / 1000);
			}
			else if(speed < 500)
			{
				Channel3Pulse = (uint16_t) ((((uint32_t) (speed + 600)) * (TimerPeriod - 1)) / 1000);
			}
			// set pwm output
			TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
			TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		}
		else if(motor == Motor2)
		{
			if(speed >= 500 ) 
			{	
				Channel2Pulse = (uint16_t) ((((uint32_t) 1000) * (TimerPeriod - 1)) / 1000);
			}
			else if(speed < 500)
			{
				Channel2Pulse = (uint16_t) ((((uint32_t) (speed+600)) * (TimerPeriod - 1)) / 1000);
			}
			// set pwm output
			TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
			TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		}
}

/******************************************************************************
                             motor stop  
  * @brief  disable mootor 1 or 2
  * @param  motor specifies which of motor 1 or 2 stops	
			@arg		motor1 : motor 1 stops
			@arg    motor2 : motor 2 stops
  * @retval None
******************************************************************************/
void Motor_Stop(Motor motor)
{
	assert_param(IS_Motor(motor));
	if(motor == Motor1)
	{
		GPIO_SetBits(INPUT1_PORT,INPUT1_Pin);			 	 // INPUT1 = 1
		GPIO_SetBits(LED1_PORT,LED1_Pin);						 // INPUT1 ON LED1
		GPIO_SetBits(INPUT2_PORT,INPUT2_Pin);   	   // INPUT2 = 1
		GPIO_SetBits(LED2_PORT,LED2_Pin);					   // INPUT2 ON LED2
	}
	else if(motor == Motor2)
	{
		GPIO_SetBits(INPUT3_PORT,INPUT3_Pin);				 // INPUT3 = 1
		GPIO_SetBits(LED3_PORT,LED3_Pin);						 // INPUT3 ON LED3
		GPIO_SetBits(INPUT4_PORT,INPUT4_Pin);   		 // INPUT4 = 1
		GPIO_SetBits(LED4_PORT,LED4_Pin);				 		 // INPUT4 ON LED4
	}
}

