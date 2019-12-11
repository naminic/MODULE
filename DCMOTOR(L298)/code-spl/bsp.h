#include "stm32f10x_gpio.h"

/******************************************************************************
                      LED 
******************************************************************************/
#define LEDn                             4
#define LED_CLK          					 		 	 RCC_APB2Periph_GPIOC

#define LED1_Pin                         GPIO_Pin_2            /* PC.2 */
#define LED1_PORT                  			 GPIOC
 
#define LED2_Pin                         GPIO_Pin_3            /* PC.3 */
#define LED2_PORT                 		   GPIOC

#define LED3_Pin                         GPIO_Pin_4            /* PC.4 */
#define LED3_PORT                   	   GPIOC

#define LED4_Pin                         GPIO_Pin_5            /* PC.5 */
#define LED4_PORT                        GPIOC

/******************************************************************************
                      PWM 
******************************************************************************/

#define PWM1_Pin												 GPIO_Pin_14           /* PD.14 */
#define PWM1_PORT												 GPIOD
#define PWM1_CLK												 RCC_APB1Periph_TIM4

#define PWM2_Pin												 GPIO_Pin_13           /* PD.13 */
#define PWM2_PORT												 GPIOD
#define PWM2_CLK												 RCC_APB1Periph_TIM4

#define PWM3_Pin												 GPIO_Pin_12           /* PD.13 */
#define PWM3_PORT												 GPIOD
#define PWM3_CLK												 RCC_APB1Periph_TIM4

/******************************************************************************
                      INPUTS 
******************************************************************************/
#define INPUT1_Pin 												 GPIO_Pin_0            /* PB.0 */
#define INPUT1_PORT												 GPIOB
#define INPUT1_CLK												 RCC_APB2Periph_GPIOB

#define INPUT2_Pin 												 GPIO_Pin_1            /* PB.1 */
#define INPUT2_PORT												 GPIOB
#define INPUT2_CLK												 RCC_APB2Periph_GPIOB

#define INPUT3_Pin 												 GPIO_Pin_0            /* PA.0 */
#define INPUT3_PORT												 GPIOA
#define INPUT3_CLK												 RCC_APB2Periph_GPIOA

#define INPUT4_Pin 												 GPIO_Pin_3            /* PA.3 */
#define INPUT4_PORT												 GPIOA
#define INPUT4_CLK												 RCC_APB2Periph_GPIOA



/******************************************************************************
                      ADC 
******************************************************************************/

//#define ADC1_Pin 												 GPIO_Pin_0            /* PB.0 */
//#define ADC1_PORT												 GPIOB
//#define ADC1_CLK												 RCC_APB2Periph_ADC1

//#define ADC2_Pin 												 GPIO_Pin_0            /* PB.1 */
//#define ADC2_PORT												 GPIOB
//#define ADC2_CLK												 RCC_APB2Periph_ADC2

//#define ADC3_Pin 												 GPIO_Pin_0            /* PA.0 */
//#define ADC3_PORT												 GPIOB
//#define ADC3_CLK												 RCC_APB2Periph_ADC3

//#define ADC4_Pin 												 GPIO_Pin_0            /* PA.3 */
//#define ADC4_PORT												 GPIOB
//#define ADC4_CLK												 RCC_APB2Periph_ADC4

void PWM_Intial(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void MOTOR1_rotate(char);
void MOTOR2_rotate(char);
void MOTOR1_ChangeSpeed(uint16_t);
void MOTOR2_ChangeSpeed(uint16_t);
void MOTOR1_Stop(void);
void MOTOR2_Stop(void);
