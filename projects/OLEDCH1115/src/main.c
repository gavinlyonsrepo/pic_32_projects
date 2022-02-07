/*******************************************************************************
  Main Source File

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system. 
 
 * URL : Project URL:  https://github.com/gavinlyonsrepo/pic_32_projects
 *******************************************************************************/


// Section: Included Files
#include <stdio.h>                      // sprintf
#include <stdint.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"               // SYS function prototypes
#include "ER_OLEDM1_CH1115.h"
#include "my_utils.h"

#define OLEDcontrast 0x80 //Contrast 00 to FF , 0x80 is default. user adjust
#define DisplayDelay1 5000
#define DisplayDelay2 0

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
void mySetup(void);
void UpdateDisplayDelay(void);
void DisplayText(void);
void DisplayGraphics(void);
void DisplayBitmap(void);
void DisplayMiscTests(void);

int main(void) {
    /* Initialize all modules */
    SYS_Initialize(NULL);
    mySetup();

    while (true) {
        SYS_Tasks();
        DisplayText(); // Font test
        DisplayGraphics(); // graphics test
        DisplayBitmap(); // bitmap test
        DisplayMiscTests();   // Function test
        while(1) {};
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE);
}

// Display Bitmap , A series of tests to display the bitmap mode
void DisplayBitmap(void) {
    // 'small image', 20x20px bitmap bi-colour horizontally addressed
    const uint8_t smallImageHa[60] = {
        0xff, 0xff, 0xf0, 0xfe, 0x0f, 0xf0, 0xf0, 0x02, 0xf0, 0xe1, 0xf8, 0x70,
        0xc7, 0xfe, 0x30, 0xc3, 0xff, 0x10, 0x80, 0x7f, 0x10, 0x80, 0x3f, 0x90,
        0x80, 0x3d, 0x80, 0x00, 0x30, 0x80, 0x00, 0x18, 0x80, 0x80, 0x1d, 0x80,
        0x80, 0x0f, 0x10, 0x80, 0x00, 0x10, 0xc0, 0x00, 0x30, 0xc0, 0x00, 0x30,
        0xe0, 0x00, 0x70, 0xf0, 0x00, 0xf0, 0xfc, 0x03, 0xf0, 0xff, 0x9f, 0xf0
    };

    // 'small image', 20x20px bitmap bi-colour vertically addressed
    const uint8_t smallImage[60] = {
        0xff, 0x3f, 0x0f, 0x07, 0x03, 0x13, 0x33, 0x39, 0x39, 0x79, 0xf9, 0xf9,
        0xfb, 0xf3, 0xf7, 0xe3, 0x87, 0x0f, 0x1f, 0xff, 0xf9, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x1d, 0x19, 0x10, 0x19,
        0x0f, 0x00, 0xc0, 0xf0, 0x0f, 0x0f, 0x0f, 0x0e, 0x0c, 0x0c, 0x08, 0x08,
        0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x0c, 0x0c, 0x0e, 0x0f, 0x0f, 0x0f
    };
    // Writes bitmap to buffer
    OGdrawBitmapBuffer(25, 22, 20, 20, BACKGROUND, FOREGROUND, (uint8_t*) smallImageHa);
    OGdrawBitmapBuffer(55, 22, 20, 20, FOREGROUND, BACKGROUND, (uint8_t*) smallImageHa);
    UpdateDisplayDelay();
    
    // Writes directly to screen 
    OLEDFillScreen(0x00, 0);
    OLEDBitmap(50, 10, 20, 20, (uint8_t*) smallImage);
    delay_ms(5000);
    OLEDFillScreen(0x00, 0);

}

// Display Graphics , A series of tests to display the graphics mode
void DisplayGraphics(void) {
    //Q1 ||  Q2
    //---------
    //Q3 ||  Q4
    //
    bool colour = 1;
    uint8_t count = 0;
    OLEDclearBuffer(); // Clear the buffer
    while (count < 15) {
        colour = !colour;

        // Draw the X
        OGdrawLine(64, 0, 64, 64, FOREGROUND);
        OGdrawFastVLine(62, 0, 64, FOREGROUND);
        OGdrawFastHLine(0, 32, 128, FOREGROUND);

        // Q1
        OGfillRect(0, 10, 20, 20, colour);
        OGfillCircle(40, 20, 10, FOREGROUND);

        // Q2
        OGfillTriangle(80, 25, 90, 5, 100, 25, !colour);
        OGdrawRect(105, 10, 15, 15, FOREGROUND);
        // Q3
        OGfillRoundRect(0, 40, 40, 20, 10, !colour);
        // Q4
        char i;
        for (i = 0; i < 10; i++) {
            OGdrawRect(70 + i, 40 + i, 50 - i * 2, 20 - i * 2, FOREGROUND);
            OLEDupdate();
            delay_ms(50);
        }
        OLEDclearBuffer();
        count++;
    }
    UpdateDisplayDelay();
}

