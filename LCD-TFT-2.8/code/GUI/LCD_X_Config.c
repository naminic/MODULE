/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2012  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.16 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCD_X_SPI_LPC1700.c
Purpose     : Port routines for LPC1700 SPI
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "main.h"

/*********************************************************************
*
*       Hardware configuration
*
**********************************************************************
*/

#define LCD_CS(x)    HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,x);

#define LCD_RS(x)    HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin,x);

#define LCD_WR(x)    HAL_GPIO_WritePin(LCD_WR_GPIO_Port,LCD_WR_Pin,x);

#define LCD_RD(x)    HAL_GPIO_WritePin(LCD_RD_GPIO_Port,LCD_RD_Pin,x);

#define LCD_RST(x)   HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,x);




/*********************************************************************
*
*       LCD_X_Init
*
* Purpose:
*   This routine should be called from your application program
*   to set port pins to their initial values
*/
void LCD_X_Init(void) {
	  LCD_RST(0)
	  LCD_RST(1)	
}

/*********************************************************************
*
*       LCD_X_Write00_16
*
* Purpose:
*   Write to controller, with A0 = 0 register
*/
void LCD_X_Write00_16(U16 c) {

  LCD_RS(0)
  LCD_RD(1)
  GPIOE->ODR = c;
  LCD_WR(0)
  LCD_WR(1)
	
}

/*********************************************************************
*
*       LCD_X_Write01_16
*
* Purpose:
*   Write to controller, with A0 = 1   data
*/
void LCD_X_Write01_16(U16 c) {
  LCD_RS(1)
  LCD_RD(1)
  GPIOE->ODR = c;
  LCD_WR(0)
  LCD_WR(1)
}

/*********************************************************************
*
*       LCD_X_Read01_16
*
* Purpose:
*   Read from controller, with A0 = 1
*/
U16 LCD_X_Read01_16(void) {
	
	GPIOE->CRH = 0x44444444;
	GPIOE->CRL = 0x44444444;
  U16 c =0;
  LCD_RS(1)
  LCD_WR(1)
  LCD_RD(0)
  c = ((uint16_t)GPIOE->IDR);
  LCD_RD(1)
	GPIOE->CRH = 0x22222222;
	GPIOE->CRL = 0x22222222;
	
  return c;
}

/*********************************************************************
*
*       LCD_X_WriteM01_16
*
* Purpose:
*   Write multiple bytes to controller, with A0 = 1
*/
void LCD_X_WriteM01_16(U16 * pData, int NumWords) {
	
   for (; NumWords; NumWords--)
	 {
		 LCD_X_Write01_16(*pData);
		 pData++;
   }
	 
}

/*********************************************************************
*
*       LCD_X_ReadM01_16
*
* Purpose:
*   Read multiple bytes from controller, with A0 = 1
*/


void LCD_X_ReadM01_16(U16 * pData, int NumWords) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIOE->CRH = 0x44444444;
	GPIOE->CRL = 0x44444444;
  LCD_RS(1)
  LCD_WR(1)
  LCD_RD(0)
	  
		 for (; NumWords; NumWords--)
		 {
			 *pData = ((uint16_t)GPIOE->IDR);
			 pData++;
		 }
	 
	LCD_RD(1) 
	GPIOE->CRH = 0x22222222;
	GPIOE->CRL = 0x22222222;
}

/*************************** End of file ****************************/
