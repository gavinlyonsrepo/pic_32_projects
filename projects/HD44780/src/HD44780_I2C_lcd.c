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

#include "HD44780_I2C_lcd.h"
#include "my_utils.h" 


//  Send data to  lcd
void PCF8574_LCDSendData(unsigned char data) {
    unsigned char data_l, data_u;
    uint8_t data_I2C[4];

    data_l = (data << 4)&0xf0; //select lower nibble by moving it to the upper nibble position
    data_u = data & 0xf0; //select upper nibble
    data_I2C[0] = data_u | DATA_BYTE_ON; //enable=1 and rs =1 1101  YYYY-X-en-X-rs
    data_I2C[1] = data_u | DATA_BYTE_OFF; //enable=0 and rs =1 1001 YYYY-X-en-X-rs
    data_I2C[2] = data_l | DATA_BYTE_ON; //enable=1 and rs =1 1101  YYYY-X-en-X-rs
    data_I2C[3] = data_l | DATA_BYTE_OFF; //enable=0 and rs =1 1001 YYYY-X-en-X-rs

    SERCOM0_I2C_Write(SLAVE_ADDRESS_LCD, data_I2C, 4);
    while(SERCOM0_I2C_IsBusy() == true);
}

// send command to LCD
void PCF8574_LCDSendCmd(unsigned char data) {
    unsigned char data_l, data_u;
    uint8_t data_I2C[4];

    data_l = (data << 4)&0xf0; //select lower nibble by moving it to the upper nibble position
    data_u = data & 0xf0; //select upper nibble
    data_I2C[0] = data_u | CMD_BYTE_ON; // 1100 YYYY-X-en-X-rs enable=1 and rs =0
    data_I2C[1] = data_u | CMD_BYTE_OFF; // 1000 YYYY-X-en-X-rs enable=0 and rs =0
    data_I2C[2] = data_l | CMD_BYTE_ON; // 1100 YYYY-X-en-X-rs enable=1 and rs =0
    data_I2C[3] = data_l | CMD_BYTE_OFF; // 1000 YYYY-X-en-X-rs enable=0 and rs =0

    SERCOM0_I2C_Write(SLAVE_ADDRESS_LCD, data_I2C, 4);
    while(SERCOM0_I2C_IsBusy() == true);
}

// Clear a line by writing spaces to every position
void PCF8574_LCDClearLine(uint8_t lineNo) {
    if (lineNo == 1) {
        PCF8574_LCDSendCmd(LCD_LINE_ADR1);
    } else if (lineNo == 2) {
        PCF8574_LCDSendCmd(LCD_LINE_ADR2);
    } else {
        return;
    }

    for (uint8_t i = 0; i < 16; i++) {
        PCF8574_LCDSendData(' ');
    }
}

// Clear screen by writing spaces to every position
void PCF8574_LCDClearScreen(void)
{
    PCF8574_LCDClearLine(LINE_NUM_1);
    PCF8574_LCDClearLine(LINE_NUM_2);
}

/* TODO
// Clear screen using command 
void PCF8574_LCDClearScreenCmd(void)
{
     PCF8574_LCDSendCmd(LCD_HOME);
    PCF8574_LCDSendCmd(CLRSCR);
   
}
*/

// Clear screen using command 
void PCF8574_LCDDisplayON(bool OnOff)
{
    OnOff ? PCF8574_LCDSendCmd(DISPLAY_ON) : PCF8574_LCDSendCmd(DISPLAY_OFF);
   
}

// initialise LCD

void PCF8574_LCDInit(void) {
   
    delay_ms(15);
    PCF8574_LCDSendCmd(LCD_HOME);
    delay_ms(5);
    PCF8574_LCDSendCmd(LCD_HOME);
    delay_ms(5);
    PCF8574_LCDSendCmd(LCD_HOME);
    delay_ms(5);
    PCF8574_LCDSendCmd(MODE_4BIT);
    PCF8574_LCDSendCmd(DISPLAY_ON);
    //lcd_send_cmd (CURSOR_BLINK);
    PCF8574_LCDSendCmd(CLRSCR);
}

// send string to LCD

void PCF8574_LCDSendString(char *str) {
    while (*str) PCF8574_LCDSendData(*str++);
}