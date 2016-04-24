
// This program drives a STM32F103RB to a 2x16 Hitachi H44780 LCD, 
//  connected over a "LCD backpack"; a I2C to parallel driver.
// I2C bus is used for communication with the LCD. 
// This version of the program is for 2x16 LCD, red backpack, labeled Funduino.
// Connect:
//  SDA -> I2C1_SDA (PB7, Morpho CN7, Pin21)
//  SCL -> I2C1_SCL (PB6, Morpho CN10, Pin17)
//     (I2C1: SCL, SDA are 5V tolerant.)
//  5V (Morpho, CN7, Pin18)
//  GND (Morpho, CN7, Pin20
//  Connect 10K pull up resistors from SCL and SDA to 5V.

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_i2c.h"
#include "delay.h"
#include "I2C.h"
#include "LiquidCrystal_I2C.h"

// Function declarations
int strlen(const char *);
char *strrev(char *);
char *itoa(int, char *, int);

int strlen(const char *str) {
	const char *s;

	s = str;
	while (*s)
		s++;
	return s - str;
}

char *strrev(char *str) {
	char *p1, *p2;

	if (!str || !*str)
		return str;

	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return str;
}

char *itoa(int n, char *s, int b) { //b is for number base; 2,8,10,16 etc
	static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i=0, sign;

	if ((sign = n) < 0)
		n = -n;

	do {
		s[i++] = digits[n % b];
	} while ((n /= b) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	return strrev(s);
}

int main()
{
  uint8_t data;
  //Describe special character:
  uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0}; 
  int i;
  int x;
  char buf[10];

  LCDI2C_init(0x27,16,2);  //Setup for I2C address 27, 16x2 LCD.

  // Create and write special character at location 0.
  //  Locations 0-7 are available in the 44780 controller:
  LCDI2C_createChar(0, heart);
  // It was necessary to do a LCDI2C_clear after the char definition.
  // Probably a quirk of the library.
  LCDI2C_clear();

  // -------  blink backlight  -------------
  LCDI2C_backlight(); //Turn on Backlight
  Delay(100);
  LCDI2C_noBacklight(); //Turn off Backlight
  Delay(100);
  LCDI2C_backlight(); //Turn on Backlight

  LCDI2C_write_String("STM32F103 ");

  LCDI2C_write(0); //Write the special character at the next available location.
  // Another ASCII character can also be written.

  //Set cursor position. (column, line) Top line is 0, bottom is 1.
  LCDI2C_setCursor(0,1);


  //Write an integer:
  LCDI2C_write_String("ARM-GCC  x=");
  x=0;

  while (1){
    itoa(x, buf, 16); // itoa takes number base as 3rd argument. Here; hex.
    LCDI2C_setCursor(11,1);
    LCDI2C_write_String(buf);
    LCDI2C_write_String("  ");
    x=x+1;
    Delay(200);
    if (x>255)
      x=0;
  }
}


#ifdef USE_FULL_ASSERT
  void assert_failed ( uint8_t* file, uint32_t line)
  {
    /* Infinite loop */
    /* Use GDB to find out why we're here */
    while (1);
  }
#endif
