Overview
--------------------------------------------
* Description:
Library to drive a LCD 16X02 character display driven by HD44780 via the I2C bus and a PCF8574 Interface "backpack" board for a PIC32CM
* Author: Gavin Lyons.
* Complier: xc32 v4.00 compiler
* IDE:  MPLAB X v6.00 , harmony v3
* PIC tested on: PIC32CM1216MC00032

Hardware
----------------------

1. SDA = 	SDA PA08 SERCOM0 I2C PAD 0
2. SCLK = SCLK PA09 SERCOM0 I2C PAD 1 


Software
------------------------------

*Timer0*

Timer 0 is used  to provide mS delays function. Setup for 1mS tick.

*Files* 

| Src Files| Desc |
| ------ | ------ |
| HD44780_I2C_lcd.h | library header file  |
| HD44780_I2C_lcd.c|  library  source file  |
| main.c | test sequence file |
| my_utils.h | misc utility header file |
| my_utils.c | misc utility source file  |
