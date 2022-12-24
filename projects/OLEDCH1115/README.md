
![ OLED ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/oled.jpg)

Table of contents
---------------------------

  * [Overview](#overview)
  * [Output](#output)
  * [Hardware](#hardware)
  * [Software](#software)
  
Overview
--------------------
* Name : ER_OLEDM1_CH1115
* Title : Library to support the ER-OLEDM1.09-1 128X64 OLED Display Module driven by the CH1115 controller for the PIC-32 micro-controller
* Description : 

1. Tested on PIC32CM1216MC00032       
2. Invert colour, vertical rotate, sleep, fade effect, horizontal scroll and contrast control functions supported.
3. 8 ASCII fonts included.
4. Graphics support included.
5. Single buffer mode.
6. Bitmaps supported.
7. Hardware SPI.
8. Printf method included for printing numerical data

* Port of my Arduino [library](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115)
* Author: Gavin Lyons
* ToolChain: MPLABX version 6.0 , C XC32 , Harmony V3.0

Output
-----------------------------

Output Screenshots.

![ output ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/output.jpg)
![ output ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115_RPI/blob/main/extras/image/fontpic.jpg)

Hardware
----------------------------

CH1115 is a single-chip CMOS OLED driver with controller for organic light emitting diode dot-matrix graphic display system. CH1115 consists of 128 segments, 64 commons that can support a maximum display resolution of 128 X 64. It is designed for Common Cathode type OLED panel. ER-OLEDM1.09-1W-SPI is a White 1.09" OLED Display Panel with Breakout Board. This module is a combination of the two.(controller and OLED)

| pin no  | pin name | pin desc | PIC HW SPI | 
|---|---|---| --- | 
| 1 | Gnd | Ground | gnd | 
| 2 | VCC | Voltage supply | vcc | 
| 3 | SCL | Serial clock input | SCK PA17 SERCOM3 PAD 1| 
| 4 | SDA | Serial data input | MOSI PA19 SERCOM3 PAD 3| 
| 5 | RES | Reset signal input  | PA02 | 
| 6 | DC | Data or Command | PA03 | 
| 7 | CS | Chip select input | PA04 | 


 This wiring Diagram from the manufacturer datasheet showing hardware setup connected to a 3.3 volt system MCU.

![ wiring ](https://github.com/gavinlyonsrepo/ER_OLEDM1_CH1115/blob/main/extras/image/wiring.jpg)


Software
-------------------------

*Timer0*

Timer 0 is used in main.c to provide mS delays function.
Setup for 1mS tick.

*fonts*

There are eight fonts.
The fonts 1-6 are a byte high(at text size 1) scale-able fonts, columns of padding added by SW.
Font 7-8 are large numerical font but it is numbers only and cannot be scaled(just one size).  
Font 7-8 will print just numbers + semi-colons, using the printf method it is possible to print 
'.' and '-' characters with font 7-8.

Font data table: 

| Font num | Font enum name | Font size xbyy |  ASCII range | Size in bytes |
| ------ | ------ | ------ | ------ |  ------ | 
| 1 | OLEDFontType_Default | 5x8 | ASCII 0 - 0xFF, Full Extended  | 1275 |
| 2 | OLEDFontType_Thick   | 7x8 |  ASCII  0x20 - 0x5A, no lowercase letters | 406 | 
| 3 | OLEDFontType_SevenSeg  | 4x8 | ASCII  0x20 - 0x7A | 360 |
| 4 | OLEDFontType_Wide | 8x8 |  ASCII 0x20 - 0x5A, no lowercase letters| 464 |
| 5 | OLEDFontType_Tiny | 3x8 | ASCII  0x20 - 0x7E | 285 |
| 6 | OLEDFontType_Homespun  | 7x8 | ASCII  0x20 - 0x7E |  658 |
| 7 | OLEDFontType_Bignum | 16x32 | ASCII 0x30-0x3A ,Numbers + : . only | 704 |
| 8 | OLEDFontType_Mednum | 16x16 | ASCII 0x30-0x3A , Numbers + : . only | 352 |


*bitmaps*

Bitmaps can be turned to data [here at link]( https://javl.github.io/image2cpp/) , 

1. OLEDBitmap function
 
Bitmaps are written directly to screen, not buffer, Updating the buffer will overwrite them(unless bitmap set to buffer)  Use vertical addressed data  to make  bitmap.

2. OGdrawBitmapBufferXX function 

Bitmaps are written to buffer with these functions 

* OGdrawBitmapBufferHa , Use horizontal addressed data to make bitmap.
* OGdrawBitmapBufferVa ,  Use vertical addressed data  to make  bitmap.

*User adjustments*

When the user calls OLEDbegin() to start OLED they can specify a contrast setting from 0x00 to 0xFF. Datasheet says 0x80 is default. User can also change contrast on the fly.
Screen can be disabled to enter a sleep type mode where OLED draws 500uA.
Screen pixel colour can be inverted and also screen can be vertically rotated. 

There is a "fade or breath display effect". Whose parameters(time brightness) can be adjusted by passing data to function see "OLEDfadeEffect" function header  in .c file and datasheet for details.
default is 0x81.

There is a  Horizontal scroll effect. Whose parameters: Time-interval , direction , mode,
can be adjusted by passing data to function see "OLEDscrollSetup" function header in .c file and datasheet for details. defaults are : 6 frames , right , continuous mode.

Files
-------------------

X = ER_OLEDM1_CH1115 in table below

| Src Files| Desc |
| ------ | ------ |
| X.h | library header file  |
| X.c|  library  source file  |
| X_graphics.h | graphics header file |
| X_graphics.c |  graphics source file |
| X_graphics_font.c |  font data file |
| main.c | test sequence file |
| my_utils.h | misc utilty header file |
| my_utils.c | misc utility source file  |
