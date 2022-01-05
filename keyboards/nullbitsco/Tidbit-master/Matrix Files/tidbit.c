// Uses the HT16K33_GFX.h library that is part of the TIDBIT source tree
// Find it here: https://github.com/nullbitsco/tidbit/blob/master/HT16K33_GFX.h
// This example is set up for a 16x8 module: https://www.adafruit.com/product/2038
// It uses the fonts defined in "font.h", which are attached to this gist.
#include QMK_KEYBOARD_H
#include "HT16K33_GFX.h"
#include <stdlib.h>

// My LED matrix has address 0x71, but the default is 0x70. FYI.
#define DISP_ADDR 0x71

HT16K33 *disp;
uint16_t delay_timer;
uint8_t c = 32;

// Clear one single pixel.
// Note: only writes to the display buffer.
// Call HT16K33_refresh() to write to the display.
void clearPixel(HT16K33 *disp, uint8_t x, uint8_t y) {
    if ((y < 0) || (y >= 8)) return;
    if ((x < 0) || (x >= 16)) return;

    disp->buf[y] &= ~(1 << x);
}

// Draw one single pixel.
// Note: only writes to the display buffer.
// Call HT16K33_refresh() to write to the display.
void drawPixel(HT16K33 *disp, uint8_t x, uint8_t y) {
    if ((y < 0) || (y >= 8)) return;
    if ((x < 0) || (x >= 16)) return;

    disp->buf[y] |= 1 << x;
}

// Draws a vertically in the y direction using one font byte.
void line2px(HT16K33 *disp, uint8_t x, uint8_t bmp) {
    for (uint8_t b=0; b<8; b++) {
        uint8_t line = (bmp & (1 << b)) >> b;
        uprintf("0x%02X %d:%d\n", bmp, b, line);
        if (line) {
            drawPixel(disp, x, b);
        } else {
            clearPixel(disp, x, b);
        }
    }
}

// Draw a single ASCII char at the specified x offset.
//todo: need vertical offset for centering
//todo: add flip, rotate
//todo: needs sanity checks for newlines, etc
void drawChar(HT16K33 *disp, uint8_t offset, uint8_t c) {
    for (int i=0; i<FONT_WIDTH; i++) {
        uint16_t idx = ((c - FONT_OFFSET) * FONT_WIDTH) + i;
        uint8_t line = pgm_read_byte_near(font + idx);
        uprintf("%c(%d)/%d: font[%d]=0x%02X\n", c, c, i, idx, line);
        line2px(disp, i+offset, line);
    }
}

void matrix_init_kb(void) {
    matrix_init_user();
    disp = newHT16K33(8, DISP_ADDR);
    delay_timer = timer_read();
}

void matrix_scan_kb(void) {
    matrix_scan_user();
    if (timer_elapsed(delay_timer) > 1000) {
        delay_timer = timer_read();
        HT16K33_clear(disp);

        // Testing with a single char
        // drawChar(disp, 0, c);
        // c += 1;
        
        #ifdef USE_FONT_5x7
        // If using 5x7 font, two chars fit on the display.
        drawChar(disp, 0, c);
        drawChar(disp, FONT_WIDTH+1, c+1);
        c += 2;
        #endif

        #ifdef USE_FONT_3x5
        // If using 3x5 font, four chars fit on the display!
        drawChar(disp, 0, c);
        drawChar(disp, FONT_WIDTH+1, c+1);
        drawChar(disp, 2*(FONT_WIDTH+1), c+2);
        drawChar(disp, 3*(FONT_WIDTH+1), c+3);
        c += 4;
        #endif

        HT16K33_refresh(disp);
        
        if (c > 127) {
            c = 32;
        }
    }
}