// Display text , A series of tests to display the text mode

void DisplayText(void) {

    OGsetTextWrap(true);
    OLEDclearBuffer(); // Clear the buffer
    OGsetFontNum(OLEDFont_Default);
    // Test 1
    OGdrawText(0, 0, "3.14", FOREGROUND, BACKGROUND, 3);

    // Test 2
    int count = 123;
    char countDisplayStr[4] = {0};
    sprintf(countDisplayStr, "%i", count);
    OGdrawText(0, 30, countDisplayStr, FOREGROUND, BACKGROUND, 2);

    // Test 3
    OGdrawText(0, 50, "HELLO WORLD", BACKGROUND, FOREGROUND, 1);

    // Test 4
    OGdrawChar(95, 15, 'H', FOREGROUND, BACKGROUND, 6);

    UpdateDisplayDelay();

    // Test 5
    OGdrawText(0, 0, "ASCII FONT 0-127", FOREGROUND, BACKGROUND, 1);
    OGsetCursor(0, 15);
    uint8_t x = 0;
    uint8_t y = 15;

    // Print first 127 chars of font
    for (char i = 0; i < 126; i++) {
        if (i == '\n' || i == '\r') continue;
        if (x > 110) {
            x = 0;
            y += 9;
        }
        OGdrawChar(x, y, i, FOREGROUND, BACKGROUND, 1);
        x += 7;
        delay_ms(1);

    }
    UpdateDisplayDelay();

    OGdrawText(0, 0, "ASCII font 128-255", FOREGROUND, BACKGROUND, 1);
    x = 0;
    y = 15;
    OGsetCursor(x, y);

    for (uint8_t i = 128; i < 255; i++) {
        if (x > 110) {
            x = 0;
            y += 9;
        }
        OGdrawChar(x, y, i, FOREGROUND, BACKGROUND, 1);
        x += 7;
        delay_ms(1);
    }

    UpdateDisplayDelay();

    // Test 7
    OGsetFontNum(OLEDFont_Default);
    OGdrawText(0, 0, "Thick Font:", FOREGROUND, BACKGROUND, 1);

    OGsetFontNum(OLEDFont_Thick);
    OGdrawText(0, 15, "123", FOREGROUND, BACKGROUND, 1);
    OGdrawChar(70, 25, 'T', FOREGROUND, BACKGROUND, 4);
    UpdateDisplayDelay();

    // Test 8
    OGsetFontNum(OLEDFont_Default);
    OGdrawText(0, 0, "Seven Segment:", FOREGROUND, BACKGROUND, 1);
    OGsetFontNum(OLEDFont_Seven_Seg);
    OGdrawText(0, 15, "123", FOREGROUND, BACKGROUND, 1);
    OGdrawChar(70, 25, 's', FOREGROUND, BACKGROUND, 4);
    UpdateDisplayDelay();

    // Test 9
    OGsetFontNum(OLEDFont_Default);
    OGdrawText(0, 0, "Wide Font:", FOREGROUND, BACKGROUND, 1);
    OGsetFontNum(OLEDFont_Wide);
    OGdrawText(0, 15, "123", FOREGROUND, BACKGROUND, 1);
    OGdrawChar(70, 25, 'W', FOREGROUND, BACKGROUND, 4);
    UpdateDisplayDelay();

    //Test 10
    OGsetFontNum(OLEDFont_Default);
    OGdrawText(0, 0, "bigNums font:", FOREGROUND, BACKGROUND, 1);

    OGsetFontNum(OLEDFont_Bignum);
    char myString[9] = {'1', '3', ':', '2', '6', ':', '1', '8'};
    OGdrawTextBigNum(0, 32, myString, BACKGROUND, FOREGROUND); // Test 10a drawTextBigNum
    UpdateDisplayDelay();

    // Test 10b
    OGdrawCharBigNum(0, 0, '8', FOREGROUND, BACKGROUND); // Test 10b drawCharBigNum
    OGdrawCharBigNum(40, 32, '4', BACKGROUND, FOREGROUND);
    UpdateDisplayDelay();

} // end

