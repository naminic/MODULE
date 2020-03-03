#include "main.h"
#include "gpio.h"
#include "rc522-spi.h"

extern SPI_HandleTypeDef hspi3;

#define SPI1_NSS_ON 		HAL_GPIO_WritePin(RC522_CS_GPIO_Port,RC522_CS_Pin,0);
#define SPI1_NSS_OFF		HAL_GPIO_WritePin(RC522_CS_GPIO_Port,RC522_CS_Pin,1);



void init_RC522(void) {
	HAL_GPIO_WritePin(RC522_RST_GPIO_Port,RC522_RST_Pin,0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(RC522_RST_GPIO_Port,RC522_RST_Pin,1);

}

uint8_t RC522_SendByte(uint8_t data) {
    unsigned char Rec_data = 0;
    HAL_SPI_TransmitReceive(&hspi3,&data,&Rec_data,1,1000);
    return Rec_data;		         					
}





void RC522_WriteReg(uint8_t address, uint8_t value) {
	SPI1_NSS_ON										// CS_Low
	RC522_SendByte(address);
	RC522_SendByte(value);
	SPI1_NSS_OFF									// CS_HIGH
}



uint8_t RC522_ReadReg(uint8_t address){
	uint8_t	val;
	SPI1_NSS_ON										// CS_Low
	RC522_SendByte(address);
	val = RC522_SendByte(0x00);
	SPI1_NSS_OFF										// CS_HIGH
	return val;
}
