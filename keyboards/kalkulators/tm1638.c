/* Copyright 2024 georgsnarbuts
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>
#include "tm1638.h"
#include "gpio.h"
#include "progmem.h"
#include "wait.h"
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "halconf.h"
#include "print.h"
#include <math.h>

#ifndef TM1638_CLK_PIN
#    error tm1638: no CLK pin defined!
#endif

#ifndef TM1638_STB_PIN
#    error tm1638: no STB pin defined!
#endif

#ifndef TM1638_DIO_PIN
#    error tm1638: no DIO pin defined!
#endif

static const unsigned char PROGMEM SevenSeg[] = {
    0x00, /* (space) */
    0x86, /* ! */
    0x22, /* " */
    0x7E, /* # */
    0x6D, /* $ */
    0xD2, /* % */
    0x46, /* & */
    0x20, /* ' */
    0x29, /* ( */
    0x0B, /* ) */
    0x21, /* * */
    0x70, /* + */
    0x10, /* , */
    0x40, /* - */
    0x80, /* . */
    0x52, /* / */
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
    0x09, /* : */
    0x0D, /* ; */
    0x61, /* < */
    0x48, /* = */
    0x43, /* > */
    0xD3, /* ? */
    0x5F, /* @ */
    0x77, /* A */
    0x7C, /* B */
    0x39, /* C */
    0x5E, /* D */
    0x79, /* E */
    0x71, /* F */
    0x3D, /* G */
    0x76, /* H */
    0x30, /* I */
    0x1E, /* J */
    0x75, /* K */
    0x38, /* L */
    0x15, /* M */
    0x37, /* N */
    0x3F, /* O */
    0x73, /* P */
    0x6B, /* Q */
    0x33, /* R */
    0x6D, /* S */
    0x78, /* T */
    0x3E, /* U */
    0x3E, /* V */
    0x2A, /* W */
    0x76, /* X */
    0x6E, /* Y */
    0x5B, /* Z */
    0x39, /* [ */
    0x64, /* \ */
    0x0F, /* ] */
    0x23, /* ^ */
    0x08, /* _ */
    0x02, /* ` */
    0x5F, /* a */
    0x7C, /* b */
    0x58, /* c */
    0x5E, /* d */
    0x7B, /* e */
    0x71, /* f */
    0x6F, /* g */
    0x74, /* h */
    0x10, /* i */
    0x0C, /* j */
    0x75, /* k */
    0x30, /* l */
    0x14, /* m */
    0x54, /* n */
    0x5C, /* o */
    0x73, /* p */
    0x67, /* q */
    0x50, /* r */
    0x6D, /* s */
    0x78, /* t */
    0x1C, /* u */
    0x1C, /* v */
    0x14, /* w */
    0x76, /* x */
    0x6E, /* y */
    0x5B, /* z */
    0x46, /* { */
    0x30, /* | */
    0x70, /* } */
    0x01, /* ~ */
};

const unsigned char *pFontSevenSegptr = SevenSeg; /**<  Pointer to the seven segment font data table */

void shiftOut(uint8_t val) {
    uint8_t i;

    for (i = 0; i < 8; i++) {
        writePin(TM1638_DIO_PIN, !!(val & (1 << i)));

        writePinHigh(TM1638_CLK_PIN);
        writePinLow(TM1638_CLK_PIN);
    }
}

void sendData(uint8_t data) {
    shiftOut(data);
}

void sendCommand(uint8_t value) {
    writePinLow(TM1638_STB_PIN);
    sendData(value);
    writePinHigh(TM1638_STB_PIN);
}

void reset() {
    sendCommand(TM_WRITE_INC);
    writePinLow(TM1638_STB_PIN);
    sendData(TM_SEG_ADR);

    for (uint8_t position = 0; position < 16; position++) {
        sendData(0x00);
    }
    writePinHigh(TM1638_STB_PIN);
}

void brightness(uint8_t brightness) {
    uint8_t value = 0;
    value         = TM_BRIGHT_ADR + (TM_BRIGHT_MASK & brightness);
    sendCommand(value);
}

void displayBegin() {
    sendCommand(TM_ACTIVATE);
    brightness(TM_DEFAULT_BRIGHTNESS);
    reset();
}

void display7Seg(uint8_t position, uint8_t value) {
    sendCommand(TM_WRITE_LOC);
    writePinLow(TM1638_STB_PIN);
    sendData(TM_SEG_ADR + (position << 1));
    sendData(value);
    writePinHigh(TM1638_STB_PIN);
}

