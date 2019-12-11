
#include "stm32f10x_gpio.h"

/******************************************************************************
               LED CONFIG
******************************************************************************/
#define LEDn                             4

#define LED1_PIN                         GPIO_Pin_0           /* PB.0*/
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK          					 RCC_APB2Periph_GPIOB
  
#define LED2_PIN                         GPIO_Pin_6            /* PF.06*/
#define LED2_GPIO_PORT                   GPIOF
#define LED2_GPIO_CLK										 RCC_APB2Periph_GPIOF


#define LED3_PIN                         GPIO_Pin_7            /* PG.07*/
#define LED3_GPIO_PORT                   GPIOG
#define LED3_GPIO_CLK  									 RCC_APB2Periph_GPIOG


#define LED4_PIN                         GPIO_Pin_11            /* PF.11*/
#define LED4_GPIO_PORT                   GPIOF
#define LED4_GPIO_CLK										 RCC_APB2Periph_GPIOF
/******************************************************************************
               KEY CONFIG
******************************************************************************/
#define KEYn                             4

#define KEY1_PIN                         GPIO_Pin_3           /* PE.03*/
#define KEY1_GPIO_PORT                   GPIOE
#define KEY1_GPIO_CLK          					 RCC_APB2Periph_GPIOE
  
#define KEY2_PIN                         GPIO_Pin_4            /* PE.04*/
#define KEY2_GPIO_PORT                   GPIOE
#define KEY2_GPIO_CLK										 RCC_APB2Periph_GPIOE


#define KEY3_PIN                         GPIO_Pin_5            /* PE.05*/
#define KEY3_GPIO_PORT                   GPIOE
#define KEY3_GPIO_CLK  									 RCC_APB2Periph_GPIOE


#define KEY4_PIN                         GPIO_Pin_6            /* PE.06*/
#define KEY4_GPIO_PORT                   GPIOE
#define KEY4_GPIO_CLK										 RCC_APB2Periph_GPIOE
/******************************************************************************
               SERIAL TO USB
******************************************************************************/

#define COM1             USART1
#define COM1_CLK				 RCC_APB2Periph_USART1
#define COM1_TXD_PIN		 GPIO_Pin_9
#define COM1_RXD_PIN     GPIO_Pin_10
#define COM1_CLK_PORT	   RCC_APB2Periph_GPIOA
#define COM1_PORT        GPIOA
