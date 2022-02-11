/*
* Project Name: ERMCH1115
* File: ERMCH1115.h
* Description: ER_OLEDM1 OLED driven by CH1115 controller header file
* Author: Gavin Lyons.
* Project URL:  https://github.com/gavinlyonsrepo/pic_32_projects
*/
  
#ifndef _ER_OLEDM1_CH1115_H_
#define _ER_OLEDM1_CH1115_H_

// Section: Includes
#include <string.h> 
#include "ER_OLEDM1_CH1115_graphics.h"
#include "definitions.h"

// Section: Defines

// Fonts setup no buffer default font
#define NO_BUFFER_FONTPADDING  send_data(0x00)
#define NO_BUFFER_FONTWIDTH 5
#define NO_BUFFER_ASCII_OFFSET 0x00

// Display Pixel colours  definition
#define FOREGROUND  0
#define BACKGROUND 1
#define INVERSE 2

/* CH1115 Command Set*/
// Fundamental Commands
#define ERMCH1115_ENTIRE_DISPLAY_ON 0xA4 //Forcibly turns the entire display on regardless of the contents of the display data RAM
#define ERMCH1115_ENTIRE_DISPLAY_OFF 0xA5 
#define ERMCH1115_DISPLAY_ON 0xAF
#define ERMCH1115_DISPLAY_OFF 0xAE
#define ERMCH1115_DISPLAY_NORMAL 0xA6 
#define ERMCH1115_DISPLAY_INVERT 0xA7
#define ERMCH115_CONTRAST_CONTROL 0x81 //Contrast Control Mode Set
#define ERMCH115_CONTRAST_DATA_DEFAULT 0x80 // Contrast Data Reg Set 0x00 to 0xFF

// Addressing Setting Commands
#define ERMCH1115_SET_PAGEADD 0xB0 // Set Page Address: (B0H - B7H)
#define ERMCH1115_SET_COLADD_LSB 0x00 // Set Lower Column Address: (00H - 0FH)
#define ERMCH1115_SET_COLADD_MSB 0x10 // Set Higher Column Address: (10H – 1FH)
#define ERMCH115_SET_DISPLAY_START_LINE 0x40 // Determine the initial display line

// Hardware Configuration Commands
#define ERMCH1115_SET_PUMP_REG 0x30 // Output voltage (V PP ) internal charger pump.
#define ERMCH115_SET_PUMP_SET   0x01 //  A1:A0[] 01 = 7.4v 
#define ERMCH1115_IREF_REG 0x82 // I REF Resistor Set 
#define ERMCH1115_IREF_SET 0x00 // I REF Resistor adjust 
#define ERMCH1115_SEG_SET_REMAP  0xA0 // Set Segment Re-map: (A0H - A1H)
#define ERMCH1115_SEG_SET_PADS 0xA2 //Set SEG pads hw config: (A2H – A3H)
#define ERMCH1115_MULTIPLEX_MODE_SET 0xA8 //Multiplex Ration Mode Set
#define ERMCH1115_MULTIPLEX_DATA_SET  0x3F //Multiplex Ration Data Set: (00H - 3FH)

#define ERMCH1115_DC_MODE_SET 0xAD // DC-DC Control Mode Set
#define ERMCH1115_DC_ONOFF_SET 0x8B // DC-DC ON/OFF Mode Set (8AH - 8BH) (a=off; b=on)
#define ERMCH1115_COMMON_SCAN_DIR 0xC0 // Set Common Op Scan Dir:C0H - C8H Flip vertical
#define ERMCH1115_OFFSET_MODE_SET 0xD3 //Display Offset Mode Set:
#define ERMCH1115_OFFSET_DATA_SET 0x00 //Display Offset Data Set: (00H~3FH)
#define ERMCCH1115_BREATHEFFECT_SET 0x23 // Set Breathing Display Effect:
#define ERMCCH1115_BREATHEFFECT_DATA 0x81 // Display Effect ON/OFF and Time Interval:

