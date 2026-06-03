// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Implementation of the SSD1306 0.91" 128x32 driver. See oled_custom.h for
// the rationale on why we don't use QMK's built-in OLED feature.

#include "oled_custom.h"
#include "config.h"
#include "quantum.h"
#include "hal.h"
#include <string.h>

// Layout constants — width/height/pages come from the public header.
// CHAR_W is the cell width of the small 5x7 font (5 px glyph + 1 px gap).
#define CHAR_W      6
#define TEXT_COLS   (OLED_DISP_WIDTH / CHAR_W)
#define TEXT_ROWS   OLED_DISP_PAGES

// I2C1 configuration. The OLED is the only device on this bus, so we own it
// exclusively (no need to coordinate with QMK's i2c_master driver).
static const I2CConfig oled_i2c_cfg = { .baudrate = 400000 };

// In-RAM framebuffer (1 byte per 8-pixel vertical column). Page 0 is the
// topmost 8 pixels, page 3 is the bottommost.
static uint8_t oled_fb[OLED_DISP_PAGES][OLED_DISP_WIDTH];

// Text cursor for the small font (managed by oled_write/oled_write_char).
static uint8_t oled_col = 0;
static uint8_t oled_row = 0;

// Compact 5x7 ASCII font (printable characters 0x20..0x7E).
// Each glyph is 5 columns × 8 rows; bit 0 of each byte is the top pixel.
static const uint8_t oled_font[][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, /* 0x20  ' ' */
    {0x00, 0x00, 0x5F, 0x00, 0x00}, /* 0x21  '!' */
    {0x00, 0x07, 0x00, 0x07, 0x00}, /* 0x22  '"' */
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, /* 0x23  '#' */
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, /* 0x24  '$' */
    {0x23, 0x13, 0x08, 0x64, 0x62}, /* 0x25  '%' */
    {0x36, 0x49, 0x55, 0x22, 0x50}, /* 0x26  '&' */
    {0x00, 0x05, 0x03, 0x00, 0x00}, /* 0x27  '\'' */
    {0x00, 0x1C, 0x22, 0x41, 0x00}, /* 0x28  '(' */
    {0x00, 0x41, 0x22, 0x1C, 0x00}, /* 0x29  ')' */
    {0x14, 0x08, 0x3E, 0x08, 0x14}, /* 0x2A  '*' */
    {0x08, 0x08, 0x3E, 0x08, 0x08}, /* 0x2B  '+' */
    {0x00, 0x50, 0x30, 0x00, 0x00}, /* 0x2C  ',' */
    {0x08, 0x08, 0x08, 0x08, 0x08}, /* 0x2D  '-' */
    {0x00, 0x60, 0x60, 0x00, 0x00}, /* 0x2E  '.' */
    {0x20, 0x10, 0x08, 0x04, 0x02}, /* 0x2F  '/' */
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, /* 0x30  '0' */
    {0x00, 0x42, 0x7F, 0x40, 0x00}, /* 0x31  '1' */
    {0x42, 0x61, 0x51, 0x49, 0x46}, /* 0x32  '2' */
    {0x21, 0x41, 0x45, 0x4B, 0x31}, /* 0x33  '3' */
    {0x18, 0x14, 0x12, 0x7F, 0x10}, /* 0x34  '4' */
    {0x27, 0x45, 0x45, 0x45, 0x39}, /* 0x35  '5' */
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, /* 0x36  '6' */
    {0x01, 0x71, 0x09, 0x05, 0x03}, /* 0x37  '7' */
    {0x36, 0x49, 0x49, 0x49, 0x36}, /* 0x38  '8' */
    {0x06, 0x49, 0x49, 0x29, 0x1E}, /* 0x39  '9' */
    {0x00, 0x36, 0x36, 0x00, 0x00}, /* 0x3A  ':' */
    {0x00, 0x56, 0x36, 0x00, 0x00}, /* 0x3B  ';' */
    {0x08, 0x14, 0x22, 0x41, 0x00}, /* 0x3C  '<' */
    {0x14, 0x14, 0x14, 0x14, 0x14}, /* 0x3D  '=' */
    {0x00, 0x41, 0x22, 0x14, 0x08}, /* 0x3E  '>' */
    {0x02, 0x01, 0x51, 0x09, 0x06}, /* 0x3F  '?' */
    {0x32, 0x49, 0x79, 0x41, 0x3E}, /* 0x40  '@' */
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, /* 0x41  'A' */
    {0x7F, 0x49, 0x49, 0x49, 0x36}, /* 0x42  'B' */
    {0x3E, 0x41, 0x41, 0x41, 0x22}, /* 0x43  'C' */
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, /* 0x44  'D' */
    {0x7F, 0x49, 0x49, 0x49, 0x41}, /* 0x45  'E' */
    {0x7F, 0x09, 0x09, 0x09, 0x01}, /* 0x46  'F' */
    {0x3E, 0x41, 0x49, 0x49, 0x7A}, /* 0x47  'G' */
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, /* 0x48  'H' */
    {0x00, 0x41, 0x7F, 0x41, 0x00}, /* 0x49  'I' */
    {0x20, 0x40, 0x41, 0x3F, 0x01}, /* 0x4A  'J' */
    {0x7F, 0x08, 0x14, 0x22, 0x41}, /* 0x4B  'K' */
    {0x7F, 0x40, 0x40, 0x40, 0x40}, /* 0x4C  'L' */
    {0x7F, 0x02, 0x04, 0x02, 0x7F}, /* 0x4D  'M' */
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, /* 0x4E  'N' */
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, /* 0x4F  'O' */
    {0x7F, 0x09, 0x09, 0x09, 0x06}, /* 0x50  'P' */
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, /* 0x51  'Q' */
    {0x7F, 0x09, 0x19, 0x29, 0x46}, /* 0x52  'R' */
    {0x46, 0x49, 0x49, 0x49, 0x31}, /* 0x53  'S' */
    {0x01, 0x01, 0x7F, 0x01, 0x01}, /* 0x54  'T' */
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, /* 0x55  'U' */
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, /* 0x56  'V' */
    {0x3F, 0x40, 0x38, 0x40, 0x3F}, /* 0x57  'W' */
    {0x63, 0x14, 0x08, 0x14, 0x63}, /* 0x58  'X' */
    {0x07, 0x08, 0x70, 0x08, 0x07}, /* 0x59  'Y' */
    {0x61, 0x51, 0x49, 0x45, 0x43}, /* 0x5A  'Z' */
    {0x00, 0x7F, 0x41, 0x41, 0x00}, /* 0x5B  '[' */
    {0x02, 0x04, 0x08, 0x10, 0x20}, /* 0x5C  '\\' */
    {0x00, 0x41, 0x41, 0x7F, 0x00}, /* 0x5D  ']' */
    {0x04, 0x02, 0x01, 0x02, 0x04}, /* 0x5E  '^' */
    {0x40, 0x40, 0x40, 0x40, 0x40}, /* 0x5F  '_' */
    {0x00, 0x01, 0x02, 0x04, 0x00}, /* 0x60  '`' */
    {0x20, 0x54, 0x54, 0x54, 0x78}, /* 0x61  'a' */
    {0x7F, 0x48, 0x44, 0x44, 0x38}, /* 0x62  'b' */
    {0x38, 0x44, 0x44, 0x44, 0x20}, /* 0x63  'c' */
    {0x38, 0x44, 0x44, 0x48, 0x7F}, /* 0x64  'd' */
    {0x38, 0x54, 0x54, 0x54, 0x18}, /* 0x65  'e' */
    {0x08, 0x7E, 0x09, 0x01, 0x02}, /* 0x66  'f' */
    {0x0C, 0x52, 0x52, 0x52, 0x3E}, /* 0x67  'g' */
    {0x7F, 0x08, 0x04, 0x04, 0x78}, /* 0x68  'h' */
    {0x00, 0x44, 0x7D, 0x40, 0x00}, /* 0x69  'i' */
    {0x20, 0x40, 0x44, 0x3D, 0x00}, /* 0x6A  'j' */
    {0x7F, 0x10, 0x28, 0x44, 0x00}, /* 0x6B  'k' */
    {0x00, 0x41, 0x7F, 0x40, 0x00}, /* 0x6C  'l' */
    {0x7C, 0x04, 0x18, 0x04, 0x78}, /* 0x6D  'm' */
    {0x7C, 0x08, 0x04, 0x04, 0x78}, /* 0x6E  'n' */
    {0x38, 0x44, 0x44, 0x44, 0x38}, /* 0x6F  'o' */
    {0x7C, 0x14, 0x14, 0x14, 0x08}, /* 0x70  'p' */
    {0x08, 0x14, 0x14, 0x18, 0x7C}, /* 0x71  'q' */
    {0x7C, 0x08, 0x04, 0x04, 0x08}, /* 0x72  'r' */
    {0x48, 0x54, 0x54, 0x54, 0x20}, /* 0x73  's' */
    {0x04, 0x3F, 0x44, 0x40, 0x20}, /* 0x74  't' */
    {0x3C, 0x40, 0x40, 0x40, 0x3C}, /* 0x75  'u' */
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, /* 0x76  'v' */
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, /* 0x77  'w' */
    {0x44, 0x28, 0x10, 0x28, 0x44}, /* 0x78  'x' */
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, /* 0x79  'y' */
    {0x44, 0x64, 0x54, 0x4C, 0x44}, /* 0x7A  'z' */
    {0x00, 0x08, 0x36, 0x41, 0x00}, /* 0x7B  '{' */
    {0x00, 0x00, 0x7F, 0x00, 0x00}, /* 0x7C  '|' */
    {0x00, 0x41, 0x36, 0x08, 0x00}, /* 0x7D  '}' */
    {0x10, 0x08, 0x08, 0x10, 0x08}, /* 0x7E  '~' */
};