void displayASCIIwDot(uint8_t position, uint8_t ascii) {
    // add 128 or 0x080 0b1000000 to turn on decimal point/dot in seven seg
    display7Seg(position, pgm_read_byte(pFontSevenSegptr + (ascii - TM_ASCII_OFFSET)) + TM_DOT_MASK_DEC);
}

void displayASCII(uint8_t position, uint8_t ascii) {
    display7Seg(position, pgm_read_byte(pFontSevenSegptr + (ascii - TM_ASCII_OFFSET)));
}

void displayText(const char *text) {
    char c, pos;
    pos = 0;
    while ((c = (*text++)) && pos < TM_DISPLAY_SIZE) {
        if (*text == '.' && c != '.') {
            displayASCIIwDot(pos++, c);

            text++;
        } else {
            displayASCII(pos++, c);
        }
    }
}

void displayTextRight(const char *text) {
    // Calculate the starting position to display the text on the far right
    uint8_t startPos = TM_DISPLAY_SIZE - strlen(text);

    // Ensure startPos is not negative
    startPos = startPos < 0 ? 0 : startPos;

    char c;
    while ((c = (*text++)) && startPos < TM_DISPLAY_SIZE) {
        if (*text == '.' && c != '.') {
            displayASCIIwDot((startPos++), c);
            text++;
        } else {
            displayASCII(startPos++, c);
        }
    }
}

void displayTextRightFloat(const char *text) {
    // Calculate the starting position to display the text on the far right
    // if there is "." in the text
    uint8_t startPos = TM_DISPLAY_SIZE - strlen(text) + 1;

    // Ensure startPos is not negative
    startPos = startPos < 0 ? 0 : startPos;

    char c;
    while ((c = (*text++)) && startPos < TM_DISPLAY_SIZE) {
        if (*text == '.' && c != '.') {
            displayASCIIwDot((startPos++), c);
            text++;
        } else {
            displayASCII(startPos++, c);
        }
    }
}

void displayIntNum(unsigned long number, bool leadingZeros) {
    char values[TM_DISPLAY_SIZE + 1];
    char TextDisplay[5] = "%";
    char TextLeft[3]    = "ld";
    char TextRight[4]   = "8ld";

    if (strcmp(TextAlignment, "TMAlignTextLeft") == 0) {
        strcat(TextDisplay, TextLeft); // %ld
    } else if (strcmp(TextAlignment, "TMAlignTextRight") == 0) {
        strcat(TextDisplay, TextRight); // %8ld
    }

    snprintf(values, TM_DISPLAY_SIZE + 1, leadingZeros ? "%08ld" : TextDisplay, number);
    displayText(values);
}

void displayHex(uint8_t position, uint8_t hex) {
    uint8_t offset = 0;
    hex            = hex % 16;
    if (hex <= 9) {
        display7Seg(position, pgm_read_byte(pFontSevenSegptr + (hex + TM_HEX_OFFSET)));
        // 16 is offset in reduced ASCII table for number 0
    } else if ((hex >= 10) && (hex <= 15)) {
        // Calculate offset in reduced ASCII table for AbCDeF
        switch (hex) {
            case 10:
                offset = 'A';
                break;
            case 11:
                offset = 'b';
                break;
            case 12:
                offset = 'C';
                break;
            case 13:
                offset = 'd';
                break;
            case 14:
                offset = 'E';
                break;
            case 15:
                offset = 'F';
                break;
        }
        display7Seg(position, pgm_read_byte(pFontSevenSegptr + (offset - TM_ASCII_OFFSET)));
    }
}

void DisplayDecNumNibble(uint16_t numberUpper, uint16_t numberLower, bool leadingZeros) {
    char valuesUpper[TM_DISPLAY_SIZE + 1];
    char valuesLower[TM_DISPLAY_SIZE / 2 + 1];
    char TextDisplay[5] = "%";
    char TextLeft[4]    = "-4d";
    char TextRight[3]   = "4d";

    if (strcmp(TextAlignment, "TMAlignTextLeft") == 0) {
        strcat(TextDisplay, TextLeft); // %-4d
    } else if (strcmp(TextAlignment, "TMAlignTextRight") == 0) {
        strcat(TextDisplay, TextRight); // %4d
    }

    snprintf(valuesUpper, TM_DISPLAY_SIZE / 2 + 1, leadingZeros ? "%04d" : TextDisplay, numberUpper);
    snprintf(valuesLower, TM_DISPLAY_SIZE / 2 + 1, leadingZeros ? "%04d" : TextDisplay, numberLower);

    strcat(valuesUpper, valuesLower);
    displayText(valuesUpper);
};