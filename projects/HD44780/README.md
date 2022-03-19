![ lcd ](https://github.com/gavinlyonsrepo/pic_16F1619_projects/blob/master/images/LCDPCF.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Hardware](#hardware)
  * [Software](#software)
  * [Output](#output)


Overview
--------------------------------------------
* Description:

Library to drive a LCD 16X02 character display driven by HD44780 via the I2C bus with a PCF8574 Interface "backpack" board for a PIC32CM microcontroller

* Backlight, Scroll, Cursor control.
* Custom character support + print method for numerical data.
* Tested only on size  16x02 but may work on other sizes (20x4 8x2 etc)
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

Output
---------------------

Output  of custom character test in test file.

![ pic ](https://github.com/gavinlyonsrepo/HD44780_LCD_RPI/blob/main/extras/image/custom_output.jpg)
