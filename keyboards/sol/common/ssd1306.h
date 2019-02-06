#pragma once

#include <stdint.h>
#include <stdbool.h>

#ifndef SSD1306_ADDRESS
#define SSD1306_ADDRESS 0x3C
#endif

#define OLED_DISPLAY_HEIGHT 32
#define OLED_DISPLAY_WIDTH 128

#define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8) * OLED_DISPLAY_WIDTH

#define OLED_FONT_START 0
#define OLED_FONT_END 224
#define OLED_FONT_WIDTH 6
#define OLED_FONT_HEIGHT 8

#define OLED_MAX_CHARS OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH
#define OLED_MAX_LINES OLED_DISPLAY_HEIGHT / OLED_FONT_HEIGHT

// Display buffer's is the same as the OLED memory layout
// this is so we don't end up with rounding errors with 
// parts of the display unusable or don't get cleared correctly
// and also allows for drawing & inverting
struct DisplayBuffer
{
  uint8_t display[OLED_MATRIX_SIZE];
  uint8_t *cursor;
  bool dirty;
};

// Initialize the oled display
void iota_gfx_init(bool flip180);

// Clears out a display buffer with 0, resets cursor to 0, and sets dirty to true
void iota_gfx_clear(void);

// Moves cursor to character position indicated by col and line, wraps if out of bounds
void iota_gfx_set_cursor(uint8_t col, uint8_t line);

// Renders the buffer to i2c oled and sets dirty to false
void iota_gfx_render(void);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void iota_gfx_write(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void iota_gfx_write_P(const char *data, bool invert);

bool iota_gfx_ready(void);