// Send a single command byte to the SSD1306. Each command is preceded by
// the 0x00 control byte that tells the panel "the next byte is a command,
// not display data".
static void oled_cmd(uint8_t cmd) {
    uint8_t buf[2] = {0x00, cmd};
    i2cMasterTransmitTimeout(&I2CD1, OLED_I2C_ADDRESS, buf, 2, NULL, 0, TIME_MS2I(10));
}

// Bring up the I2C1 bus and run the SSD1306 initialisation sequence
// recommended by the datasheet for a 128x32 panel with internal charge pump.
void oled_init(void) {
    // Configure GP18/GP19 as alternate-function I2C with strong drive and
    // internal pullups so the bus settles quickly even without external R's.
    palSetLineMode(OLED_SDA_PIN, PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_SLEWFAST | PAL_RP_PAD_PUE | PAL_RP_PAD_DRIVE4);
    palSetLineMode(OLED_SCL_PIN, PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_SLEWFAST | PAL_RP_PAD_PUE | PAL_RP_PAD_DRIVE4);

    i2cStart(&I2CD1, &oled_i2c_cfg);
    wait_ms(50);  // give the panel time to power up before commands

    // SSD1306 init sequence (see datasheet section "Application example").
    oled_cmd(0xAE);                       // display OFF (so we can configure it)
    oled_cmd(0xD5); oled_cmd(0x80);       // clock divide ratio / oscillator freq
    oled_cmd(0xA8); oled_cmd(0x1F);       // multiplex ratio = 31 (= 32 rows)
    oled_cmd(0xD3); oled_cmd(0x00);       // display vertical offset = 0
    oled_cmd(0x40);                       // RAM start line = 0
    oled_cmd(0x8D); oled_cmd(0x14);       // enable internal charge pump
    oled_cmd(0x20); oled_cmd(0x00);       // horizontal addressing mode
    oled_cmd(0xA1);                       // segment remap (flip horizontally)
    oled_cmd(0xC8);                       // COM scan direction reversed (flip V)
    oled_cmd(0xDA); oled_cmd(0x02);       // COM pin hardware config for 128x32
    oled_cmd(0x81); oled_cmd(0x8F);       // contrast
    oled_cmd(0xD9); oled_cmd(0xF1);       // pre-charge period
    oled_cmd(0xDB); oled_cmd(0x40);       // VCOMH deselect level
    oled_cmd(0xA4);                       // display follows GDDRAM contents
    oled_cmd(0xA6);                       // normal display (not inverted)
    oled_cmd(0xAF);                       // display ON

    memset(oled_fb, 0, sizeof(oled_fb));
    oled_col = 0;
    oled_row = 0;
}

