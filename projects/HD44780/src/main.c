/*
 * File: main.c
 * Description: 
 * This file contains the "main" function for  project, a set of test sequence
 * to test the HD44780 LCD library
 * Author: Gavin Lyons.
 * Complier: xc32 v4.00 compiler
 * PIC: PIC32CM1216CM00032
 * IDE:  MPLAB X v6.00
 * Created : Feb 2022
 * Description: See URL for full details.
 * URL: https://github.com/gavinlyonsrepo/pic_32_projects
 */

// Section: Included Files
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                 // SYS function prototypes
#include "my_utils.h"                   // my delay
#include "HD44780_I2C_lcd.h"

// Section: Defines
#define INIT_DELAY 1000
#define DISPLAY_DELAY_2 2000
#define DISPLAY_DELAY 5000

// Section: Function Prototypes
void Setup(void);
void HelloWorld(void);
void CursorMoveTest(void);
void ScrollTest(void);
void gotoTest(void);
void resetTest(void);
void customChar(void);
void backLightTest(void);

// Section: Main Loop

int main(void) {
    /* Initialize all modules */
    SYS_Initialize(NULL);
    Setup();

    while (true) {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
       
        HelloWorld();
        CursorMoveTest();
        ScrollTest();
        gotoTest();
        resetTest();
        customChar();
        backLightTest();
        LED_Toggle();
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE);
} // end of main. 

// Section :  Functions

void Setup(void) {
    LED_Clear();
    delay_ms(INIT_DELAY);
    PCF8574_LCDInit(CURSOR_ON);
    PCF8574_LCDClearScreen();
    PCF8574_LCDBackLightSet(true);
    LED_Set();
}

void HelloWorld(void) {
    PCF8574_LCDGOTO(1, 0);
    PCF8574_LCDSendString("Hello");
    PCF8574_LCDGOTO(2, 0);
    PCF8574_LCDSendString("World"); // Display a string
    PCF8574_LCDSendChar('!'); // Display a single character
    delay_ms(DISPLAY_DELAY);
}

void CursorMoveTest(void) {
    PCF8574_LCDMoveCursor(MOVE_RIGHT, 2);
    delay_ms(DISPLAY_DELAY);
    PCF8574_LCDMoveCursor(MOVE_LEFT, 2);
}

void ScrollTest(void) {
    for (uint8_t i = 0; i < 5; i++) {
        PCF8574_LCDScroll(MOVE_RIGHT, 1);
        delay_ms(DISPLAY_DELAY_2);
    }
    PCF8574_LCDScroll(MOVE_LEFT, 5);
    delay_ms(DISPLAY_DELAY_2);
}

void gotoTest(void) {
    PCF8574_LCDClearScreen();
    PCF8574_LCDGOTO(1, 10);
    PCF8574_LCDSendChar('A');
    PCF8574_LCDGOTO(2, 2);
    PCF8574_LCDSendString("Line");
    delay_ms(DISPLAY_DELAY);
}

void resetTest(void) {
    PCF8574_LCDResetScreen(CURSOR_BLINK);
    delay_ms(DISPLAY_DELAY);
}

void customChar(void) {

    // Data to test custom function
    uint8_t bell[8] = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
    uint8_t note[8] = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
    uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
    uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
    uint8_t duck[8] = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
    uint8_t check[8] = {0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0};
    uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
    uint8_t retarrow[8] = {0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

    PCF8574_LCDClearScreen();

    // Load the CGRAM with the data , custom characters
    PCF8574_LCDCreateCustomChar(0, bell);
    PCF8574_LCDCreateCustomChar(1, note);
    PCF8574_LCDCreateCustomChar(2, clock);
    PCF8574_LCDCreateCustomChar(3, heart);
    PCF8574_LCDCreateCustomChar(4, duck);
    PCF8574_LCDCreateCustomChar(5, check);
    PCF8574_LCDCreateCustomChar(6, cross);
    PCF8574_LCDCreateCustomChar(7, retarrow);

    PCF8574_LCDGOTO(1, 0);

    // Print out custom characters

    for (uint8_t i = 0; i < 8; i++) {
        PCF8574_LCDSendData(i);
    }

    delay_ms(DISPLAY_DELAY);
    PCF8574_LCDClearScreen();
}

void backLightTest(void)
{
    PCF8574_LCDBackLightSet(false);
    PCF8574_LCDGOTO(2, 1);
    PCF8574_LCDSendString("Backlight test");
    delay_ms(DISPLAY_DELAY);
    PCF8574_LCDBackLightSet(true);
    PCF8574_LCDClearScreen();
}

// EOF

