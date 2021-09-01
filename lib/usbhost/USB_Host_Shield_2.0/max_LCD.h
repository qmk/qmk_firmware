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
//HD44780 compatible LCD display via MAX3421E GPOUT support header
//pinout: D[4-7] -> GPOUT[4-7], RS-> GPOUT[2], E ->GPOUT[3]
//

#ifndef _Max_LCD_h_
#define _Max_LCD_h_

#include "Usb.h"
#include "Print.h"

// commands
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON           0x04
#define LCD_DISPLAYOFF          0x00
#define LCD_CURSORON            0x02
#define LCD_CURSOROFF           0x00
#define LCD_BLINKON             0x01
#define LCD_BLINKOFF            0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00

// flags for function set
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00

class Max_LCD : public Print {
        USB *pUsb;

public:
        Max_LCD(USB *pusb);
        void init();
        void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
        void clear();
        void home();
        void noDisplay();
        void display();
        void noBlink();
        void blink();
        void noCursor();
        void cursor();
        void scrollDisplayLeft();
        void scrollDisplayRight();
        void leftToRight();
        void rightToLeft();
        void autoscroll();
        void noAutoscroll();
        void createChar(uint8_t, uint8_t[]);
        void setCursor(uint8_t, uint8_t);
        void command(uint8_t);

#if defined(ARDUINO) && ARDUINO >=100
        size_t write(uint8_t);
        using Print::write;
#else
        void write(uint8_t);
#endif

private:
        void sendbyte(uint8_t val);
        uint8_t _displayfunction; //tokill
        uint8_t _displaycontrol;
        uint8_t _displaymode;
        uint8_t _initialized;
        uint8_t _numlines, _currline;
};

#endif