void oled_clear(void) {
    memset(oled_fb, 0, sizeof(oled_fb));
    oled_col = 0;
    oled_row = 0;
}

void oled_write_char(char c) {
    if (c == '\n') {
        oled_col = 0;
        oled_row++;
        return;
    }
    if (oled_col >= TEXT_COLS) {
        oled_col = 0;
        oled_row++;
    }
    if (oled_row >= TEXT_ROWS) return;
    if (c < 0x20 || c > 0x7E) c = ' ';

    const uint8_t *g = oled_font[(uint8_t)c - 0x20];
    uint8_t x = oled_col * CHAR_W;
    for (uint8_t i = 0; i < 5; i++) oled_fb[oled_row][x + i] = g[i];
    oled_fb[oled_row][x + 5] = 0x00;
    oled_col++;
}

void oled_write(const char *str) {
    while (*str) oled_write_char(*str++);
}

// Big font: render each 5x7 glyph at 2x scale into a 12 px wide × 14 px tall
// cell (10 px glyph + 2 px right gap). Output spans two pages vertically.
// `page` is the TOP page index (must satisfy page + 1 < OLED_DISP_PAGES).
void oled_write_big(uint8_t x, uint8_t page, const char *str) {
    if (page + 1 >= OLED_DISP_PAGES) return;

    while (*str) {
        char c = *str++;
        if (c < 0x20 || c > 0x7E) c = ' ';
        const uint8_t *g = oled_font[(uint8_t)c - 0x20];

        // If the next 12 px cell wouldn't fit, drop the rest of the string.
        if (x + 12 > OLED_DISP_WIDTH) break;

        // For each of the 5 source columns of the 5x7 glyph, expand the
        // 8-bit column to a 16-bit column where every source bit becomes
        // two bits — that's the vertical 2x stretch.
        for (uint8_t col = 0; col < 5; col++) {
            uint8_t  src     = g[col];
            uint16_t doubled = 0;
            for (uint8_t b = 0; b < 8; b++) {
                if (src & (1 << b)) {
                    doubled |= (3u << (b * 2));
                }
            }
            uint8_t lo = doubled & 0xFF;        // top page  (rows 0..7 of cell)
            uint8_t hi = (doubled >> 8) & 0xFF; // bottom page (rows 8..15)

            // Horizontal 2x stretch — write each column twice.
            for (uint8_t dup = 0; dup < 2; dup++) {
                uint8_t px = x + col * 2 + dup;
                if (px >= OLED_DISP_WIDTH) break;
                oled_fb[page][px]     |= lo;
                oled_fb[page + 1][px] |= hi;
            }
        }
        // 12 px cell width = 10 px glyph + 2 px gap
        x += 12;
    }
}

