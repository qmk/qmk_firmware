/* mbed TextDisplay Library Base Class
 * Copyright (c) 2007-2009 sford
 * Released under the MIT License: http://mbed.org/license/mit
 *
 * A common base class for Text displays
 * To port a new display, derive from this class and implement
 * the constructor (setup the display), character (put a character
 * at a location), rows and columns (number of rows/cols) functions.
 * Everything else (locate, printf, putc, cls) will come for free
 *
 * The model is the display will wrap at the right and bottom, so you can
 * keep writing and will always get valid characters. The location is
 * maintained internally to the class to make this easy
 */

#ifndef MBED_TEXTDISPLAY_H
#define MBED_TEXTDISPLAY_H

#include "mbed.h"

class TextDisplay : public Stream {
public:

    // functions needing implementation in derived implementation class
    TextDisplay(const char *name = NULL);
    virtual void character(int column, int row, int c) = 0;
    virtual int rows() = 0;
    virtual int columns() = 0;

    // functions that come for free, but can be overwritten
    virtual void cls();
    virtual void locate(int column, int row);
    virtual void foreground(int colour);
    virtual void background(int colour);
    // putc (from Stream)
    // printf (from Stream)

protected:

    virtual int _putc(int value);
    virtual int _getc();

    // character location
    short _column;
    short _row;

    // colours
    int _foreground;
    int _background;
};

#endif
