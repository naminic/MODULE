/* Includes ------------------------------------------------------------------*/
#include "main.h"


#define SPI_RC522                 SPI2
#define SPI_RC522_CLK             RCC_APB1Periph_SPI2
#define SPI_RC522_AF              GPIO_AF_SPI2

#define SPI_RC522_PIN_SCK         GPIO_Pin_13
#define SPI_RC522_SCK_CLK         RCC_AHB1Periph_GPIOB
#define SPI_RC522_GPIO_SCK        GPIOB
#define SPI_RC522_SCK_SOURCE      GPIO_PinSource13


#define SPI_RC522_PIN_MISO        GPIO_Pin_14
#define SPI_RC522_MISO_CLK        RCC_AHB1Periph_GPIOB
#define SPI_RC522_GPIO_MISO       GPIOB
#define SPI_RC522_MISO_SOURCE     GPIO_PinSource14


#define SPI_RC522_PIN_MOSI        GPIO_Pin_15
#define SPI_RC522_MOSI_CLK        RCC_AHB1Periph_GPIOB
#define SPI_RC522_GPIO_MOSI       GPIOB
#define SPI_RC522_MOSI_SOURCE     GPIO_PinSource15


#define SPI_RC522_CS             GPIO_Pin_15
#define SPI_RC522_CS_GPIO        GPIOE
#define SPI_RC522_CS_GPIO_CLK    RCC_AHB1Periph_GPIOE

#define SPI_RC522_RS             GPIO_Pin_12
#define SPI_RC522_RS_GPIO        GPIOB
#define SPI_RC522_RS_GPIO_CLK    RCC_AHB1Periph_GPIOB

#define 	SPI_I2S_FLAG_BSY	((uint16_t)0x0080)
//#define 	SPI1_NSS_ON()		GPIO_ResetBits(GPIOC,GPIO_Pin_4)//nuzhat
//#define 	SPI1_NSS_OFF()		GPIO_SetBits(GPIOC,GPIO_Pin_4)
#define 	SPI1_NSS_ON()		GPIO_ResetBits(SPI_RC522_CS_GPIO,SPI_RC522_CS)
#define 	SPI1_NSS_OFF()		GPIO_SetBits(SPI_RC522_CS_GPIO,SPI_RC522_CS)

extern void init_RC522(void);
extern uint8_t RC522_SendByte(uint8_t data);
extern void RC522_WriteReg(uint8_t address, uint8_t value);
extern uint8_t RC522_ReadReg(uint8_t address);


