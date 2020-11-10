# group `pfleury_lcd` {#group__pfleury__lcd}

Basic routines for interfacing a HD44780U-based character LCD display.

```cpp
#include <lcd.h> 
```

LCD character displays can be found in many devices, like espresso machines, laser printers. The Hitachi HD44780 controller and its compatible controllers like Samsung KS0066U have become an industry standard for these types of displays.

This library allows easy interfacing with a HD44780 compatible display and can be operated in memory mapped mode (LCD_IO_MODE defined as 0 in the include file lcd.h.) or in 4-bit IO port mode (LCD_IO_MODE defined as 1). 8-bit IO port mode is not supported.

Memory mapped mode is compatible with old Kanda STK200 starter kit, but also supports generation of R/W signal through A8 address line.

**See also**: The chapter [Interfacing a HD44780 Based LCD to an AVR]( http://homepage.hispeed.ch/peterfleury/avr-lcd44780.html) on my home page, which shows example circuits how to connect an LCD to an AVR controller.

Peter Fleury [pfleury@gmx.ch](mailto:pfleury@gmx.ch)[http://tinyurl.com/peterfleury](http://tinyurl.com/peterfleury)

2.0

(C) 2015 Peter Fleury, GNU General Public License Version 3

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------

