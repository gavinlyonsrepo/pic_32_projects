/*
* Project Name: ER_OLEDM1_CH1115
* File: ER_OLEDM1_CH1115_graphics.h
* Description: ER_OLEDM1 OLED driven by CH1115 controller header file 
* for the custom graphics functions based on Adafruit graphics library
* Author: Gavin Lyons.
* Project URL:  https://github.com/gavinlyonsrepo/pic_32_projects
*/

#ifndef _ER_OLEDM1_CH1115_GRAPHICS_H
#define _ER_OLEDM1_CH1115_GRAPHICS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> // for the abs function, Calculates the absolute value.
#include "ER_OLEDM1_CH1115_font.h"
#include "ER_OLEDM1_CH1115.h"

#define swap(a, b) { int16_t t = a; a = b; b = t; }


typedef enum 
{
    OLEDFont_Default = 1,
    OLEDFont_Thick = 2,
    OLEDFont_Seven_Seg = 3,
    OLEDFont_Wide = 4,
    OLEDFont_Bignum = 5,
}OLEDFONT_e;

typedef enum {
    FONT_W_FIVE = 5, FONT_W_SEVEN = 7, FONT_W_FOUR = 4, FONT_W_EIGHT = 8, FONT_W_16 = 16
}OLEDFONT_width_e ; // width of the font in bytes cols.

typedef enum  {
    FONT_O_EXTEND = 0x00, 
    FONT_O_SP = 0x20, // Starts at Space
    FONT_N_SP = 0x30 // Starts at number 0
}OLEDFONT_offset_e; // font offset in the ASCII table

typedef enum  
{
    FONT_H_8 = 8, FONT_H_32 = 32
}OLEDFONT_height_e; // width of the font in bits

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

void OGdrawBitmapBuffer(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color, 
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

void OGsetFontNum(uint8_t FontNumber);
void OGdrawCharBigNum(uint8_t x, uint8_t y, uint8_t c, uint8_t color , uint8_t bg);
void OGdrawTextBigNum(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg);
	
#endif 
