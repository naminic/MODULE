
#include "stm32f10x.h"

/******************************************************************************
                      Relays 
******************************************************************************/
#define Relayn                             4

#define Relay1    1
#define Relay2    2
#define Relay3    3
#define Relay4    4

#define Relays_GPIO_PORT                   GPIOC
#define Relays_GPIO_CLK                    RCC_APB2Periph_GPIOC

#define Relay1_PIN                         GPIO_Pin_9    
#define Relay1_GPIO_PORT                   GPIOC
#define Relay1_GPIO_CLK          				   RCC_APB2Periph_GPIOC
  
#define Relay2_PIN                         GPIO_Pin_8      
#define Relay2_GPIO_PORT                   GPIOC
#define Relay2_GPIO_CLK										 RCC_APB2Periph_GPIOC


#define Relay3_PIN                         GPIO_Pin_7          
#define Relay3_GPIO_PORT                   GPIOC
#define Relay3_GPIO_CLK  									 RCC_APB2Periph_GPIOC


#define Relay4_PIN                         GPIO_Pin_6         
#define Relay4_GPIO_PORT                   GPIOC
#define Relay4_GPIO_CLK										 RCC_APB2Periph_GPIOC
/******************************************************************************
                      DIGITAL INPUTS 
******************************************************************************/
#define DInput1    1
#define DInput2    2
#define DInput3    3
#define DInput4    4

#define Relays_GPIO_PORT                    GPIOC
#define Relays_GPIO_CLK                     RCC_APB2Periph_GPIOC

#define DInput1_PIN                         GPIO_Pin_5  
#define DInput1_GPIO_PORT                   GPIOC
#define DInput1_GPIO_CLK          				  RCC_APB2Periph_GPIOC
  
#define DInput2_PIN                         GPIO_Pin_4      
#define DInput2_GPIO_PORT                   GPIOC
#define DInput2_GPIO_CLK									  RCC_APB2Periph_GPIOC


#define DInput3_PIN                         GPIO_Pin_3         
#define DInput3_GPIO_PORT                   GPIOC
#define DInput3_GPIO_CLK  									RCC_APB2Periph_GPIOC


#define DInput4_PIN                          GPIO_Pin_2         
#define DInput4_GPIO_PORT                   GPIOC
#define DInput4_GPIO_CLK  								  RCC_APB2Periph_GPIOC

void RCC_Configuration(void);
void GPIO_Configuration(void);

