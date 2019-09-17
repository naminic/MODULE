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
File        : LCDConf.c
Purpose     : Display controller configuration

              Display:        Ampire 240320L8
              Controller:     Ilitek ILI9320

              Display:        Ampire 240320LD
              Controller:     OriseTech SPFD5408,
                              Raydium RM68050

              Display:        Ampire 240320LG
              Controller:     Himax HX8347-D

              Display driver: GUIDRV_FlexColor
              Operation mode: 16bpp, 16-bit interface or SPI

---------------------------END-OF-HEADER------------------------------
*/

#include "GUI.h"
#include "GUIDRV_FlexColor.h"

/*********************************************************************
*
*       Layer configuration
*
**********************************************************************
*/

#define lcd9325


#define XSIZE_PHYS 240		

#ifdef lcd9325
#define YSIZE_PHYS 320
#else
#define YSIZE_PHYS 400
#endif
//
// Color conversion
//
#define COLOR_CONVERSION GUICC_565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// Buffers / VScreens
//
#define NUM_BUFFERS   1
#define NUM_VSCREENS  1

//
// Display orientation
//
//#define DISPLAY_ORIENTATION  0
//#define DISPLAY_ORIENTATION               (GUI_MIRROR_X | GUI_MIRROR_Y)
//  #define DISPLAY_ORIENTATION (GUI_SWAP_XY | GUI_MIRROR_Y)
////////#define DISPLAY_ORIENTATION (GUI_SWAP_XY | GUI_MIRROR_X)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_X)
//#define DISPLAY_ORIENTATION (GUI_MIRROR_Y)
#define DISPLAY_ORIENTATION ( GUI_SWAP_XY | GUI_MIRROR_Y )

//
// Touch screen
//
#define USE_TOUCH   0
//
// Touch screen calibration
#define TOUCH_X_MIN 0x00E0
#define TOUCH_X_MAX 0x0F40
#define TOUCH_Y_MIN 0x00C0
#define TOUCH_Y_MAX 0x0F60

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
// #ifndef   XSIZE_PHYS
//   #error Physical X size of display is not defined!
// #endif
// #ifndef   YSIZE_PHYS
//   #error Physical Y size of display is not defined!
// #endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif
#ifndef   NUM_VSCREENS
  #define NUM_VSCREENS 1
#else
  #if (NUM_VSCREENS <= 0)
    #error At least one screeen needs to be defined!
  #endif
#endif
#if (NUM_VSCREENS > 1) && (NUM_BUFFERS > 1)
  #error Virtual screens and multiple buffers are not allowed!
#endif
#ifndef   DISPLAY_ORIENTATION
  #define DISPLAY_ORIENTATION  0
#endif

#if ((DISPLAY_ORIENTATION & GUI_SWAP_XY) != 0)
#define LANDSCAPE   1
#else
#define LANDSCAPE   0
#endif

#if (LANDSCAPE == 1)
#define WIDTH       YSIZE_PHYS  /* Screen Width (in pixels)         */
#define HEIGHT      XSIZE_PHYS  /* Screen Hight (in pixels)         */
#else
#define WIDTH       XSIZE_PHYS  /* Screen Width (in pixels)         */
#define HEIGHT      YSIZE_PHYS  /* Screen Hight (in pixels)         */
#endif

#if ((DISPLAY_ORIENTATION & GUI_SWAP_XY) != 0)
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_X) != 0)
    #define TOUCH_TOP    TOUCH_X_MAX
    #define TOUCH_BOTTOM TOUCH_X_MIN
  #else
    #define TOUCH_TOP    TOUCH_X_MIN
    #define TOUCH_BOTTOM TOUCH_X_MAX
  #endif
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_Y) != 0)
    #define TOUCH_LEFT   TOUCH_Y_MAX
    #define TOUCH_RIGHT  TOUCH_Y_MIN
  #else
    #define TOUCH_LEFT   TOUCH_Y_MIN
    #define TOUCH_RIGHT  TOUCH_Y_MAX
  #endif
