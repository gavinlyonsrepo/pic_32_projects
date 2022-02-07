/*
* Project Name: ERMCH1115
* File: ERMCH1115.c
* Description: ER_OLEDM1 OLED driven by CH1115 controller source file
* Author: Gavin Lyons.
* Project URL:  https://github.com/gavinlyonsrepo/pic_32_projects
*/

#include "ER_OLEDM1_CH1115.h"
#include "my_utils.h"

bool _sleep = true; // False awake/ON , true sleep/OFF
uint8_t _OLEDcontrast; // Contrast default 0x80 datasheet 00-FF
uint8_t screenBuffer[OLED_WIDTH * (OLED_HEIGHT / 8)]; // 1024 bytes = 128 * 64/8
uint8_t* OLEDBufferPtr = (uint8_t*) &screenBuffer;  // Assign the pointer to the buffer

uint8_t bufferWidth = OLED_WIDTH;
uint8_t bufferHeight = OLED_HEIGHT;

// Desc: begin Method initialise OLED 
// Sets pinmodes and SPI setup
// Param1: OLEDcontrast default = 0x80 , range 0x00 to 0xFE
void OLEDbegin (uint8_t myOLEDcontrast) 
{
  _OLEDcontrast  = myOLEDcontrast ;
		//SPI.begin();
  OLEDinit();
}


// Desc: Called from OLEDbegin carries out Power on sequence and register init
// Can be used to reset OLED to default values.
void OLEDinit()
 {
	
	ERMCH1115_CS_SetLow;
	
	OLEDReset();
	
	sendCommand(ERMCH1115_DISPLAY_OFF, 0); 
	
	sendCommand(ERMCH1115_SET_COLADD_LSB, 0); 
	sendCommand(ERMCH1115_SET_COLADD_MSB, 0); 
	sendCommand(ERMCH1115_SET_PAGEADD, 0); 
	sendCommand(ERMCH115_SET_DISPLAY_START_LINE, 0); 
   
	sendCommand(ERMCH115_CONTRAST_CONTROL  ,0); 
	sendCommand(_OLEDcontrast, 0);  
	
	sendCommand(ERMCH1115_IREF_REG, 0); 
	sendCommand(ERMCH1115_IREF_SET, 0); 
	
	sendCommand(ERMCH1115_SEG_SET_REMAP, 0); 
	sendCommand(ERMCH1115_SEG_SET_PADS, 0); 
	sendCommand(ERMCH1115_ENTIRE_DISPLAY_ON, 0); 
	sendCommand(ERMCH1115_DISPLAY_NORMAL, 0);
	
	sendCommand(ERMCH1115_MULTIPLEX_MODE_SET, 0); 
	sendCommand(ERMCH1115_MULTIPLEX_DATA_SET , 0); 
	
	sendCommand(ERMCH1115_COMMON_SCAN_DIR, 0); 
	
	sendCommand(ERMCH1115_OFFSET_MODE_SET, 0); 
	sendCommand(ERMCH1115_OFFSET_DATA_SET, 0); 
	
	sendCommand(ERMCH1115_OSC_FREQ_MODE_SET, 0); 
	sendCommand(ERMCH1115_OSC_FREQ_DATA_SET, 0); 
	
	sendCommand(ERMCH1115_PRECHARGE_MODE_SET, 0); 
	sendCommand(ERMCH1115_PRECHARGE_DATA_SET, 0); 
	
	sendCommand(ERMCH1115_COM_LEVEL_MODE_SET, 0); 
	sendCommand(ERMCH1115_COM_LEVEL_DATA_SET, 0); 
	
	sendCommand(ERMCH1115_SET_PUMP_REG, ERMCH115_SET_PUMP_SET); 
	
	sendCommand(ERMCH1115_DC_MODE_SET, 0); 
	sendCommand(ERMCH1115_DC_ONOFF_SET, 0);
	
	sendCommand(ERMCH1115_DISPLAY_ON, 0);
	_sleep= false;
	ERMCH1115_CS_SetHigh;  
	
	delay_ms(ERMCH1115_INITDELAY);
}

// Desc: Sends a command to the display
// Param1: the command
// Param2: the values to change
void sendCommand (uint8_t command,uint8_t value) 
{
  ERMCH1115_CD_SetLow; 
  sendData(command | value);
  ERMCH1115_CD_SetHigh;
}

// Desc: Resets OLED in a four wire setup called at start 
void OLEDReset () 
{
	ERMCH1115_RST_SetHigh; 
	delay_ms(ERMCH1115_RST_DELAY1);
	ERMCH1115_RST_SetLow;
	delay_ms(ERMCH1115_RST_DELAY1);
	ERMCH1115_RST_SetHigh ;
	delay_ms(ERMCH1115_RST_DELAY2);
}

// Desc: Turns On Display
// Param1: bits,  1  on , 0 off
void OLEDEnable (uint8_t bits) 
{
 
 ERMCH1115_CS_SetLow;
 if (bits)
 {
	  _sleep= false;
	  sendCommand(ERMCH1115_DISPLAY_ON, 0);
 }else
 {
	 _sleep= true;
	 sendCommand(ERMCH1115_DISPLAY_OFF, 0);
 }
 ERMCH1115_CS_SetHigh;
 
}

