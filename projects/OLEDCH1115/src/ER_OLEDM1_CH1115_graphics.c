
/*
 * Project Name: ER_OLEDM1_CH1115
 * File:ER_OLEDM1_CH1115_graphics.c
 * Description: ER_OLEDM1 OLED driven by CH1115 controller source file for the graphics functions.
 * Project URL:  https://github.com/gavinlyonsrepo/pic_32_projects
 */

#include "ER_OLEDM1_CH1115_graphics.h"


// Section: Variables 

// Screen related
const int16_t WIDTH = OLED_WIDTH ;
const int16_t HEIGHT = OLED_HEIGHT; 
int16_t _width;
int16_t _height;
int16_t cursor_x;
int16_t cursor_y;
uint8_t textcolor;
uint8_t textbgcolor;
uint8_t textsize;
uint8_t rotation;
bool wrap; // If set, 'wrap' text at right edge of display

// default font settings 
uint8_t _FontNumber = 1;
uint8_t _CurrentFontWidth = 5;
uint8_t _CurrentFontoffset = 0;
uint8_t _CurrentFontheight = 8;


// Section:  Function Space

// Init OLED graphics 
void OGInit() {
    _width = WIDTH;
    _height = HEIGHT;
    rotation = 0;
    cursor_y = cursor_x = 0;
    textsize = 1;
    textcolor = 0x00;
    textbgcolor = 0xFF;
    wrap = true;
}

// Draw a circle outline
void OGdrawCircle(int16_t x0, int16_t y0, int16_t r,
        uint8_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    drawPixel(x0, y0 + r, color);
    drawPixel(x0, y0 - r, color);
    drawPixel(x0 + r, y0, color);
    drawPixel(x0 - r, y0, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        drawPixel(x0 + x, y0 + y, color);
        drawPixel(x0 - x, y0 + y, color);
        drawPixel(x0 + x, y0 - y, color);
        drawPixel(x0 - x, y0 - y, color);
        drawPixel(x0 + y, y0 + x, color);
        drawPixel(x0 - y, y0 + x, color);
        drawPixel(x0 + y, y0 - x, color);
        drawPixel(x0 - y, y0 - x, color);
    }
}

void OGdrawCircleHelper(int16_t x0, int16_t y0,
        int16_t r, uint8_t cornername, uint8_t color) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        if (cornername & 0x4) {
            drawPixel(x0 + x, y0 + y, color);
            drawPixel(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
            drawPixel(x0 + x, y0 - y, color);
            drawPixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            drawPixel(x0 - y, y0 + x, color);
            drawPixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            drawPixel(x0 - y, y0 - x, color);
            drawPixel(x0 - x, y0 - y, color);
        }
    }
}

void OGfillCircle(int16_t x0, int16_t y0, int16_t r,
        uint8_t color) {
    OGdrawFastVLine(x0, y0 - r, 2 * r + 1, color);
    OGfillCircleHelper(x0, y0, r, 3, 0, color);
}

// Used to do circles and roundrects

void OGfillCircleHelper(int16_t x0, int16_t y0, int16_t r,
        uint8_t cornername, int16_t delta, uint8_t color) {

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x1) {
            OGdrawFastVLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
            OGdrawFastVLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
        }
        if (cornername & 0x2) {
            OGdrawFastVLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
            OGdrawFastVLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
        }
    }
}
 
