/* mbed TextDisplay Display Library Base Class
 * Copyright (c) 2007-2009 sford
 * Released under the MIT License: http://mbed.org/license/mit
 */

#include "TextDisplay.h"

TextDisplay::TextDisplay(const char *name) : Stream(name) {
    _row = 0;
    _column = 0;
}

int TextDisplay::_putc(int value) {
    if(value == '\n') {
        _column = 0;
        _row++;
        if(_row >= rows()) {
            _row = 0;
        }
    } else {
        character(_column, _row, value);
        _column++;
        if(_column >= columns()) {
            _column = 0;
            _row++;
            if(_row >= rows()) {
                _row = 0;
            }
        }
    }
    return value;
}

// crude cls implementation, should generally be overwritten in derived class
void TextDisplay::cls() {
    locate(0, 0);
    for(int i=0; i<columns()*rows(); i++) {
        putc(' ');
    }
}

void TextDisplay::locate(int column, int row) {
    _column = column;
    _row = row;
}

int TextDisplay::_getc() {
    return -1;
}

void TextDisplay::foreground(int colour) {
    _foreground = colour;
}

void TextDisplay::background(int colour) {
    _background = colour;
}