#else
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_X) != 0)
    #define TOUCH_LEFT   TOUCH_X_MAX
    #define TOUCH_RIGHT  TOUCH_X_MIN
  #else
    #define TOUCH_LEFT   TOUCH_X_MIN
    #define TOUCH_RIGHT  TOUCH_X_MAX
  #endif
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_Y) != 0)
    #define TOUCH_TOP    TOUCH_Y_MAX
    #define TOUCH_BOTTOM TOUCH_Y_MIN
  #else
    #define TOUCH_TOP    TOUCH_Y_MIN
    #define TOUCH_BOTTOM TOUCH_Y_MAX
  #endif
#endif

/*********************************************************************
*
*       Driver Port functions
*
**********************************************************************
*/
extern void LCD_X_Init(void);
extern void LCD_X_Write00_16(U16 c);
extern void LCD_X_Write01_16(U16 c);
extern U16  LCD_X_Read01_16 (void);
extern void LCD_X_WriteM01_16(U16 * pData, int NumWords);
extern void LCD_X_ReadM01_16 (U16 * pData, int NumWords);

/*********************************************************************
*
*       Private code
*
**********************************************************************
*/
static void delay (int cnt) {
  cnt <<= 15;
  while (cnt--);
}

static void wr_reg (U16 reg, U16 dat) {
  LCD_X_Write00_16(reg);
  LCD_X_Write01_16(dat);
}

static U16 rd_reg (U16 reg) {
  LCD_X_Write00_16(reg);
  return LCD_X_Read01_16();
}



/* LCD Command Codes */
#define TS_INS_START_OSC            0x00
#define TS_INS_DRIV_OUT_CTRL        0x01
#define TS_INS_DRIV_WAV_CTRL        0x02
#define TS_INS_ENTRY_MOD            0x03
#define TS_INS_RESIZE_CTRL          0x04
#define TS_INS_DISP_CTRL1           0x07
#define TS_INS_DISP_CTRL2           0x08
#define TS_INS_DISP_CTRL3           0x09
#define TS_INS_DISP_CTRL4           0x0A
#define TS_INS_RGB_DISP_IF_CTRL1    0x0C
#define TS_INS_FRM_MARKER_POS       0x0D
#define TS_INS_RGB_DISP_IF_CTRL2    0x0F
#define TS_INS_POW_CTRL1            0x10
#define TS_INS_POW_CTRL2            0x11
#define TS_INS_POW_CTRL3            0x12
#define TS_INS_POW_CTRL4            0x13
#define TS_INS_GRAM_HOR_AD          0x20
#define TS_INS_GRAM_VER_AD          0x21
#define TS_INS_RW_GRAM              0x22
#define TS_INS_POW_CTRL7            0x29
#define TS_INS_FRM_RATE_COL_CTRL    0x2B
#define TS_INS_GAMMA_CTRL1          0x30
#define TS_INS_GAMMA_CTRL2          0x31
#define TS_INS_GAMMA_CTRL3          0x32
#define TS_INS_GAMMA_CTRL4          0x35 
#define TS_INS_GAMMA_CTRL5          0x36
#define TS_INS_GAMMA_CTRL6          0x37
#define TS_INS_GAMMA_CTRL7          0x38
#define TS_INS_GAMMA_CTRL8          0x39
#define TS_INS_GAMMA_CTRL9          0x3C
#define TS_INS_GAMMA_CTRL10         0x3D
#define TS_INS_HOR_START_AD         0x50
#define TS_INS_HOR_END_AD           0x51
#define TS_INS_VER_START_AD         0x52
#define TS_INS_VER_END_AD           0x53
#define TS_INS_GATE_SCAN_CTRL1      0x60
#define TS_INS_GATE_SCAN_CTRL2      0x61
#define TS_INS_GATE_SCAN_CTRL3      0x6A
#define TS_INS_PART_IMG1_DISP_POS   0x80
#define TS_INS_PART_IMG1_START_AD   0x81
#define TS_INS_PART_IMG1_END_AD     0x82
#define TS_INS_PART_IMG2_DISP_POS   0x83
#define TS_INS_PART_IMG2_START_AD   0x84
#define TS_INS_PART_IMG2_END_AD     0x85
#define TS_INS_PANEL_IF_CTRL1       0x90
#define TS_INS_PANEL_IF_CTRL2       0x92
#define TS_INS_PANEL_IF_CTRL3       0x93
#define TS_INS_PANEL_IF_CTRL4       0x95
#define TS_INS_PANEL_IF_CTRL5       0x97
#define TS_INS_PANEL_IF_CTRL6       0x98  

