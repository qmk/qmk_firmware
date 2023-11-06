// Just a copy of the HelloWorld example bundled with the LiquidCrystal library in the Arduino IDE

// HD44780 compatible LCD display via MAX3421E GPOUT support header
// pinout: D[4-7] -> GPOUT[4-7], RS-> GPOUT[2], E ->GPOUT[3]

#include <max_LCD.h>

// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
Max_LCD lcd(&Usb);

void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, World!");
}

void loop() {
  // Set the cursor to column 0, line 1 (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // Print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