// Desc: OLEDIsOff
// Returns: bool  value of _sleep if true OLED is off and in sleep mode, 500uA.
bool OLEDIssleeping() { return  _sleep ;}

// Desc: Sets up Horionztal Scroll
// Param1: TimeInterval 0x00 -> 0x07 , 0x00 = 6 frames
// Param2: Direction 0x26 right 0x27 left (A2 – A0)
// Param3: Mode. Set Scroll Mode: (28H – 2BH)  0x28 = continuous
void OLEDscrollSetup(uint8_t Timeinterval, uint8_t Direction, uint8_t mode) 
{
 
 ERMCH1115_CS_SetLow;

 sendCommand(ERMCH1115_HORIZONTAL_A_SCROLL_SETUP, 0);
 sendCommand(ERMCH1115_HORIZONTAL_A_SCROLL_SET_SCOL, 0);
 sendCommand(ERMCH1115_HORIZONTAL_A_SCROLL_SET_ECOL, 0);

 sendCommand(Direction , 0);
 sendCommand(ERMCH1115_SPAGE_ADR_SET , 0);
 sendCommand(Timeinterval , 0);
 sendCommand(ERMCH1115_EPAGE_ADR_SET , 0);

 sendCommand(mode, 0);
  
 ERMCH1115_CS_SetHigh;
 
}

// Desc: Turns on Horizontal scroll 
// Param1: bits 1  on , 0 off
// Note OLEDscrollSetup must be called before it 
void OLEDscroll(uint8_t bits) 
{
	
	ERMCH1115_CS_SetLow;
	bits ? sendCommand(ERMCH1115_ACTIVATE_SCROLL , 0) :   sendCommand(ERMCH1115_DEACTIVATE_SCROLL, 0);
	ERMCH1115_CS_SetHigh;
	
}

// Desc: Adjusts contrast 
// Param1: Contrast 0x00 to 0xFF , default 0x80
// Note: Setup during init. 
void OLEDContrast(uint8_t contrast)
{
	
	ERMCH1115_CS_SetLow;
	sendCommand(ERMCH115_CONTRAST_CONTROL  ,0); 
	sendCommand(contrast, 0);  
	ERMCH1115_CS_SetHigh;
	
}

// Desc: Rotates the display vertically 
// Param1: bits 1  on , 0 off
void OLEDFlip(uint8_t  bits) 
{
 
 ERMCH1115_CS_SetLow;
  
  bits ? sendCommand(ERMCH1115_COMMON_SCAN_DIR, 0x08):sendCommand(ERMCH1115_COMMON_SCAN_DIR, 0x00)  ; // C0H - C8H 
  bits ? sendCommand(ERMCH1115_SEG_SET_REMAP, 0x01):   sendCommand(ERMCH1115_SEG_SET_REMAP, 0x00); //(A0H - A1H)
 
  ERMCH1115_CS_SetHigh;
  
}

// Desc: Turns on fade effect 
// Param1: bits  
// bits = 0x00 to stop  
// bits values: (see datasheet breatheffect P25 for more details)
// 		ON/OFF * * A4 A3 A2 A1 A0
//      When ON/OFF =”H”, Breathing Light ON.
//	 	Breathing Display Effect Maximum Brightness Adjust Set: (A4 – A3)
//		Breathing Display Effect Time Interval Set: (A2 – A0)
// 		Default on is 0x81
void OLEDfadeEffect(uint8_t bits) 
{
 
 ERMCH1115_CS_SetLow;
 sendCommand(ERMCCH1115_BREATHEFFECT_SET,0);
 sendCommand(bits,0);
 ERMCH1115_CS_SetHigh;
 
}

// Call when powering down
void OLEDPowerDown(void)
{
	OLEDEnable(0);
	ERMCH1115_CD_SetLow ;
	ERMCH1115_RST_SetLow ;
	ERMCH1115_CS_SetLow;
	_sleep= true;
}

// Desc: invert the display
// Param1: bits, 1 invert , 0 normal
void OLEDInvert(uint8_t bits) 
{
 
 ERMCH1115_CS_SetLow;
  bits ? sendCommand(ERMCH1115_DISPLAY_INVERT, 0) :   sendCommand(ERMCH1115_DISPLAY_NORMAL, 0);
 ERMCH1115_CS_SetHigh;
 
}

// Desc: Fill the screen NOT the buffer with a datapattern 
// Param1: datapattern can be set to zero to clear screen (not buffer) range 0x00 to 0ff
// Param2: optional delay in milliseconds can be set to zero normally.
void OLEDFillScreen(uint8_t dataPattern, uint8_t delay) 
{
	for (uint8_t row = 0; row < OLED_PAGE_NUM; row++) 
	{
		OLEDFillPage(row,dataPattern,delay);
	}
}