#define TS_VAL_ENTRY_MOD            0x0030

U16 driverCode;
/*********************************************************************
*
*       _InitController
*
* Purpose:
*   Initializes the display controller
*/
static void _InitController(void) {
#ifndef WIN32
  
	
	LCD_X_Init();

 

  driverCode = rd_reg(0x00);
	driverCode = 0x9325;
	if(driverCode == 0x9325)
	{
		LCD_X_Write00_16(0x00E3);
		LCD_X_Write01_16(0x3008); 					//set the internal timing
		LCD_X_Write00_16(0x00E7);
		LCD_X_Write01_16(0x0012); 					//set the internal timing
		LCD_X_Write00_16(0x00EF);
		LCD_X_Write01_16(0x1231); 					//set the internal timing
		LCD_X_Write00_16(TS_INS_START_OSC);
		LCD_X_Write01_16(0x0001); 					//start oscillator
		delay(50);

		LCD_X_Write00_16(TS_INS_DRIV_OUT_CTRL);
		LCD_X_Write01_16(0x0100); 					//set SS, SM
		LCD_X_Write00_16(TS_INS_DRIV_WAV_CTRL);
		LCD_X_Write01_16(0x0700); 					//set 1 line inversion
	
		LCD_X_Write00_16(TS_INS_ENTRY_MOD);
		LCD_X_Write01_16(TS_VAL_ENTRY_MOD);			//set GRAM write direction, BGR=0

		LCD_X_Write00_16(TS_INS_RESIZE_CTRL);
		LCD_X_Write01_16(0x0000); 					//no resizing

		LCD_X_Write00_16(TS_INS_DISP_CTRL2);
		LCD_X_Write01_16(0x0202); 					//front & back porch periods = 2
		LCD_X_Write00_16(TS_INS_DISP_CTRL3);
		LCD_X_Write01_16(0x0000); 					
		LCD_X_Write00_16(TS_INS_DISP_CTRL4);
		LCD_X_Write01_16(0x0000); 					
		LCD_X_Write00_16(TS_INS_RGB_DISP_IF_CTRL1);
		LCD_X_Write01_16(0x0000); 					//select system interface				
		LCD_X_Write00_16(TS_INS_FRM_MARKER_POS);
		LCD_X_Write01_16(0x0000); 					
		LCD_X_Write00_16(TS_INS_RGB_DISP_IF_CTRL2);
		LCD_X_Write01_16(0x0000);					
	
		LCD_X_Write00_16(TS_INS_POW_CTRL1);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_POW_CTRL2);
		LCD_X_Write01_16(0x0007); 					
		LCD_X_Write00_16(TS_INS_POW_CTRL3);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_POW_CTRL4);
		LCD_X_Write01_16(0x0000); 					
		delay(200);

		LCD_X_Write00_16(TS_INS_POW_CTRL1);
		LCD_X_Write01_16(0x1690);
		LCD_X_Write00_16(TS_INS_POW_CTRL2);
		LCD_X_Write01_16(0x0227); //LCD_X_Write01_16(0x0137); 					
		delay(50);

		LCD_X_Write00_16(TS_INS_POW_CTRL3);
		LCD_X_Write01_16(0x001A); //LCD_X_Write01_16(0x013C);
		delay(50);

		LCD_X_Write00_16(TS_INS_POW_CTRL4);
		LCD_X_Write01_16(0x1800); //LCD_X_Write01_16(0x1400);
		LCD_X_Write00_16(TS_INS_POW_CTRL7);
		LCD_X_Write01_16(0x002A); //LCD_X_Write01_16(0x0007);
		delay(50);

		LCD_X_Write00_16(TS_INS_GRAM_HOR_AD);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_GRAM_VER_AD);
		LCD_X_Write01_16(0x0000);

		LCD_X_Write00_16(TS_INS_GAMMA_CTRL1);
		LCD_X_Write01_16(0x0007);
		LCD_X_Write00_16(TS_INS_GAMMA_CTRL2);
		LCD_X_Write01_16(0x0605);
		LCD_X_Write00_16(TS_INS_GAMMA_CTRL3);
		LCD_X_Write01_16(0x0106);
		LCD_X_Write00_16(TS_INS_GAMMA_CTRL4);
		LCD_X_Write01_16(0x0206);
		LCD_X_Write00_16(TS_INS_GAMMA_CTRL5);
		LCD_X_Write01_16(0x0808);
		LCD_X_Write00_16(TS_INS_GAMMA_CTRL6);
		LCD_X_Write01_16(0x0007);
		LCD_X_Write00_16(TS_INS_GAMMA_CTRL7);
		LCD_X_Write01_16(0x0201);
		LCD_X_Write00_16(TS_INS_GAMMA_CTRL8);
		LCD_X_Write01_16(0x0007);
		LCD_X_Write00_16(TS_INS_GAMMA_CTRL9);
		LCD_X_Write01_16(0x0602);
		LCD_X_Write00_16(TS_INS_GAMMA_CTRL10);
		LCD_X_Write01_16(0x0808);

		LCD_X_Write00_16(TS_INS_HOR_START_AD);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_HOR_END_AD);
		LCD_X_Write01_16(0x00EF);
		LCD_X_Write00_16(TS_INS_VER_START_AD);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_VER_END_AD);
		LCD_X_Write01_16(0x013F);
		LCD_X_Write00_16(TS_INS_GATE_SCAN_CTRL1);
		LCD_X_Write01_16(0xA700);
		LCD_X_Write00_16(TS_INS_GATE_SCAN_CTRL2);
		LCD_X_Write01_16(0x0001);
		LCD_X_Write00_16(TS_INS_GATE_SCAN_CTRL3);
		LCD_X_Write01_16(0x0000);

		LCD_X_Write00_16(TS_INS_PART_IMG1_DISP_POS);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_PART_IMG1_START_AD);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_PART_IMG1_END_AD);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_PART_IMG2_DISP_POS);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_PART_IMG2_START_AD);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_PART_IMG2_END_AD);
		LCD_X_Write01_16(0x0000);

		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL1);
		LCD_X_Write01_16(0x0010);
		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL2);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL3);
		LCD_X_Write01_16(0x0003);
		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL4);
		LCD_X_Write01_16(0x0110);
		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL5);
		LCD_X_Write01_16(0x0000);
		LCD_X_Write00_16(TS_INS_PANEL_IF_CTRL6);
		LCD_X_Write01_16(0x0000);

		LCD_X_Write00_16(TS_INS_DISP_CTRL1);
		LCD_X_Write01_16(0x0133);
			}
