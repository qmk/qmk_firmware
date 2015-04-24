/* mbed TextLCD Library Base Class
 * Copyright (c) 2007-2009 sford
 * Released under the MIT License: http://mbed.org/license/mit
 */
#include "TextDisplay.h"

#ifndef MBED_TEXTLCD_H
#define MBED_TEXTLCD_H

class TextLCD : public TextDisplay {
public:

    TextLCD(PinName rs, PinName rw, PinName e, PinName d0, PinName d1, PinName d2, PinName d3, const char *name = NULL);
    virtual void character(int column, int row, int c);
    virtual int rows();
    virtual int columns();

    // locate, cls, putc, printf come from derived class

protected:

    void writeByte(int value);
    void writeCommand(int command);
    void writeData(int data);

    DigitalOut _rw, _rs, _e;
    BusOut _d;
};

#endif
