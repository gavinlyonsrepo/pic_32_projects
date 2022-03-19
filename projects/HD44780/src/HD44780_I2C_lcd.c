/*
 * File: HD44780_I2C_lcd.c
 * Description: 
 * HD44780-based character LCD 16x02 I2C(PCF8574) library source file
 * Author: Gavin Lyons.
 * Complier: xc32 v4.00 compiler
 * PIC: PIC32CM1216CM00032
 * IDE:  MPLAB X v6.00 , Harmony V3
 * Created : Feb 2022
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_32_projects
 */

// Section : Includes
#include "HD44780_I2C_lcd.h"


// Section : Variables
uint8_t LCDBACKLIGHT = LCD_BACKLIGHTON_MASK;
//I2C  address for I2C module PCF8574 backpack on LCD
uint8_t _LCDSlaveAddresI2C = 0x27 ;
uint8_t _NumRowsLCD = 2;
uint8_t _NumColsLCD = 16;    

// Section : Functions

//  Func Desc: Send data byte to  lcd
//  Param1: data byte
void PCF8574_LCDSendData(unsigned char data) {
    unsigned char data_l, data_u;
    uint8_t data_I2C[4];

    data_l = (data << 4)&0xf0; //select lower nibble by moving it to the upper nibble position
    data_u = data & 0xf0; //select upper nibble
    data_I2C[0] = data_u | (LCD_DATA_BYTE_ON & LCDBACKLIGHT); //enable=1 and rs =1 1101  YYYY-X-en-X-rs
    data_I2C[1] = data_u | (LCD_DATA_BYTE_OFF & LCDBACKLIGHT); //enable=0 and rs =1 1001 YYYY-X-en-X-rs
    data_I2C[2] = data_l | (LCD_DATA_BYTE_ON & LCDBACKLIGHT); //enable=1 and rs =1 1101  YYYY-X-en-X-rs
    data_I2C[3] = data_l | (LCD_DATA_BYTE_OFF &  LCDBACKLIGHT); //enable=0 and rs =1 1001 YYYY-X-en-X-rs

    SERCOM0_I2C_Write(_LCDSlaveAddresI2C, data_I2C, 4);
    while (SERCOM0_I2C_IsBusy() == true);
}

//  Func Desc: Send command byte to  lcd
//  Param1: command byte

void PCF8574_LCDSendCmd(unsigned char cmd) {
    unsigned char cmd_l, cmd_u;
    uint8_t cmd_I2C[4];

    cmd_l = (cmd << 4)&0xf0; //select lower nibble by moving it to the upper nibble position
    cmd_u = cmd & 0xf0; //select upper nibble
    cmd_I2C[0] = cmd_u | (LCD_CMD_BYTE_ON & LCDBACKLIGHT); // YYYY-1100 YYYY-led-en-rw-rs ,enable=1 and rs =0
    cmd_I2C[1] = cmd_u | (LCD_CMD_BYTE_OFF & LCDBACKLIGHT); // YYYY-1000 YYYY-led-en-rw-rs ,enable=0 and rs =0
    cmd_I2C[2] = cmd_l | (LCD_CMD_BYTE_ON & LCDBACKLIGHT); // YYYY-1100 YYYY-led-en-rw-rs ,enable=1 and rs =0
    cmd_I2C[3] = cmd_l | (LCD_CMD_BYTE_OFF & LCDBACKLIGHT); // YYYY-1000 YYYY-led-en-rw-rs ,enable=0 and rs =0

    SERCOM0_I2C_Write(_LCDSlaveAddresI2C, cmd_I2C, 4);
    while (SERCOM0_I2C_IsBusy() == true);
}

// Func Desc: Clear a line by writing spaces to every position
// Param1: uint8_t lineNo, row number 1-2

void PCF8574_LCDClearLine(uint8_t lineNo) {
	if (lineNo == 1) {
		PCF8574_LCDSendCmd(LCD_LINE_ADR1);
	} else if (lineNo == 2) {
		PCF8574_LCDSendCmd(LCD_LINE_ADR2);
	} else if (lineNo == 3) {
		PCF8574_LCDSendCmd(LCD_LINE_ADR3);
	}else if (lineNo == 4) {
		PCF8574_LCDSendCmd(LCD_LINE_ADR4);
	}else{
		return;
	}

	for (uint8_t i = 0; i < _NumColsLCD; i++) {
		PCF8574_LCDSendData(' ');
	}
}

// Func Desc: Clear screen by writing spaces to every position

void PCF8574_LCDClearScreen(void) {
	if (_NumRowsLCD >= 1)
		PCF8574_LCDClearLine(1);
	if (_NumRowsLCD >= 2)
		PCF8574_LCDClearLine(2);
	if (_NumRowsLCD >= 3)
		PCF8574_LCDClearLine(3);
	if (_NumRowsLCD == 4)
		PCF8574_LCDClearLine(4);
}


// Func Desc: Reset screen 
// Param1: enum LCD_CURSOR_TYPE_e cursor type, 4 choices

void PCF8574_LCDResetScreen(LCDCursorType_e CursorType) {
    PCF8574_LCDSendCmd(LCD_MODE_4BIT);
    PCF8574_LCDSendCmd(LCD_DISPLAY_ON);
    PCF8574_LCDSendCmd(CursorType);
    PCF8574_LCDSendCmd(LCD_CLRSCR);
    PCF8574_LCDSendCmd(LCD_INC_MODE);
}


// Func Desc: Turn Screen on and off 
// Param1: passed bool, True = display on , false = display off

