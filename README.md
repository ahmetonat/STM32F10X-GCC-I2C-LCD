# STM32F10X-GCC-I2C-LCD
STM32F103 driving an LCD with I2C backpack (Funduino). Uses Gnu ARM Embedded toolchain and no GUI for development

This project demonstrates the use of GCC ARM Embedded toolchain without a GUI. This example is about driving a STM32F103RB to a 2x16 Hitachi H44780 LCD, connected over a "LCD backpack"; a I2C to parallel driver. I2C bus is used for communication with the LCD.

See the blog post at: http://aviatorahmet.blogspot.com/2016/04/arm-stm32f10x-gcc-display-variables-on.html

The processor is STM32F103RB, I2C module initialization and use is demonstrated. STM32F10x_StdPeriph_Lib_V3.5.0 is used for
standard peripheral drivers etc.

This version of the program is for the red 2x16 LCD Backpack, labeled Funduino. However most of the clones are the same as long as they use the PCF8574T I2C to parallel converter chip. Check the address and write that value in main.c (default is 0x27).

Connections:
 SDA -> I2C1_SDA (PB7, Morpho CN7, Pin21)
 SCL -> I2C1_SCL (PB6, Morpho CN10, Pin17)
 5V (Morpho, CN7, Pin18)
 GND (Morpho, CN7, Pin20
 (STM32F103 I2C1: SCL, SDA are 5V tolerant.)
 Connect 10K pull up resistors from SCL and SDA to 5V.

The LiquidCrystal library is by YWROBOT, but was written for Arduino. ARM conversion and most of the code here was taken from this post: http://habrahabr.ru/post/223947/ (in Russian. I do not know Russian...). 
I used this as one of the first steps when learning how to program STM32F103. Tweaked it, and prepared a project, complete with all files. I am posting it in the hope that someone will benefit from this complete project.