// Timing & Driving Scheme Setting Commands
#define ERMCH1115_OSC_FREQ_MODE_SET 0xD5 //Divide Ratio/Oscillator Frequency Mode Set: (D5H)
#define ERMCH1115_OSC_FREQ_DATA_SET 0xA0  
#define ERMCH1115_PRECHARGE_MODE_SET 0xD9 //Pre-charge Period Mode Set:
#define ERMCH1115_PRECHARGE_DATA_SET 0x22 //Discharge/Pre-charge Period Data Set: (00H - FFH)
#define ERMCH1115_COM_LEVEL_MODE_SET 0xDB //COM Deselect Level Mode Set: (DBH)
#define ERMCH1115_COM_LEVEL_DATA_SET 0x40 //VCOM Deselect Level Data Set: (00H - FFH)

// HORIZONTAL Scrolling Commands
#define ERMCH1115_HORIZONTAL_A_SCROLL_SETUP 0x24 //  Additional Horizontal Scroll Setup Mode Set: (24H)
#define ERMCH1115_HORIZONTAL_A_SCROLL_SET_SCOL 0x00  // Start Column Position Set: (A7 – A0)
#define ERMCH1115_HORIZONTAL_A_SCROLL_SET_ECOL 0x7F // End Column Position Set: (B7 – B0)
#define ERMCH1115_SCROLL_SETUP  0x26 //Horizontal Scroll Setup: 26 right 27 left (A2 – A0)
#define ERMCH1115_SPAGE_ADR_SET 0x00  // Start Page Address Set 0x00 = page 0
#define ERMCH1115_TIME_SET 0x00 //Time Interval Set: (B2 – B0) 0x00 = 6 frames
#define ERMCH1115_EPAGE_ADR_SET  0x07 //End Page Address Set: (C2 – C0) 
#define ERMCH1115_SET_SCROLL_MODE 0x28 // Set Scroll Mode: (28H – 2BH) 0x28 = continuous
#define ERMCH1115_DEACTIVATE_SCROLL  0x2E
#define ERMCH1115_ACTIVATE_SCROLL   0x2F

// GPIO
#define ERMCH1115_CS_SetHigh CS_Set()
#define ERMCH1115_CS_SetLow CS_Clear()
#define ERMCH1115_CD_SetHigh DC_Set()
#define ERMCH1115_CD_SetLow DC_Clear()
#define ERMCH1115_RST_SetHigh RESET_Set()
#define ERMCH1115_RST_SetLow RESET_Clear() 

// Delays
#define ERMCH1115_INITDELAY 100 // mS
#define ERMCH1115_RST_DELAY1 10 // mS
#define ERMCH1115_RST_DELAY2 100 // mS

// Display  Size
#define OLED_WIDTH  128
#define OLED_HEIGHT  64
#define OLED_PAGE_NUM  (OLED_HEIGHT/8)

// External user functions
void OLEDupdate(void);
void OLEDclearBuffer(void);
void OLEDBuffer(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t* data);

void OLEDbegin(uint8_t OLEDcontrast );
void OLEDinit(void);
void OLEDReset(void);

void OLEDFillScreen(uint8_t pixel, uint8_t mircodelay);
void OLEDFillPage(uint8_t page_num, uint8_t pixels,uint8_t delay);
void OLEDBitmap(int16_t x, int16_t y, uint8_t w, uint8_t h, const uint8_t* data);

void OLEDEnable(uint8_t on);
void OLEDInvert(uint8_t on);
void OLEDFlip(uint8_t on);
void OLEDContrast(uint8_t contrast);
void OLEDscroll(uint8_t bits) ;
void OLEDscrollSetup(uint8_t Timeinterval, uint8_t Direction, uint8_t mode) ;
void OLEDfadeEffect(uint8_t bits );
bool OLEDIssleeping(void);
void OLEDPowerDown(void);

// Internal not needed by user
void drawPixel(int16_t x, int16_t y, uint8_t colour);
void sendData(uint8_t data);
void sendCommand(uint8_t command, uint8_t value);

#endif // end of guard header