void OGdrawLine(int16_t x0, int16_t y0,
        int16_t x1, int16_t y1,
        uint8_t color) {
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0 <= x1; x0++) {
        if (steep) {
            drawPixel(y0, x0, color);
        } else {
            drawPixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

// Draw a rectangle

void OGdrawRect(int16_t x, int16_t y,
        int16_t w, int16_t h,
        uint8_t color) {
    OGdrawFastHLine(x, y, w, color);
    OGdrawFastHLine(x, y + h - 1, w, color);
    OGdrawFastVLine(x, y, h, color);
    OGdrawFastVLine(x + w - 1, y, h, color);
}

void OGdrawFastVLine(int16_t x, int16_t y,
        int16_t h, uint8_t color) {

    OGdrawLine(x, y, x, y + h - 1, color);
}

void OGdrawFastHLine(int16_t x, int16_t y,
        int16_t w, uint8_t color) {
    
    OGdrawLine(x, y, x + w - 1, y, color);
}

void OGfillRect(int16_t x, int16_t y, int16_t w, int16_t h,
        uint8_t color) {
    for (int16_t i = x; i < x + w; i++) {
        OGdrawFastVLine(i, y, h, color);
    }
}

void OGfillScreen(uint8_t color) {
    OGfillRect(0, 0, _width, _height, color);
}

// Draw a rounded rectangle

void OGdrawRoundRect(int16_t x, int16_t y, int16_t w,
        int16_t h, int16_t r, uint8_t color) {
    OGdrawFastHLine(x + r, y, w - 2 * r, color); // Top
    OGdrawFastHLine(x + r, y + h - 1, w - 2 * r, color); // Bottom
    OGdrawFastVLine(x, y + r, h - 2 * r, color); // Left
    OGdrawFastVLine(x + w - 1, y + r, h - 2 * r, color); // Right
    // draw four corners
    OGdrawCircleHelper(x + r, y + r, r, 1, color);
    OGdrawCircleHelper(x + w - r - 1, y + r, r, 2, color);
    OGdrawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
    OGdrawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

// Fill a rounded rectangle

void OGfillRoundRect(int16_t x, int16_t y, int16_t w,
        int16_t h, int16_t r, uint8_t color) {
    OGfillRect(x + r, y, w - 2 * r, h, color);

    // draw four corners
    OGfillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
    OGfillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}

// Draw a triangle

void OGdrawTriangle(int16_t x0, int16_t y0,
        int16_t x1, int16_t y1,
        int16_t x2, int16_t y2, uint8_t color) {
    OGdrawLine(x0, y0, x1, y1, color);
    OGdrawLine(x1, y1, x2, y2, color);
    OGdrawLine(x2, y2, x0, y0, color);
}

// Fill a triangle

void OGfillTriangle(int16_t x0, int16_t y0,
        int16_t x1, int16_t y1,
        int16_t x2, int16_t y2, uint8_t color) {

    int16_t a, b, y, last;

    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }
    if (y1 > y2) {
        swap(y2, y1);
        swap(x2, x1);
    }
    if (y0 > y1) {
        swap(y0, y1);
        swap(x0, x1);
    }

    if (y0 == y2) {
        a = b = x0;
        if (x1 < a) a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a) a = x2;
        else if (x2 > b) b = x2;
        OGdrawFastHLine(a, y0, b - a + 1, color);
        return;
    }

    int16_t
    dx01 = x1 - x0,
            dy01 = y1 - y0,
            dx02 = x2 - x0,
            dy02 = y2 - y0,
            dx12 = x2 - x1,
            dy12 = y2 - y1;
    int32_t
    sa = 0,
            sb = 0;

    if (y1 == y2) last = y1;
    else last = y1 - 1;

    for (y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;

        if (a > b) swap(a, b);
        OGdrawFastHLine(a, y, b - a + 1, color);
    }

    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;

        if (a > b) swap(a, b);
        OGdrawFastHLine(a, y, b - a + 1, color);
    }
}

// Desc:  Draw a 1-bit color bitmap at the specified x, y position from the
// provided bitmap buffer using color as the
// foreground color and bg as the background color.
// Param 1,2  X,Y screen co-ord
// Param 3,4 0-127 possible values width and height of bitmap in pixels 
// Param 4,5 bitmap colors ,bitmap is bi-color
// Param 6: an array of unsigned chars containing bitmap
// NOTES :: data horizontally  addressed.
void OGdrawBitmapBufferHa(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color, uint8_t bgcolor, const unsigned char bitmap[]) {
    int16_t byteWidth = (w + 7) / 8;
    uint8_t byte = 0;
    for (int16_t j = 0; j < h; j++, y++) {
        for (int16_t i = 0; i < w; i++) {
            if (i & 7)
                byte <<= 1;
            else
                byte = bitmap[j * byteWidth + i / 8];
            drawPixel(x + i, y, (byte & 0x80) ? color : bgcolor);
        }
    }
}