// Scrolling variant of oled_write_big. Accepts a SIGNED x offset so the
// caller can place text partially or fully off-screen for scroll animations.
// Glyphs entirely off-screen are skipped; on-screen glyph columns are clipped.
void oled_write_big_scroll(int16_t x, uint8_t page, const char *str) {
    if (page + 1 >= OLED_DISP_PAGES) return;

    while (*str) {
        char c = *str++;
        if (c < 0x20 || c > 0x7E) c = ' ';
        const uint8_t *g = oled_font[(uint8_t)c - 0x20];

        // Glyph entirely past the right edge → nothing left to draw, stop.
        if (x >= OLED_DISP_WIDTH) break;
        // Glyph entirely past the left edge → skip it but advance x.
        if (x + 12 <= 0) { x += 12; continue; }

        for (uint8_t col = 0; col < 5; col++) {
            uint8_t  src     = g[col];
            uint16_t doubled = 0;
            for (uint8_t b = 0; b < 8; b++) {
                if (src & (1 << b)) {
                    doubled |= (3u << (b * 2));
                }
            }
            uint8_t lo = doubled & 0xFF;
            uint8_t hi = (doubled >> 8) & 0xFF;

            for (uint8_t dup = 0; dup < 2; dup++) {
                int16_t px = x + col * 2 + dup;
                if (px < 0 || px >= OLED_DISP_WIDTH) continue;
                oled_fb[page][px]     |= lo;
                oled_fb[page + 1][px] |= hi;
            }
        }
        x += 12;
    }
}

