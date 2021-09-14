/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */
#include "max_LCD.h"
#include <string.h>

// pin definition and set/clear

#define RS  0x04    // RS pin
#define E   0x08    // E pin

#define SET_RS  lcdPins |= RS
#define CLR_RS  lcdPins &= ~RS
#define SET_E   lcdPins |= E
#define CLR_E   lcdPins &= ~E

#define SENDlcdPins()   pUsb->gpioWr( lcdPins )

#define LCD_sendcmd(a)  {   CLR_RS;             \
                            sendbyte(a);    \
                        }

#define LCD_sendchar(a) {   SET_RS;             \
                            sendbyte(a);    \
                        }

static byte lcdPins; //copy of LCD pins

Max_LCD::Max_LCD(USB *pusb) : pUsb(pusb) {
        lcdPins = 0;
}

void Max_LCD::init() {
        _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

        //   MAX3421E::gpioWr(0x55);

        begin(16, 1);
}

void Max_LCD::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
        if(lines > 1) {
                _displayfunction |= LCD_2LINE;
        }
        _numlines = lines;
        _currline = 0;

        // for some 1 line displays you can select a 10 pixel high font
        if((dotsize != 0) && (lines == 1)) {
                _displayfunction |= LCD_5x10DOTS;
        }

        // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
        // according to datasheet, we need at least 40ms after power rises above 2.7V
        // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
        delayMicroseconds(50000);
        lcdPins = 0x30;
        SET_E;
        SENDlcdPins();
        CLR_E;
        SENDlcdPins();
        delayMicroseconds(10000); // wait min 4.1ms
        //second try
        SET_E;
        SENDlcdPins();
        CLR_E;
        SENDlcdPins();
        delayMicroseconds(10000); // wait min 4.1ms
        // third go!
        SET_E;
        SENDlcdPins();
        CLR_E;
        SENDlcdPins();
        delayMicroseconds(10000);
        // finally, set to 4-bit interface
        lcdPins = 0x20;
        //SET_RS;
        SET_E;
        SENDlcdPins();
        //CLR_RS;
        CLR_E;
        SENDlcdPins();
        delayMicroseconds(10000);
        // finally, set # lines, font size, etc.
        command(LCD_FUNCTIONSET | _displayfunction);

        // turn the display on with no cursor or blinking default
        _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
        display();

        // clear it off
        clear();

        // Initialize to default text direction (for romance languages)
        _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
        // set the entry mode
        command(LCD_ENTRYMODESET | _displaymode);
}

/********** high level commands, for the user! */
void Max_LCD::clear() {
        command(LCD_CLEARDISPLAY); // clear display, set cursor position to zero
        delayMicroseconds(2000); // this command takes a long time!
}

void Max_LCD::home() {
        command(LCD_RETURNHOME); // set cursor position to zero
        delayMicroseconds(2000); // this command takes a long time!
}

void Max_LCD::setCursor(uint8_t col, uint8_t row) {
        int row_offsets[] = {0x00, 0x40, 0x14, 0x54};
        if(row > _numlines) {
                row = _numlines - 1; // we count rows starting w/0
        }

        command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)

void Max_LCD::noDisplay() {
        _displaycontrol &= ~LCD_DISPLAYON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void Max_LCD::display() {
        _displaycontrol |= LCD_DISPLAYON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off

void Max_LCD::noCursor() {
        _displaycontrol &= ~LCD_CURSORON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void Max_LCD::cursor() {
        _displaycontrol |= LCD_CURSORON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
}


// Turn on and off the blinking cursor

void Max_LCD::noBlink() {
        _displaycontrol &= ~LCD_BLINKON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void Max_LCD::blink() {
        _displaycontrol |= LCD_BLINKON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM

void Max_LCD::scrollDisplayLeft(void) {
        command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void Max_LCD::scrollDisplayRight(void) {
        command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right

void Max_LCD::leftToRight(void) {
        _displaymode |= LCD_ENTRYLEFT;
        command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left

void Max_LCD::rightToLeft(void) {
        _displaymode &= ~LCD_ENTRYLEFT;
        command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor

void Max_LCD::autoscroll(void) {
        _displaymode |= LCD_ENTRYSHIFTINCREMENT;
        command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor

void Max_LCD::noAutoscroll(void) {
        _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
        command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters

void Max_LCD::createChar(uint8_t location, uint8_t charmap[]) {
        location &= 0x7; // we only have 8 locations 0-7
        command(LCD_SETCGRAMADDR | (location << 3));
        for(int i = 0; i < 8; i++) {
                write(charmap[i]);
        }
}

/*********** mid level commands, for sending data/cmds */

inline void Max_LCD::command(uint8_t value) {
        LCD_sendcmd(value);
        delayMicroseconds(100);
}

#if defined(ARDUINO) && ARDUINO >=100

inline size_t Max_LCD::write(uint8_t value) {
        LCD_sendchar(value);
        return 1; // Assume success
}
#else

inline void Max_LCD::write(uint8_t value) {
        LCD_sendchar(value);
}
#endif

void Max_LCD::sendbyte(uint8_t val) {
        lcdPins &= 0x0f; //prepare place for the upper nibble
        lcdPins |= (val & 0xf0); //copy upper nibble to LCD variable
        SET_E; //send
        SENDlcdPins();
        delayMicroseconds(2);
        CLR_E;
        delayMicroseconds(2);
        SENDlcdPins();
        lcdPins &= 0x0f; //prepare place for the lower nibble
        lcdPins |= (val << 4) & 0xf0; //copy lower nibble to LCD variable
        SET_E; //send
        SENDlcdPins();
        CLR_E;
        SENDlcdPins();
        delayMicroseconds(100);
}