void PCF8574_LCDDisplayON(bool OnOff) {
    OnOff ? PCF8574_LCDSendCmd(LCD_DISPLAY_ON) : PCF8574_LCDSendCmd(LCD_DISPLAY_OFF);

}


// Func Desc: Initialise LCD
// Param1: enum LCD_CURSOR_TYPE_e cursor type, 4 choices. 

void PCF8574_LCDInit(LCDCursorType_e CursorType, uint8_t NumRow, uint8_t NumCol, uint8_t I2Caddress) {

    delay_ms(15);
    PCF8574_LCDSendCmd(LCD_HOME);
    delay_ms(5);
    PCF8574_LCDSendCmd(LCD_HOME);
    delay_ms(5);
    PCF8574_LCDSendCmd(LCD_HOME);
    delay_ms(5);
    PCF8574_LCDSendCmd(LCD_MODE_4BIT);
    PCF8574_LCDSendCmd(LCD_DISPLAY_ON);
    PCF8574_LCDSendCmd(CursorType);
    PCF8574_LCDSendCmd(LCD_INC_MODE);
    PCF8574_LCDSendCmd(LCD_CLRSCR);
    
    _NumRowsLCD = NumRow;
    _NumColsLCD = NumCol;
    _LCDSlaveAddresI2C  = I2Caddress;
   
}

// Func Desc: Send string to LCD
// Param1: Pointer to the char array

void PCF8574_LCDSendString(char *str) {
    while (*str) PCF8574_LCDSendData(*str++);
}


// Func Desc: Sends a character to screen , simply wraps SendData command.
// Param1: Character to display
void PCF8574_LCDSendChar(char data) {
    PCF8574_LCDSendData(data);
}

// Func Desc: Moves cursor 
// Param1. enum LCD_DIRECTION_TYPE_e left or right 
// Param2. uint8_t number of spaces to move

void PCF8574_LCDMoveCursor(LCDDirectionType_e direction, uint8_t moveSize) {
    uint8_t i = 0;
    if (direction == LCDMoveRight) {
        for (i = 0; i < moveSize; i++) {
            PCF8574_LCDSendCmd(LCD_MOV_CURSOR_RIGHT);
        }
    } else {
        for (i = 0; i < moveSize; i++) {
            PCF8574_LCDSendCmd(LCD_MOV_CURSOR_LEFT);
        }
    }

}

// Func Desc: Scrolls screen 
// Param1. enum LCD_DIRECTION_TYPE_e , left or right 
// Param2. uint8_t number of spaces to scroll

void PCF8574_LCDScroll(LCDDirectionType_e direction, uint8_t ScrollSize) {
    uint8_t i = 0;
    if (direction == LCDMoveRight) {
        for (i = 0; i < ScrollSize; i++) {
            PCF8574_LCDSendCmd(LCD_SCROLL_RIGHT);
        }
    } else {
        for (i = 0; i < ScrollSize; i++) {
            PCF8574_LCDSendCmd(LCD_SCROLL_LEFT);
        }
    }

}
// Func Desc: moves cursor
// Param1: uint8_t row 1-2 
// Param2: uint8_t col 0-15
void PCF8574_LCDGOTO(uint8_t row, uint8_t col) {
	switch (row) {
		case 1:
			PCF8574_LCDSendCmd(LCD_LINE_ADR1 | col);
			break;
		case 2:
			PCF8574_LCDSendCmd(LCD_LINE_ADR2 | col);
			break;
		case 3:
			PCF8574_LCDSendCmd(LCD_LINE_ADR3 | col);
			break;
		case 4:
			PCF8574_LCDSendCmd(LCD_LINE_ADR4 | col);
			break;
		default:
			__NOP();
	}
}

// Func Desc: Saves a custom character to a location in CG_RAM
// Param1: CG_RAM location 0-7 we only have 8 locations 0-7
// Param2: An array of 8 bytes representing a custom character data
void PCF8574_LCDCreateCustomChar(uint8_t location, uint8_t * charmap)
{
    if (location >=8 ) {return;}
    // Base ram address 64 + location * 8
    PCF8574_LCDSendCmd(LCD_CG_RAM | (location<<3));
	for (uint8_t i=0; i<8; i++) {
		PCF8574_LCDSendData(charmap[i]);
	}
}

// Print out a customer character from CGRAM
// Param1 CGRAM location 0-7 
void PCF8574_LCDPrintCustomChar(uint8_t location)
{
	if (location >=8 ) {return;}
    
    PCF8574_LCDSendData(location);
}

// Func Desc: Turn LED backlight on and off 
// Param1: passed bool True = LED on , false = display LED off
// Note: another command must be issued before takes effect.
void PCF8574_LCDBackLightSet(bool OnOff)
{
     OnOff ? (LCDBACKLIGHT = LCD_BACKLIGHTON_MASK) : (LCDBACKLIGHT = LCD_BACKLIGHTOFF_MASK);
}


// Func Desc: vsprintf wrapper to print numerical data
// Parameters: https://www.tutorialspoint.com/c_standard_library/c_function_vsprintf.htm 
// The C library function int vsprintf(char *str, const char *format, va_list arg) 
// sends formatted output to a string using an argument list passed to it.
// Returns: If successful, the total number of characters written is returned, 
// otherwise a negative number is returned.
// Note: requires stdio.h and stdarg.h
int PCF8574_LCDPrintf(const char *fmt, ...)
{
    int length;
    char buffer[65];
    
    va_list ap;

    va_start(ap, fmt);
    length = vsprintf(buffer, fmt, ap);
    va_end(ap);
    if (length > 0) {
         PCF8574_LCDSendString(buffer);
    }
    return length;
}
 
// ********* EOF ********