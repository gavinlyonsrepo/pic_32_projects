/*
* File: HD44780_I2C_lcd.h
* Description: 
 * HD44780-based character LCD 16x02 I2C(PCF8574) library header file
* Author: Gavin Lyons.
* Complier: xc32 v4.00 compiler
* PIC: PIC32CM1216CM00032
* IDE:  MPLAB X v6.00 , Harmony V3
* Created : Feb 2022
* Description: See URL for full details.
* URL: https://github.com/gavinlyonsrepo/pic_32_projects
*/

#include <stdint.h>
#include "definitions.h"

#ifndef LCD_H
#define LCD_H

// Section: Defines 

#define SLAVE_ADDRESS_LCD 0x27 //I2C  address for I2C module PCF8574 backpack on LCD

// Command Byte Codes 
// See  http://www.dinceraydin.com/lcd/commands.html for HD44780 CMDs

#define LINE_NUM_1 1
#define LINE_NUM_2 2
#define LCD_LINE_ADR1 0x80
#define LCD_LINE_ADR2 0xC0
#define LCD_HOME  0x02
#define CLRSCR 0x01
#define DISPLAY_ON 0x0C
#define DISPLAY_OFF 0x08
#define CURSOR_ON 0x0A
#define CURSOR_OFF 0x08
#define CURSOR_BLINK 0x0F
#define CURSOR_INC 0x06
#define MODE_8BIT 0x38
#define MODE_4BIT 0x28

// Codes for I2C byte
// Byte = DATA-X-en-X-rs (en=enable rs = reg select)
#define DATA_BYTE_ON 0x0D //enable=1 and rs =1 1101  YYYY-X-en-X-rs
#define DATA_BYTE_OFF 0x09 // enable=0 and rs =1 1001 YYYY-X-en-X-rs
#define CMD_BYTE_ON 0x0C  // enable=1 and rs =0 1100 YYYY-X-en-X-rs 
#define CMD_BYTE_OFF 0x08 // enable=0 and rs =0 1000 YYYY-X-en-X-rs 

// Section: Function prototypes 
void PCF8574_LCDInit (void);
void PCF8574_LCDDisplayON(bool );
//void PCF8574_LCDClearScreenCmd(void);

void PCF8574_LCDSendCmd (unsigned char data);
void PCF8574_LCDSendData (unsigned char data);

void PCF8574_LCDClearLine (uint8_t lineNo);
void PCF8574_LCDClearScreen(void);

void PCF8574_LCDSendString (char *str);

#endif