// initialize the OLED
void mySetup(void) {
    OLEDbegin(OLEDcontrast); 
    OGInit();
    OLEDFillScreen(0x00, 0);
    OGsetTextColor(FOREGROUND, BACKGROUND);
    OGsetFontNum(OLEDFont_Default);
    OLEDclearBuffer(); 
}

void UpdateDisplayDelay(void) {
    OLEDupdate(); // Write to the buffer
    delay_ms(DisplayDelay1);
    OLEDclearBuffer();
}

// A series of tests to check OLED miscellaneous functions.
void DisplayMiscTests(void)
{
  OGsetFontNum(1);
  OGsetTextSize(1);

  //  ** Test A OLED enable and disable **
  OGdrawText(0, 30, "OLED Disable test 1", FOREGROUND, BACKGROUND, 1);
  OLEDupdate();
  delay_ms(3000); //display message
  
  OLEDEnable(0); //turn off display (sleep mode 500uA measured)
  delay_ms(3000); //wait for 3
  OLEDEnable(1); //turn on
  delay_ms(2000); //display message
  OLEDclearBuffer();

  // ** Test B inverse **
  OGdrawText(0, 10, "OLED Inverse test 2", FOREGROUND, BACKGROUND, 1);
  OLEDupdate();
  delay_ms(3000);
  OLEDInvert(1); // Inverted
  delay_ms(5000);
  OLEDInvert(0);
  delay_ms(1000);


  // ** Test C OLED flip **
  OLEDclearBuffer();
  OGdrawText(5, 5, "Flip test 3", FOREGROUND, BACKGROUND, 1);
  OLEDupdate();
  delay_ms(4000);
  OLEDFlip(1);
  delay_ms(4000);
  OLEDFlip(0);
  delay_ms(2000);

  // ** Test D contrast **
  OLEDclearBuffer();
  OGdrawText(2, 1, "Contrast test 4", FOREGROUND, BACKGROUND, 1);
  OLEDupdate();
  delay_ms(2500);
  OLEDFillScreen(0x77, 0); // fill screen

  OLEDContrast(0x00);
  delay_ms(1000);
  OLEDContrast(0x80);
  delay_ms(1000);
  OLEDContrast(0xFF);
  delay_ms(1000);
  OLEDContrast(OLEDcontrast);
  delay_ms(1000);
  OLEDclearBuffer();

  // ** Test E OLED scroll **
  OLEDclearBuffer();
  OGdrawText(0, 40, "Scroll test 5 ", FOREGROUND, BACKGROUND, 1);
  OLEDupdate();
  delay_ms(2500);

  // See .c file for more info on these parameters.
  uint8_t timeInterval = 0x00; // 6 frames 0x00 - 0x07
  uint8_t scrollDirection = 0x26; //right 0x26 or 0x27
  uint8_t scrollMode = 0x28; // contiunous 0x28-0x2A,
  OLEDscrollSetup(timeInterval, scrollDirection , scrollMode);
  OLEDscroll(1); //start scroll
  delay_ms(15000);
  OLEDscroll(0); // stop Scroll

  delay_ms(1);

  timeInterval = 0x02; // 64 frames , 0x00 - 0x07
  scrollDirection = 0x27; // left , 0x26 or 0x27
  scrollMode = 0x29; // contiunous 0x28 one shot 0x29 , one col 0x2A,
  OLEDscrollSetup(timeInterval, scrollDirection , scrollMode);
  OLEDscroll(1); //start
  delay_ms(15000);
  OLEDscroll(0); // stop

  // ** TEST F fade ~ breath effect **
  OLEDclearBuffer();
  OGdrawText(0, 40, "Fade effect test 6", FOREGROUND, BACKGROUND, 1);
  OLEDupdate();
  delay_ms(3000);
  OLEDfadeEffect(ERMCCH1115_BREATHEFFECT_DATA);
  OLEDFillScreen(0xE3, 0);
  delay_ms(10000);
  OLEDfadeEffect(0x00); // switch off fade
  
  OLEDclearBuffer();
  OLEDFillScreen(0x00, 0);
  OGdrawText(0, 0, "End of tests", FOREGROUND, BACKGROUND, 1);
  OLEDupdate();
  delay_ms(5000);
}

/*******************************************************************************
 End of File
 */