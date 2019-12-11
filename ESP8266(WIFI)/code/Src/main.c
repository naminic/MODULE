/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
typedef enum
{
  ESP_OK       		= 0x00U,
  ESP_ERROR    		= 0x01U,
  ESP_BUSY     		= 0x02U,
	ESP_IPD			 		= 0x03U,
	ESP_FAIL     		= 0x04U,
	ESP_DISCONNECT  = 0x05U, 
  ESP_TIMEOUT 	  = 0x06U,
	ESP_REDY				= 0x07U
} ESP_Status;


typedef enum
{
COMMAND_OK				=	0x00U,
COMMAND_ERROR			= 0x01U,
COMMAND_TIMEOUT		= 0x02U	
}ESP_CommandStatus;	

uint8_t Rec_Data;
int RxCounter = 0;
char RxBuffer[1000];
volatile ESP_Status reciveFlag = 0;
uint16_t len;	
char Command[50];
#define ESP_TimeOut 1000
char buffr[30];
char lenbuff[4];
char buff[200];
char *a1 ;
char *a2;
int  a3;
char flagof;


void delay(void)
{
	int tt;
	for(tt=0;tt<100000;tt++);
}

char WIFI_Connected = 0;
char WIFI_Get_IP = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
#define ResetFrame memset(RxBuffer,0x00,sizeof(RxBuffer));

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void  ESP_Callback(char *pBuff,uint16_t len)
{
  if(strstr(pBuff,"LED1_ON"))
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
		flagof = 1;
	}
  else if(strstr(pBuff,"LED1_OFF")) 
	{
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
		flagof = 2;
	} 		
	

}	


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    HAL_UART_Receive_IT(&huart1,&Rec_Data,1);
    RxBuffer[RxCounter++] = Rec_Data;
	  if( RxBuffer[RxCounter - 1] == 0x0a && RxBuffer[RxCounter - 2] == 0x0d && RxBuffer[RxCounter - 3] == 'K' && RxBuffer[RxCounter - 4] == 'O')
		{
				reciveFlag = ESP_OK ;
			  delay();
				RxCounter = 0x00;
		} 
		if( RxBuffer[RxCounter - 4] == 'E' &&  RxBuffer[RxCounter - 4] == 'R' && RxBuffer[RxCounter - 3] == 'R' && RxBuffer[RxCounter - 2] == 'O' && RxBuffer[RxCounter - 1] == 'R')
		{
				reciveFlag = ESP_ERROR ;
				RxCounter = 0x00;
		}
		if( RxBuffer[RxCounter - 4] == 'F' && RxBuffer[RxCounter - 3] == 'A' && RxBuffer[RxCounter - 2] == 'I' && RxBuffer[RxCounter - 1] == 'L')
	  {
				reciveFlag = ESP_FAIL ;
				RxCounter = 0x00;
		}
		if( RxBuffer[RxCounter - 4] == 'D' &&   RxBuffer[RxCounter - 4] == 'I' &&   RxBuffer[RxCounter - 4] == 'S' &&   RxBuffer[RxCounter - 4] == 'C' &&   RxBuffer[RxCounter - 4] == 'O' &&   RxBuffer[RxCounter - 4] == 'N' &&  RxBuffer[RxCounter - 4] == 'N' && RxBuffer[RxCounter - 3] == 'E' && RxBuffer[RxCounter - 2] == 'C' && RxBuffer[RxCounter - 1] == 'T')
		{
				reciveFlag = ESP_DISCONNECT ;
				RxCounter = 0x00;
		}		
		if(strstr(RxBuffer,"\r\n+IPD,") && RxBuffer[RxCounter - 3] == 'E' && RxBuffer[RxCounter - 2] == 'N'  && RxBuffer[RxCounter - 1] == 'D')
		//if(strstr(RxBuffer,"\r\n+IPD,"))
		{
								
     delay();

			a1 = strstr(RxBuffer,",");
			a2 = strstr(RxBuffer,":");
			a3 = a2 - a1 - 1;
			delay();

      strncpy  (lenbuff,a1 + 1,a3);
			len = atoi(lenbuff) - 3;
     // strncpy (buffr,a2 + 1,len) ;
			
			
			ESP_Callback(a2 + 1,len);
			ResetFrame
			RxCounter = 0x00;

		}
}









ESP_Status Send_Command(char *command,uint32_t Timeout)
{
	  uint32_t tickstart = 0U;
	  reciveFlag = ESP_REDY;
	
    HAL_UART_Transmit(&huart1,(uint8_t*)command,strlen(command),Timeout); 
	  tickstart = HAL_GetTick();
	
	  while(reciveFlag == ESP_REDY && ( HAL_GetTick() - tickstart ) < Timeout);
	
		if( ( HAL_GetTick() - tickstart ) >= Timeout )
		{
			return ESP_TIMEOUT;
		}
    else if( reciveFlag == ESP_OK)
    {
		  ResetFrame
			return ESP_OK;
		}	
		else if (reciveFlag == ESP_ERROR)
    {}			
		else if (reciveFlag == ESP_FAIL)
    {}	
		else if (reciveFlag == ESP_IPD)
    {
		  //ESP_Callback();
		  return ESP_OK;
		}	
		else if (reciveFlag == ESP_DISCONNECT)
    {}			
}