// Desc:  Draw a 1-bit color bitmap at the specified x, y position from the
// provided bitmap buffer using color as the
// foreground color and bg as the background color.
// Param 1,2  X,Y screen co-ord
// Param 3,4 0-127 possible values width and height of bitmap in pixels 
// Param 4,5 bitmap colors ,bitmap is bi-color
// Param 6: an array of unsigned chars containing bitmap 
// NOTES :: data vertically addressed.
void OGdrawBitmapBufferVa(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color, uint8_t bgcolor, const unsigned char bitmap[]) {
	uint8_t vline;
	int16_t i, j, r = 0, yin = y;
	
	for (i=0; i<(w+1); i++ ) {
		if (r == (h+7)/8 * w) break;
		vline = bitmap [ r] ;
		r++;
		if (i == w) {
			y = y+8;
			i = 0;
		}
		
		for (j=0; j<8; j++ ) {
			if (y+j-yin == h) break;
			if (vline & 0x1) {
				drawPixel(x+i, y+j, color);
			}
			else {
				drawPixel(x+i, y+j, bgcolor);
			}	
			vline >>= 1;
		}
	}
}

// Draw a character for Font 1-6,

void OGdrawChar(int16_t x, int16_t y, unsigned char c,
        uint8_t color, uint8_t bg, uint8_t size) {

    if ((x >= _width) || // Clip right
            (y >= _height) || // Clip bottom
            ((x + (_CurrentFontWidth + 1) * size - 1) < 0) || // Clip left
            ((y + _CurrentFontheight * size - 1) < 0)) // Clip top
        return;

    for (int8_t i = 0; i < (_CurrentFontWidth + 1); i++) {
        uint8_t line;
        if (i == _CurrentFontWidth) {
            line = 0x0;
        } else {
            switch (_FontNumber) {
                case OLEDFontType_Default : line = pFontDefaultptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
                case OLEDFontType_Thick : line = pFontThickptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
                case OLEDFontType_SevenSeg: line = pFontSevenSegptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
                case OLEDFontType_Wide : line = pFontWideptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
                case OLEDFontType_Tiny : line = pFontTinyptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
                case OLEDFontType_Homespun : line = pFontHomeSpunptr[((c - _CurrentFontoffset) * _CurrentFontWidth) + i]; break;
                default: // wrong font number
                    return;
                break;
            }
        }
        for (int8_t j = 0; j < _CurrentFontheight; j++) {
            if (line & 0x1) {
                if (size == 1) // default size
                    drawPixel(x + i, y + j, color);
                else { // big size
                    OGfillRect(x + (i * size), y + (j * size), size, size, color);
                }
            } else if (bg != color) {
                if (size == 1) // default size
                    drawPixel(x + i, y + j, bg);
                else { // big size
                   OGfillRect(x + i*size, y + j*size, size, size, bg);
                }
            }
            line >>= 1;
        }
    }
}

void OGsetCursor(int16_t x, int16_t y) {
    cursor_x = x;
    cursor_y = y;
}

void OGsetTextSize(uint8_t s) {
    textsize = (s > 0) ? s : 1;
}

void OGsetTextColor(uint8_t c, uint8_t b) {
    textcolor = c;
    textbgcolor = b;
}

void OGsetTextWrap(bool w) {
    wrap = w;
}

uint8_t OGgetRotation(void) {
    return rotation;
}

void OGsetRotation(uint8_t x) {
    rotation = (x & 3);
    switch (rotation) {
        case 0:
        case 2:
            _width = WIDTH;
            _height = HEIGHT;
            break;
        case 1:
        case 3:
            _width = HEIGHT;
            _height = WIDTH;
            break;
    }
}

// Return the size of the display (per current rotation)

int16_t OGwidth(void) {
    return _width;
}

int16_t OGheight(void) {
    return _height;
}

// Desc :  Set the font number
// Param1: fontnumber 1-8  OLEDFontType_e
// 1=default 2=thick 3=seven segment 4=wide 5=tiny 6=homespun
// 7= bignum 8=mednum