// Desc: Fill the chosen page(1-8)  with a datapattern 
// Param1: datapattern can be set to 0 to FF (not buffer)
// Param2: optional delay in milliseconds can be set.
void OLEDFillPage(uint8_t page_num, uint8_t dataPattern,uint8_t mydelay) 
{
	
	ERMCH1115_CS_SetLow;
	sendCommand(ERMCH1115_SET_COLADD_LSB, 0); 
	sendCommand(ERMCH1115_SET_COLADD_MSB, 0);
	sendCommand(ERMCH1115_SET_PAGEADD, page_num); 
	ERMCH1115_CS_SetHigh;
	delay_ms(1);
	ERMCH1115_CS_SetLow;
	uint8_t numofbytes = OLED_WIDTH; // 128 bytes
	for (uint8_t i = 0; i < numofbytes; i++) 
	{
	  sendData(dataPattern);
	  delay_ms(mydelay);
	}
	ERMCH1115_CS_SetHigh;
	
}

//Desc: Draw a bitmap in PROGMEM to the screen
//Param1: x offset 0-128
//Param2: y offset 0-64
//Param3: width 0-128
//Param4 height 0-64
//Param5 the bitmap must be in PROGMEM
void OLEDBitmap(int16_t x, int16_t y, uint8_t w, uint8_t h, const uint8_t* data) 
{
 
 ERMCH1115_CS_SetLow;

  uint8_t tx, ty; 
  uint16_t offset = 0; 
  uint8_t column = (x < 0) ? 0 : x;
  uint8_t page = (y < 0) ? 0 : y >>3;

  for (ty = 0; ty < h; ty = ty + 8) 
  {
		if (y + ty < 0 || y + ty >= OLED_HEIGHT) {continue;}
		sendCommand(ERMCH1115_SET_COLADD_LSB, (column & 0x0F)); 
		sendCommand(ERMCH1115_SET_COLADD_MSB, (column & 0xF0) >> 4);
		sendCommand(ERMCH1115_SET_PAGEADD, page++); 

		for (tx = 0; tx < w; tx++) 
		{
			  if (x + tx < 0 || x + tx >= OLED_WIDTH) {continue;}
			  offset = (w * (ty >> 3)) + tx; 
			  sendData(data[offset]);
		}
  }
ERMCH1115_CS_SetHigh;

}



//Desc: Send data byte with SPI to ERMCH1115
//Param1: the data byte
void sendData(uint8_t byte)
{
	//(void)SPI.transfer(byte); 
    SERCOM3_SPI_Write(&byte, 1);
} 


//Desc: updates the buffer i.e. writes it to the screen
void OLEDupdate() 
{
  uint8_t x = 0; uint8_t y = 0; uint8_t w = bufferWidth; uint8_t h = bufferHeight;
  OLEDBuffer( x,  y,  w,  h, (uint8_t*) OLEDBufferPtr);
}

//Desc: clears the buffer i.e. does NOT write to the screen
void OLEDclearBuffer()
{

   memset( OLEDBufferPtr, 0x00, (bufferWidth * (bufferHeight /8))  ); 
   return;
}

//Desc: Draw a bitmap to the screen
//Param1: x offset 0-128
//Param2: y offset 0-64
//Param3: width 0-128
//Param4 height 0-64
//Param5 the bitmap
//Note: Called by OLEDupdate
void OLEDBuffer(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t* data) 
{

 
 ERMCH1115_CS_SetLow;

  uint8_t tx, ty; 
  uint16_t offset = 0; 
  uint8_t column = (x < 0) ? 0 : x;
  uint8_t page = (y < 0) ? 0 : y/8;

  for (ty = 0; ty < h; ty = ty + 8) 
  {
	if (y + ty < 0 || y + ty >= OLED_HEIGHT) {continue;}
	
	sendCommand(ERMCH1115_SET_COLADD_LSB, (column & 0x0F)); 
	sendCommand(ERMCH1115_SET_COLADD_MSB, (column & 0XF0) >> 4); 
	sendCommand(ERMCH1115_SET_PAGEADD, page++); 
 
	for (tx = 0; tx < w; tx++) 
	{
		  if (x + tx < 0 || x + tx >= OLED_WIDTH) {continue;}
		  offset = (w * (ty /8)) + tx; 
		  sendData(data[offset++]);
	}
  }
  
  
ERMCH1115_CS_SetHigh;

}

// Desc: Draws a Pixel to the screen overides the  graphics library
// Passed x and y co-ords and colour of pixel.
void drawPixel(int16_t x, int16_t y, uint8_t colour) 
{

  if ((x < 0) || (x >= bufferWidth) || (y < 0) || (y >= bufferHeight)) {
	return;
  }
	  uint16_t tc = (bufferWidth * (y /8)) + x; 
	  switch (colour)
	  {
		case FOREGROUND:  OLEDBufferPtr[tc] |= (1 << (y & 7)); break;
		case BACKGROUND:  OLEDBufferPtr[tc] &= ~(1 << (y & 7)); break;
		case INVERSE: OLEDBufferPtr[tc] ^= (1 << (y & 7)); break;
	  }
}

// ***************** EOF ***************