ESP_CommandStatus ESP_INIT(void)
{
	sprintf(Command,"AT+RST\r\n\r\n");
	
	if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
		return COMMAND_ERROR;
	
	sprintf(Command,"AT\r\n");
	
	if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
		return COMMAND_ERROR;
	
	  return COMMAND_OK;
}


ESP_CommandStatus  ESP_WIFI_MODE(uint8_t mode)
{
	 sprintf(Command,"AT+CWMODE=%d\r\n",mode); 
	
	 if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
		return COMMAND_ERROR;
	 
	 return COMMAND_OK;
}


ESP_CommandStatus		ESP_CIP_MODE(uint8_t mode)
{
	 sprintf(Command,"AT+CIPMODE=%d\r\n",mode); 
	
	 if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
		return COMMAND_ERROR;
	 
	 return COMMAND_OK;
}


ESP_CommandStatus  ESP_CIP_MUX(uint8_t mode)
{
	 sprintf(Command,"AT+CIPMUX=%d\r\n",mode); 
	
	 if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
		return COMMAND_ERROR;
	 
	 return COMMAND_OK;
}



ESP_CommandStatus  ESP_CW_SAP(char * ssid,char * pwd,uint8_t id,uint8_t enc)
{
	sprintf(Command,"AT+CWSAP=\"%s\",\"%s\",%d,%d\r\n",ssid,pwd,id,enc);
	
	if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
		return COMMAND_ERROR;
	 
	 return COMMAND_OK;
	
}


ESP_CommandStatus  ESP_SET_IP(char *ip)
{
	sprintf(Command,"AT+CIPAP=\"%s\"\r\n",ip); //Set IP
	
	if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
		return COMMAND_ERROR;
	 
	 return COMMAND_OK;
}	

ESP_CommandStatus  ESP_SET_SERVER(uint8_t mode,uint32_t port)
{

	sprintf(Command,"AT+CIPSERVER=%d,%d\r\n",mode,port); 

	if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
		return COMMAND_ERROR;
	 
	 return COMMAND_OK;	
}

ESP_CommandStatus  ESP_CONNECT_ROUTER(char *ssid,char *pwd)
{
  sprintf(Command,"AT+CWJAP=\"%s\",\"%s\"\r\n\r\n",ssid,pwd);
	
	if(Send_Command(Command,ESP_TimeOut * 20) != ESP_OK )
		return COMMAND_ERROR;	

	return COMMAND_OK;	
}


ESP_CommandStatus  ESP_CONNECT_UDPSERVER(char *ip,int port)
{
  sprintf(Command,"AT+CIPSTART=\"UDP\",\"%s\",%d,4540\r\n\r\n",ip,port);
	
	if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
		return COMMAND_ERROR;		
	
	return COMMAND_OK;	
}	

ESP_CommandStatus  ESP_CONNECT_TCPSERVER(char *ip,int port)
{
  sprintf(Command,"AT+CIPSTART=\"TCP\",\"%s\",%d,4540\r\n\r\n",ip,port);
	
	if(Send_Command(Command,ESP_TimeOut * 5) != ESP_OK )
		return COMMAND_ERROR;		
	
	return COMMAND_OK;	
}	

ESP_CommandStatus  ESP_SEND_DATA(char *data,unsigned short len)
{
  sprintf(Command,"AT+CIPSEND=%d\r\n\r\n",len);
	
	if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
			return COMMAND_ERROR;	
	
	sprintf(Command,"%s\r\n\r\n",data);
	
	if(Send_Command(Command,ESP_TimeOut) != ESP_OK )
			return COMMAND_ERROR;

  return COMMAND_OK;			

}	


/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */   

    
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  /* USER CODE BEGIN 2 */
    HAL_Delay(500); 
    HAL_UART_Receive_IT(&huart1,&Rec_Data,1);
   do
	 {
		HAL_Delay(2000);
	 }while(ESP_INIT() != COMMAND_OK);
		 

	 
//	 if(ESP_WIFI_MODE(2) != COMMAND_OK)
//	 {
//	   while(1);
//	 }
//	 if(ESP_CIP_MUX(0) != COMMAND_OK)
//	 {
//	   while(1);
//	 }
//	 if(ESP_CIP_MUX(1) != COMMAND_OK)
//	 {
//	   while(1);
//	 }
//	 if(ESP_CW_SAP("Naminic.com","12345678",6,4) != COMMAND_OK)
//	 {
//	   while(1);
//	 }
//	 if(ESP_SET_IP("192.168.1.7") != COMMAND_OK)
//	 {
//	   while(1);
//	 }
//	 if(ESP_SET_SERVER(1,1000) != COMMAND_OK)
//	 {
//	   while(1);
//	 }
	 
	 
	 if(ESP_WIFI_MODE(1) != COMMAND_OK)
	 {
	   while(1);
	 }
	 if(ESP_CONNECT_ROUTER("naminic","naminics") != COMMAND_OK)
	 {
	   while(1);
	 }
	 
	 if(ESP_CONNECT_TCPSERVER("172.20.10.2",1000) != COMMAND_OK)
	 {
	   while(1);
	 }
  
   HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		if(flagof == 1 )
		{	
			ESP_SEND_DATA("ON",2);
				flagof = 0;
		//HAL_Delay(2000);
		}
		if(flagof == 2 )
		{			
			ESP_SEND_DATA("OFF",3);
				flagof = 0;	
		}
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */  
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /**Configure the Systick interrupt time 
    */
  __HAL_RCC_PLLI2S_ENABLE();

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED1_Pin LED2_Pin LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