void OGsetFontNum(OLEDFontType_e FontNumber) {
    _FontNumber = FontNumber;

    switch (_FontNumber) {
	case OLEDFontType_Default:  // Norm default 5 by 8
		_CurrentFontWidth = OLEDFontWidth_5;
		_CurrentFontoffset =  OLEDFontOffset_Extend;
		_CurrentFontheight = OLEDFontHeight_8;
	break; 
	case OLEDFontType_Thick: // Thick 7 by 8 (NO LOWERCASE LETTERS)
		_CurrentFontWidth = OLEDFontWidth_7;
		_CurrentFontoffset = OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break; 
	case OLEDFontType_SevenSeg:  // Seven segment 4 by 8
		_CurrentFontWidth = OLEDFontWidth_4;
		_CurrentFontoffset = OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break;
	case OLEDFontType_Wide : // Wide  8 by 8 (NO LOWERCASE LETTERS)
		_CurrentFontWidth = OLEDFontWidth_8;
		_CurrentFontoffset = OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break; 
	case OLEDFontType_Tiny:  // tiny 3 by 8
		_CurrentFontWidth = OLEDFontWidth_3;
		_CurrentFontoffset =  OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break;
	case OLEDFontType_Homespun: // homespun 7 by 8 
		_CurrentFontWidth = OLEDFontWidth_7;
		_CurrentFontoffset = OLEDFontOffset_Space;
		_CurrentFontheight = OLEDFontHeight_8;
	break;
	case OLEDFontType_Bignum : // big nums 16 by 32 (NUMBERS + : only)
		_CurrentFontWidth = OLEDFontWidth_16;
		_CurrentFontoffset = OLEDFontOffset_Number;
		_CurrentFontheight = OLEDFontHeight_32;
	break; 
	case OLEDFontType_Mednum: // med nums 16 by 16 (NUMBERS + : only)
		_CurrentFontWidth = OLEDFontWidth_16;
		_CurrentFontoffset =  OLEDFontOffset_Number;
		_CurrentFontheight = OLEDFontHeight_16;
	break;
	default: // if wrong font num passed in,  set to default
		_CurrentFontWidth = OLEDFontWidth_5;
		_CurrentFontoffset =  OLEDFontOffset_Extend;
		_CurrentFontheight = OLEDFontHeight_8;
		_FontNumber = OLEDFontType_Default;
	break;
    }
}

// Desc: writes a char (c) on the OLED
// Param 1 , 2 : coordinates (x, y).
// Param 3: The ASCII character
// Param 4: foreground color 
// Param 5: background color
// Notes for font 7-8 only

void OGdrawCharNum(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t bg) {
    if (_FontNumber < OLEDFontType_Bignum) {
        return;
    }
    uint8_t i, j;
    uint8_t ctemp = 0, y0 = y;

    for (i = 0; i < (_CurrentFontheight*2); i++) {
        if (_FontNumber == OLEDFontType_Bignum){
			ctemp = pFontBigNumptr[c - _CurrentFontoffset][i];
		}
		else if (_FontNumber == OLEDFontType_Mednum){
			ctemp = pFontMedNumptr[c - _CurrentFontoffset][i];

		}

        for (j = 0; j < 8; j++) {
            if (ctemp & 0x80) {
                drawPixel(x, y, color);
            } else {
                drawPixel(x, y, bg);
            }

            ctemp <<= 1;
            y++;
            if ((y - y0) == _CurrentFontheight) {
                y = y0;
                x++;
                break;
            }
        }
    }
}

// Desc: Writes text string (*ptext) on the Oled 
// Param 1 , 2 : coordinates (x, y).
// Param 3: pointer to string 
// Param 4: color 
// Param 5: background color
// Notes for font 7-8 only  

void OGdrawTextNum(uint8_t x, uint8_t y, char *pText, uint8_t color, uint8_t bg) {	
    if (_FontNumber < OLEDFontType_Bignum) {
        return;
    }

    while (*pText != '\0') {
        if (x > (_width - _CurrentFontWidth)) {
            x = 0;
            y += _CurrentFontheight;
            if (y > (_height - _CurrentFontheight)) {
                y = x = 0;
            }
        }

        OGdrawCharNum(x, y, *pText, color, bg);
        x += _CurrentFontWidth;
        pText++;
    }
}

