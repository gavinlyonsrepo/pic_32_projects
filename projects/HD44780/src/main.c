/*
 * File: main.c
 * Description: 
 * This file contains the "main" function for project, a set of test sequence
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

#include "my_utils.h"                   // my delay user custom
#include "HD44780_I2C_lcd.h"            // user custom

// Section: Defines
#define INIT_DELAY 100
#define DISPLAY_DELAY_2 2000
#define DISPLAY_DELAY 5000


// Section: Function Prototypes
void Setup(void);
void TestPrintf(void);
void HelloWorld(void);
void CursorMoveTest(void);
void ScrollTest(void);
void GotoTest(void);
void CursorTypeTest(void);
void EntryModeTest(void);
void CustomChar(void);
void BackLightTest(void);


// Section: Main Loop

int main(void) {
    /* Initialize all modules */
    SYS_Initialize(NULL);
    Setup();

    while (true) {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
        TestPrintf(); // test numerical data
        EntryModeTest(); // test entry mode commands
        HelloWorld(); // test string + character data
        CursorMoveTest(); //test cursor move
        ScrollTest(); // test screen scroll

        GotoTest(); // test cursor goto and clear line 
        CursorTypeTest(); // test reset + change cursor types 
        CustomChar(); // test custom character save and print
        BackLightTest(); //test back light LED, on and off

    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE);
} // end of main. 

// Section :  Functions

void Setup(void) {
    customDelayMS(INIT_DELAY);
    // Cursor type , rows number , col number , I2C address) 
    PCF8574_LCDInit(LCDCursorTypeOn, 2, 16, 0x27);
    PCF8574_LCDClearScreen();
    PCF8574_LCDBackLightSet(true);
}

void TestPrintf(void) {
    uint16_t testOne = 62005;
    int16_t testTwo = -4501;
    double testThree = 3.143567;
    double testFour = -14.561;

    PCF8574_LCDGOTO(LCDLineNumberOne, 0);
    PCF8574_LCDPrintf("%u ", testOne);
    PCF8574_LCDPrintf("%d", testTwo);
    PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
    PCF8574_LCDPrintf("%.4f ", testThree);
    PCF8574_LCDPrintf("%.2f", testFour);

    customDelayMS(DISPLAY_DELAY);
    PCF8574_LCDClearScreen();
}

void EntryModeTest(void) {

    PCF8574_LCDSendCmd(LCDEntryModeOne);
    PCF8574_LCDGOTO(LCDLineNumberOne, 8);
    PCF8574_LCDSendString("1234"); // <-C4321
    customDelayMS(DISPLAY_DELAY_2);
    PCF8574_LCDClearScreenCmd();

    PCF8574_LCDSendCmd(LCDEntryModeTwo);
    PCF8574_LCDGOTO(LCDLineNumberTwo, 8);
    PCF8574_LCDSendString("1234"); // C4321->
    customDelayMS(DISPLAY_DELAY_2);
    PCF8574_LCDClearScreenCmd();

    PCF8574_LCDSendCmd(LCDEntryModeFour);
    PCF8574_LCDGOTO(LCDLineNumberTwo, 8);
    PCF8574_LCDSendString("1234"); // <-1234C
    customDelayMS(DISPLAY_DELAY_2);
    PCF8574_LCDClearScreenCmd();

    PCF8574_LCDSendCmd(LCDEntryModeThree); // Set back to default entry mode
    PCF8574_LCDClearScreenCmd();
}

void HelloWorld(void) {
    PCF8574_LCDGOTO(LCDLineNumberOne, 0);
    PCF8574_LCDSendString("Hello");
    PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
    PCF8574_LCDSendString("World"); // Display a string
    PCF8574_LCDSendChar('!'); // Display a single character
    customDelayMS(DISPLAY_DELAY);
}

void CursorMoveTest(void) {
    PCF8574_LCDMoveCursor(LCDMoveRight, 2);
    customDelayMS(DISPLAY_DELAY_2);
    PCF8574_LCDMoveCursor(LCDMoveLeft, 2);
    customDelayMS(DISPLAY_DELAY_2);
}

void ScrollTest(void) {
    for (uint8_t i = 0; i < 5; i++) {
        PCF8574_LCDScroll(LCDMoveRight, 1);
        customDelayMS(DISPLAY_DELAY_2);
    }
    PCF8574_LCDScroll(LCDMoveLeft, 5);
    customDelayMS(DISPLAY_DELAY_2);
}

void GotoTest(void) {
    PCF8574_LCDClearScreen();
    PCF8574_LCDGOTO(LCDLineNumberOne, 10);
    PCF8574_LCDSendChar('A');
    PCF8574_LCDGOTO(LCDLineNumberTwo, 2);
    PCF8574_LCDSendString("Line2");
    customDelayMS(DISPLAY_DELAY_2);
    PCF8574_LCDClearLine(LCDLineNumberOne);
    customDelayMS(DISPLAY_DELAY_2);
    PCF8574_LCDClearLine(LCDLineNumberTwo);
    customDelayMS(DISPLAY_DELAY_2);
}

void CursorTypeTest(void) {
    PCF8574_LCDResetScreen(LCDCursorTypeOnBlink); //type 4 cursor
    PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
    PCF8574_LCDSendString("Cursor no 4");
    customDelayMS(DISPLAY_DELAY);
    PCF8574_LCDClearLine(LCDLineNumberTwo);

    PCF8574_LCDResetScreen(LCDCursorTypeOff); //type 1 cursor
    PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
    PCF8574_LCDSendString("Cursor no 1");
    customDelayMS(DISPLAY_DELAY);
    PCF8574_LCDClearLine(LCDLineNumberTwo);

    PCF8574_LCDResetScreen(LCDCursorTypeBlink); //type 2 cursor
    PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
    PCF8574_LCDSendString("Cursor no 2");
    customDelayMS(DISPLAY_DELAY);
    PCF8574_LCDClearLine(LCDLineNumberTwo);

    PCF8574_LCDResetScreen(LCDCursorTypeOn); // Back to initial state , type 3
    PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
    PCF8574_LCDSendString("Cursor no 3");
    customDelayMS(DISPLAY_DELAY_2);
}

void CustomChar(void) {

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

    PCF8574_LCDGOTO(LCDLineNumberOne, 0);

    // Print out custom characters

    for (uint8_t i = 0; i < 8; i++) {
        PCF8574_LCDPrintCustomChar(i);
        PCF8574_LCDMoveCursor(LCDMoveRight, 1);
    }

    customDelayMS(DISPLAY_DELAY);
    PCF8574_LCDClearScreen();
}

void BackLightTest(void) {
    PCF8574_LCDBackLightSet(false);
    PCF8574_LCDGOTO(LCDLineNumberTwo, 1);
    PCF8574_LCDSendString("Backlight test");
    customDelayMS(DISPLAY_DELAY);
    PCF8574_LCDBackLightSet(true);
    PCF8574_LCDClearScreen();

    PCF8574_LCDGOTO(LCDLineNumberTwo, 0);
    PCF8574_LCDSendString("End of Tests");
    customDelayMS(DISPLAY_DELAY);
}


// EOF