else
{
	wr_reg(0x0000,0x0001);

	wr_reg(0x001A, 0x0004); // BT[3:0]=0100, VCL=-VCI; VGH=VCI+2DDVDH; VGL=-2DDVDH
	wr_reg(0x001B, 0x000C); // VRH[4:0]=0Ch, VREG1=(2.5v*1.9)=4.75V		VCIRE=1;
		// VCOM offset
	wr_reg(0x0023, 0x0000); // SELVCM=0, R24h and R25h selects VCOM
	wr_reg(0x0024, 0x0040); // VCM[6:0]=1000000, VCOMH voltage=VREG1*0.748 (originally 5F)
	wr_reg(0x0025, 0x000F); // VDV[4:0]=01111, VCOMH amplitude=VREG*1.00
	wr_reg(0x002D, 0x0006); // NOW[2:0]=110, Gate output non-overlap period = 6 clocks
	delay(20);
	// Power on Setting
	wr_reg(0x0018, 0x0008); // RADJ[3:0]=1000, Display frame rate 60Hz 100%
	wr_reg(0x0019, 0x0001); // OSC_EN=1, start OSC
	delay(20);
	wr_reg(0x0001, 0x0000); // DSTB=0, out deep sleep
	wr_reg(0x001F, 0x0088); // STB=0
	wr_reg(0x001C, 0x0006); // AP[2:0]=110, High OPAMP current (default 011)
	delay(10);
	wr_reg(0x001F, 0x0080); // DK=0
	delay(10);
	wr_reg(0x001F, 0x0090); // PON=1
	delay(5);
	wr_reg(0x001F, 0x00D0); // VCOMG=1
	delay(10);
	wr_reg(0x0017, 0x0005); // IFPF[2:0]=101, 16-bit/pixel

	// Panel Configuration
	//wr_reg(0x0036, 0x0011); // REV_PANEL=1, SM_PANEL=1, GS_PANEL=1, SS_PANEL=1
	//wr_reg(0x0029, 0x0031); // NL[5:0]=110001, 400 lines
	//wr_reg(0x0071, 0x001A); // RTN0


	//Gamma 2.2 Setting

	wr_reg(0x0040, 0x0000);
	wr_reg(0x0041, 0x0009);
	wr_reg(0x0042, 0x0012);
	wr_reg(0x0043, 0x0004);
	wr_reg(0x0044, 0x0000);
	wr_reg(0x0045, 0x0023);//
	wr_reg(0x0046, 0x0003);
	wr_reg(0x0047, 0x005E);//
	wr_reg(0x0048, 0x0000);
	wr_reg(0x0049, 0x0000);
	wr_reg(0x004A, 0x0000);
	wr_reg(0x004B, 0x0000);
	wr_reg(0x004C, 0x0000);
	wr_reg(0x004D, 0x0000);
	wr_reg(0x004E, 0x0000);
	wr_reg(0x0057, 0x004F);//

#ifdef ORIENTATION_VERTICAL
	wr_reg(0x0016, 0x00C8);
#else
	wr_reg(0x0016, 0x00A8);//A8
#endif
	wr_reg(0x0028, 0x0038); //GON=1; DTE=1; D[1:0]=10
	delay(40);
	wr_reg(0x0028, 0x003C); //GON=1; DTE=1; D[1:0]=11

	delay(10); 
}	
  //LCD_X_Init();
	//LCD_ResetDevice();