// Desc: Draw a char array to screen
// Param 1 , 2 : coordinates (x, y).
// Param 3: pointer to string 
// Param 4: color 
// Param 5: background color
// Param 6: size 1 to X
// Notes for font 1-6 only  
void OGdrawText(uint8_t x, uint8_t y, char *pText, uint16_t color, uint16_t bg, uint8_t size) 
{
     if (_FontNumber >= OLEDFontType_Bignum){return;}
    
    uint8_t cursor_x, cursor_y;
    cursor_x = x, cursor_y = y;
      while (*pText != '\0') 
      {
        if (wrap && ((cursor_x + size * _CurrentFontWidth) > _width)) 
        {
            cursor_x = 0;
            cursor_y = cursor_y + size * 7 + 3;
            if (cursor_y > _height) cursor_y = _height;
        }
        OGdrawChar(cursor_x, cursor_y, *pText, color, bg, size);
        cursor_x = cursor_x + size * (_CurrentFontWidth + 1);
        if (cursor_x > _width) cursor_x = _width;
        pText++;
      }
}

// Desc: vsprintf wrapper to print numerical data
// Parameters: https://www.tutorialspoint.com/c_standard_library/c_function_vsprintf.htm 
// The C library function int vsprintf(char *str, const char *format, va_list arg) 
// sends formatted output to a string using an argument list passed to it.
// Returns: If successful, the total number of characters written is returned, 
// otherwise a negative number is returned.
// Note: requires stdio.h and stdarg.h libraries

int OGPrintf(const char *fmt, ...) {
    int length;
    char buffer[20];
    char *pText = buffer;
    
    va_list ap;
    va_start(ap, fmt);
    length = vsprintf(buffer, fmt, ap);
    va_end(ap);
    
    if (length > 0) 
    {
        while (*pText != '\0')
        {
            OGwrite(*pText);
            pText++;
        }
    }
    return length;
}

// Desc :: Prints a single character to screen called by OGPrintf.
size_t OGwrite(uint8_t character) 
{
	if (_FontNumber < OLEDFontType_Bignum)
	{
		if (character == '\n') {
		cursor_y += textsize*_CurrentFontheight;
		cursor_x  = 0;
		} else if (character == '\r') {
		// skip 
		} else {
		OGdrawChar(cursor_x, cursor_y, character, textcolor, textbgcolor, textsize);
		cursor_x += textsize*(_CurrentFontWidth+1);
			if (wrap && (cursor_x > (_width - textsize*(_CurrentFontWidth+1)))) {
			  cursor_y += textsize*_CurrentFontheight;
			  cursor_x = 0;
			}
		}
	}else if (_FontNumber == OLEDFontType_Bignum || _FontNumber == OLEDFontType_Mednum)
	{
		uint8_t decPointRadius = 3;
        uint8_t SkipSpace = 0;
		if (_FontNumber == OLEDFontType_Mednum) decPointRadius = 2;
		
        switch (character)
        {
            case '\n': 
                cursor_y += _CurrentFontheight;
                cursor_x  = 0;
            break;
            case '\r': break;
            case '.':  // draw a circle for decimal & point skip a space.
                OGfillCircle(cursor_x+(_CurrentFontWidth/2), cursor_y + (_CurrentFontheight-6), decPointRadius, textcolor);
                SkipSpace = 1;
             break;
            case '-':  // draw a rect for negative number line and skip a space
                OGfillRect(cursor_x+2, cursor_y + (_CurrentFontheight/2)-2 ,_CurrentFontWidth-4 , decPointRadius+1,  textcolor);              
                SkipSpace = 1;
            break;
            default:
                OGdrawCharNum(cursor_x, cursor_y, character, textcolor, textbgcolor);
                SkipSpace = 1;
            break;
        }
        if (SkipSpace == 1)
        {
            cursor_x += (_CurrentFontWidth+1);
			if (wrap && (cursor_x  > (_width - (_CurrentFontWidth+1)))) 
			{
				cursor_y += _CurrentFontheight;
				cursor_x = 0;
			}
        }
	}
  return 1;
}
//***************** EOF *****************