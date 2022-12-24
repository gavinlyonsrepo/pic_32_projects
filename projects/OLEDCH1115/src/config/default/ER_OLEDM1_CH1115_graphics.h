/*
* Project Name: ER_OLEDM1_CH1115
* File: ER_OLEDM1_CH1115_graphics.h
* Description: ER_OLEDM1 OLED driven by CH1115 controller header file 
* for the  graphics functions.
* Project URL:  https://github.com/gavinlyonsrepo/pic_32_projects
*/

#ifndef _ER_OLEDM1_CH1115_GRAPHICS_H
#define _ER_OLEDM1_CH1115_GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> // for the abs function, Calculates the absolute value.
#include <stdio.h>  // vsprintf
#include <stdarg.h> // varg
#include "ER_OLEDM1_CH1115_font.h"
#include "ER_OLEDM1_CH1115.h"

#define swap(a, b) { int16_t t = a; a = b; b = t; }

// ==== Enums ====

typedef enum 
{
	OLEDFontType_Default = 1,
	OLEDFontType_Thick = 2, // NO LOWERCASE
	OLEDFontType_SevenSeg = 3,
	OLEDFontType_Wide = 4, // NO LOWERCASE
	OLEDFontType_Tiny = 5,
	OLEDFontType_Homespun = 6,
	OLEDFontType_Bignum = 7, // NUMBERS + : . ,one size
	OLEDFontType_Mednum = 8   // NUMBERS + : . ,one size
}OLEDFontType_e;

typedef enum 
{
	OLEDFontWidth_3 = 3,
	OLEDFontWidth_5 = 5, 
	OLEDFontWidth_7 = 7, 
	OLEDFontWidth_4 = 4, 
	OLEDFontWidth_8 = 8,
	OLEDFontWidth_16 = 16
}OLEDFontWidth_e; // width of the font in bytes cols.

typedef enum 
{
	OLEDFontOffset_Extend = 0x00, //   extends ASCII
	OLEDFontOffset_Space = 0x20,  // Starts at Space
	OLEDFontOffset_Number = 0x30,  // Starts at number '0'
}OLEDFontOffset_e; // font offset in the ASCII table

typedef enum 
{
	OLEDFontHeight_8 = 8, 
	OLEDFontHeight_16 = 16, 
	OLEDFontHeight_32 = 32
}OLEDFontHeight_e; // height of the font in bits

// === Function headers ===

void OGInit(); 

void OGdrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
void OGdrawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
void OGdrawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
void OGdrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void OGfillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
void OGfillScreen(uint8_t color);

void OGdrawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
void OGdrawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
    uint8_t color);
void OGfillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
void OGfillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
    int16_t delta, uint8_t color);
void OGdrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t x2, int16_t y2, uint8_t color);
void OGfillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
    int16_t x2, int16_t y2, uint8_t color);
void OGdrawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
    int16_t radius, uint8_t color);
void OGfillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
    int16_t radius, uint8_t color);

void OGdrawBitmapBufferHa(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color, 
        uint8_t bgcolor, const unsigned char bitmap[]);
void OGdrawBitmapBufferVa(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color, 
        uint8_t bgcolor, const unsigned char bitmap[]);

void OGdrawChar(int16_t x, int16_t y, unsigned char c, uint8_t color,
    uint8_t bg, uint8_t size);
void OGdrawText(uint8_t x, uint8_t y, char *_text, uint16_t color, 
        uint16_t bg, uint8_t size);

void OGsetCursor(int16_t x, int16_t y);
void OGsetTextColor(uint8_t c, uint8_t bg);
void OGsetTextSize(uint8_t s);
void OGsetTextWrap(bool w);
void OGsetRotation(uint8_t r);
uint8_t OGgetRotation(void);

int16_t OGheight(void);
int16_t OGwidth(void);

void OGsetFontNum(OLEDFontType_e FontNumber);
void OGdrawCharNum(uint8_t x, uint8_t y, uint8_t c, uint8_t color , uint8_t bg);
void OGdrawTextNum(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg);
int  OGPrintf(const char *fmt, ...);
size_t OGwrite(uint8_t);
#endif 
