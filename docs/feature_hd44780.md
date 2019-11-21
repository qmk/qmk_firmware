# HD44780 LCD Displays

This is an integration of Peter Fleury's LCD library. This page will explain the basics. [For in depth documentation visit his page.](http://homepage.hispeed.ch/peterfleury/doxygen/avr-gcc-libraries/group__pfleury__lcd.html)

You can enable support for HD44780 Displays by setting the `HD44780_ENABLE` flag in your keyboards `rules.mk` to yes.

## Configuration

You will need to configure the pins used by your display, and its number of lines and columns in your keyboard's `config.h`.


Uncomment the section labled HD44780 and change the parameters as needed.
````
/*
 * HD44780 LCD Display Configuration
 */

#define LCD_LINES           2     //< number of visible lines of the display
#define LCD_DISP_LENGTH    16     //< visibles characters per line of the display
#define LCD_IO_MODE      1            //< 0: memory mapped mode, 1: IO port mode
#if LCD_IO_MODE
#define LCD_PORT         PORTB        //< port for the LCD lines
#define LCD_DATA0_PORT   LCD_PORT     //< port for 4bit data bit 0
#define LCD_DATA1_PORT   LCD_PORT     //< port for 4bit data bit 1
#define LCD_DATA2_PORT   LCD_PORT     //< port for 4bit data bit 2
#define LCD_DATA3_PORT   LCD_PORT     //< port for 4bit data bit 3
#define LCD_DATA0_PIN    4            //< pin for 4bit data bit 0
#define LCD_DATA1_PIN    5            //< pin for 4bit data bit 1
#define LCD_DATA2_PIN    6            //< pin for 4bit data bit 2
#define LCD_DATA3_PIN    7            //< pin for 4bit data bit 3
#define LCD_RS_PORT      LCD_PORT     //< port for RS line        
#define LCD_RS_PIN       3            //< pin  for RS line        
#define LCD_RW_PORT      LCD_PORT     //< port for RW line        
#define LCD_RW_PIN       2            //< pin  for RW line        
#define LCD_E_PORT       LCD_PORT     //< port for Enable line     
#define LCD_E_PIN        1            //< pin  for Enable line    
#endif
````

Should you need to configure other properties you can copy them from `quantum/hd44780.h` and set them in your `config.h`

## Usage

To initialize your display, call `lcd_init()` with one of these parameters:
````
LCD_DISP_OFF             : display off
LCD_DISP_ON              : display on, cursor off
LCD_DISP_ON_CURSOR       : display on, cursor on
LCD_DISP_ON_CURSOR_BLINK : display on, cursor on flashing
````
This is best done in your keyboards `matrix_init_kb` or your keymaps `matrix_init_user`.  
It is advised to clear the display before use.  
To do so call `lcd_clrsrc()`.

To now print something to your Display you first call `lcd_gotoxy(column, line)`. To go to the start of the first line you would call `lcd_gotoxy(0, 0)` and then print a string with `lcd_puts("example string")`.

There are more methods available to control the display. [For in depth documentation please visit the linked page.](http://homepage.hispeed.ch/peterfleury/doxygen/avr-gcc-libraries/group__pfleury__lcd.html)
