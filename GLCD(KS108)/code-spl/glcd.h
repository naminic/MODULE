
#define GLCD_RS_PIN		GPIO_Pin_9
#define GLCD_RS_PORT	GPIOE

#define GLCD_RW_PIN		GPIO_Pin_11
#define GLCD_RW_PORT	GPIOE

#define GLCD_EN_PIN		GPIO_Pin_13
#define GLCD_EN_PORT	GPIOE

#define GLCD_CS1_PIN	GPIO_Pin_12	
#define GLCD_CS1_PORT	GPIOE

#define GLCD_CS2_PIN	GPIO_Pin_10
#define GLCD_CS2_PORT	GPIOE

#define GLCD_RST_PIN	  GPIO_Pin_8
#define GLCD_RST_PORT	  GPIOE

#define KS0108_SCREEN_WIDTH		128
#define KS0108_SCREEN_HEIGHT 	64
#define DISPLAY_SET_Y      	 	0x40
#define DISPLAY_SET_X       	0xB8
#define DISPLAY_START_LINE  	0xC0
#define DISPLAY_ON_CMD				0x3E
#define ON	0x01

void glcd_init();
static void DATAPORT(char val);
void GLCD_DisableController(unsigned char controller);
void GLCD_EnableController(unsigned char controller);
void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller);
void GLCD_WriteData(unsigned char dataToWrite);
void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller);
void GLCD_WriteData(unsigned char dataToWrite);
void GLCD_GoTo(unsigned char x, unsigned char y);
void putpixel(unsigned int x, unsigned int y);
void GLCD_ClearScreen(void);
unsigned char GLCD_ReadByteFromROMMemory(char * ptr);
void GLCD_WriteString(char * stringToWrite);
void SetPage(unsigned char x);
void SetColumn(unsigned char y);
void Number_font(unsigned char x,unsigned char y,int Num);
void GLCD_Line(unsigned int X1,unsigned int Y1,unsigned int X2,unsigned int Y2);