// Total pixel width of `str` if rendered with the big font (12 px per cell).
uint16_t oled_big_text_width(const char *str) {
    uint16_t n = 0;
    while (*str++) n++;
    return n * 12;
}

/* ---- Primitive pixel / rectangle drawing ---- */

// Turn ON a single pixel. Off-screen coordinates are silently ignored.
void oled_set_pixel(uint8_t x, uint8_t y) {
    if (x >= OLED_DISP_WIDTH || y >= OLED_DISP_HEIGHT) return;
    oled_fb[y >> 3][x] |= (uint8_t)(1u << (y & 7));
}

// Fill a rectangle. Clipped to the visible area.
void oled_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    if (x >= OLED_DISP_WIDTH || y >= OLED_DISP_HEIGHT) return;
    if (x + w > OLED_DISP_WIDTH)  w = OLED_DISP_WIDTH  - x;
    if (y + h > OLED_DISP_HEIGHT) h = OLED_DISP_HEIGHT - y;
    for (uint8_t row = 0; row < h; row++) {
        uint8_t py = y + row;
        uint8_t *cell = &oled_fb[py >> 3][x];
        uint8_t bit = (uint8_t)(1u << (py & 7));
        for (uint8_t col = 0; col < w; col++) cell[col] |= bit;
    }
}

// Draw a 1-pixel-tall horizontal line.
void oled_hline(uint8_t x, uint8_t y, uint8_t w) {
    oled_fill_rect(x, y, w, 1);
}

// Push the entire framebuffer out over I2C in one column-addressed sweep.
// We set the column window to 0..127 and the page window to 0..3 (full
// 128x32 area), then stream the 4 pages back-to-back.
void oled_flush(void) {
    oled_cmd(0x21); oled_cmd(0); oled_cmd(OLED_DISP_WIDTH - 1);  // col window
    oled_cmd(0x22); oled_cmd(0); oled_cmd(OLED_DISP_PAGES - 1);  // page window

    // Each I2C transmit is preceded by 0x40 (= "the next bytes are display data").
    static uint8_t buf[OLED_DISP_WIDTH + 1];
    buf[0] = 0x40;
    for (uint8_t p = 0; p < OLED_DISP_PAGES; p++) {
        memcpy(buf + 1, oled_fb[p], OLED_DISP_WIDTH);
        i2cMasterTransmitTimeout(&I2CD1, OLED_I2C_ADDRESS, buf, sizeof(buf), NULL, 0, TIME_MS2I(50));
    }
}
