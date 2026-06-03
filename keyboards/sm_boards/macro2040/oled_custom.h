// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Minimal SSD1306 0.91" 128x32 OLED driver for the SM Boards Macro2040.
//
// We do NOT use QMK's built-in OLED feature because the Macro2040 needs both
// I2C peripherals on the RP2040:
//   - I2C0 (GP4/GP5)  : owned by QMK i2c_master for the AS5600 magnetic encoder
//   - I2C1 (GP18/GP19): owned by this driver for the OLED display
//
// QMK's OLED feature can only target the same bus as i2c_master, so a small
// dedicated driver living entirely on ChibiOS I2CD1 is the simplest solution.
// All public symbols are prefixed with `oled_` to avoid clashes with QMK.

#pragma once

#include <stdint.h>

// SSD1306 0.91" panel geometry (exposed so callers can position content).
#define OLED_DISP_WIDTH   128
#define OLED_DISP_HEIGHT  32
#define OLED_DISP_PAGES   4   // 32 pixels / 8 pixels-per-page

// Initialise the I2C1 bus and SSD1306 panel. Call once at boot
// (after any other code that might touch GP18/GP19).
void oled_init(void);

// Clear the in-RAM framebuffer (does NOT push to the panel).
void oled_clear(void);

// Append a single 5x7 character to the framebuffer at the current text
// cursor. '\n' moves to the start of the next text row.
void oled_write_char(char c);

// Append a NUL-terminated string of 5x7 characters to the framebuffer.
void oled_write(const char *str);

// Push the entire framebuffer to the panel via I2C1.
void oled_flush(void);

/* ---- Big font (5x7 stretched 2x to 10x14, drawn in a 12x14 cell) ---- */

// Render a NUL-terminated string in big font at pixel (x, page).
// `page` is the top page index (0..2 valid for the 32 px display because
// the glyph spans two pages = 14 px tall). The whole string must fit on
// screen; glyphs that don't fit are dropped.
void oled_write_big(uint8_t x, uint8_t page, const char *str);

// Big-font variant that accepts a SIGNED x offset and clips glyph columns
// that fall outside the visible 0..(OLED_DISP_WIDTH-1) range. Use this for
// horizontally-scrolling banners where x can be negative or off-screen.
void oled_write_big_scroll(int16_t x, uint8_t page, const char *str);

// Total pixel width of a big-font string (12 px per character cell).
uint16_t oled_big_text_width(const char *str);

/* ---- Primitive drawing (used by the on-board mini-games) ---- */

// Turn ON a single pixel at (x, y). No-op if the pixel is off-screen.
void oled_set_pixel(uint8_t x, uint8_t y);

// Fill a rectangle of size (w x h) starting at (x, y). Clipped to screen.
void oled_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

// Draw a horizontal 1-pixel-tall line of length w starting at (x, y).
void oled_hline(uint8_t x, uint8_t y, uint8_t w);