#endif  /* WIN32 */
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*   
*/
void LCD_X_Config(void) {
  GUI_DEVICE * pDevice;
  GUI_PORT_API PortAPI = {0}; 
  CONFIG_FLEXCOLOR Config = {0};
  
  #if (NUM_BUFFERS > 1)
    GUI_MULTIBUF_Config(NUM_BUFFERS);
  #endif
  //
  // Set display driver and color conversion for 1st layer
  //
  pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Common display driver configuration
  //
  if (LCD_GetSwapXY()) {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
  } else {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
  }
    //
    // Set controller and operation mode
    //
    PortAPI.pfWrite16_A0  = LCD_X_Write00_16;
    PortAPI.pfWrite16_A1  = LCD_X_Write01_16;
    PortAPI.pfWriteM16_A1 = LCD_X_WriteM01_16;
    PortAPI.pfReadM16_A1  = LCD_X_ReadM01_16;
	//		if(DeviceCode==0x9325||DeviceCode==0x9328)			/*ILI9325	  ¥Û∆¡9320 –°∆¡9325*/
	//{
	#ifdef lcd9325
		GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66708, GUIDRV_FLEXCOLOR_M16C0B16);
	#else
		    GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66715, GUIDRV_FLEXCOLOR_M16C0B16);
	#endif
	//}
    //
    // Orientation and offset of SEG/COM lines
    //
    Config.Orientation   = DISPLAY_ORIENTATION;
    Config.RegEntryMode  = 0;
    GUIDRV_FlexColor_Config(pDevice, &Config);
  #if (USE_TOUCH == 1)
    //
    // Set orientation of touch screen
    //
    GUI_TOUCH_SetOrientation(DISPLAY_ORIENTATION);
    //
    // Calibrate touch screen
    //
    GUI_TOUCH_Calibrate(GUI_COORD_X, 0, WIDTH  - 1, TOUCH_LEFT, TOUCH_RIGHT);
    GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, HEIGHT - 1, TOUCH_TOP,  TOUCH_BOTTOM);
  #endif
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if 
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - OK
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;

  switch (Cmd) {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    _InitController();
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/
