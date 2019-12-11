#include <stdio.h>
#include "stm32f10x.h"
#include "i2c_ee.h"
/** @addtogroup I2C_EEPROM
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define EEPROM_WriteAddress1    0x01
#define EEPROM_ReadAddress1     0x200
#define BufferSize1             sizeof(Tx1_Buffer)

uint8_t Tx1_Buffer[] = "STM32 EEPROM MEMORY TEST Naminic.com";
uint8_t Rx1_Buffer[256];

int main(void)
{

	 /* Initialize the I2C EEPROM driver ----------------------------------------*/
  I2C_EE_Init();
	
	memset(Rx1_Buffer,0,sizeof(Rx1_Buffer));
	
  I2C_EE_BufferWrite(Tx1_Buffer, EEPROM_ReadAddress1, BufferSize1);
	  /* First write in the memory followed by a read of the written data --------*/
  /* Write on I2C EEPROM from EEPROM_WriteAddress1 */
  I2C_EE_BufferWrite(Tx1_Buffer, EEPROM_WriteAddress1, BufferSize1);
	
	memset(Rx1_Buffer,0,sizeof(Rx1_Buffer));

  /* Read from I2C EEPROM from EEPROM_ReadAddress1 */
  I2C_EE_BufferRead(Rx1_Buffer, EEPROM_ReadAddress1, BufferSize1);
	
	while(1);
	
  return 0;
}