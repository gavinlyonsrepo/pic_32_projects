/*
 * File: main.c
 * Description: 
 * This file contains the "main" function for a project.
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
#define DISPLAY_DELAY 5000

// Section: function Prototypes
void Setup(void);
void HelloWorld(void);

// Section: Main Loop

int main(void) {
    /* Initialize all modules */
    SYS_Initialize(NULL);
    Setup();

    while (true) {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
        HelloWorld();
        delay_ms(5000);
        LED_Toggle();
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE);
} // end of main. 


// Section :  Functions

void HelloWorld(void) {
    PCF8574_LCDSendCmd(LCD_LINE_ADR1);
    PCF8574_LCDSendString("Hello");
    PCF8574_LCDSendCmd(LCD_LINE_ADR2);
    PCF8574_LCDSendString("World"); // Display a stringPCF8574_LCDSendCmd
    PCF8574_LCDSendData('!'); // Display a single character 
}

void Setup(void) {
    LED_Clear();
    delay_ms(INIT_DELAY);
    PCF8574_LCDInit();
    PCF8574_LCDClearLine(LINE_NUM_1);
    PCF8574_LCDClearLine(LINE_NUM_2);
    LED_Set();
}

// EOF

