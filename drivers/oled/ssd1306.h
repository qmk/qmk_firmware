/*
Copyright 2019 Ryan Caltabiano <https://github.com/XScorpion2>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include <stdint.h>
#include <stdbool.h>


#if defined(OLED_DISPLAY_CUSTOM)
  // Expected user to implement the necessary defines
#elif defined(OLED_DISPLAY_128X64)
  // Double height 128x64
  #define OLED_DISPLAY_WIDTH 128
  #define OLED_DISPLAY_HEIGHT 64
  #define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH) // 1024 (compile time mathed)
  #define OLED_BLOCK_TYPE uint16_t
  #define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8) // 16 (compile time mathed)
  #define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT) // 64 (compile time mathed)

  #ifdef OLED_ROTATE90
    // For 90 degree rotation, we map our internal matrix to oled matrix using fixed arrays
    // The OLED writes to it's memory horizontally, starting top left, but our memory starts bottom left in this mode
    #define OLED_SOURCE_MAP { 0, 8, 16, 24, 32, 40, 48, 56 }
    #define OLED_TARGET_MAP { 56, 48, 40, 32, 24, 16, 8, 0 }
    // If OLED_BLOCK_TYPE is uint8_t, these tables would look like:
    // #define OLED_SOURCE_MAP { 0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120 }
    // #define OLED_TARGET_MAP { 56, 120, 48, 112, 40, 104, 32, 96, 24, 88, 16, 80, 8, 72, 0, 64 }
  #endif
#else
  // Default 128x32
  #define OLED_DISPLAY_WIDTH 128
  #define OLED_DISPLAY_HEIGHT 32
  #define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH) // 512 (compile time mathed)
  #define OLED_BLOCK_TYPE uint8_t // Type to use for segmenting the oled display for smart rendering, use unsigned types only
  #define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8) // 8 (compile time mathed)
  #define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT) // 128 (compile time mathed)

  #ifdef OLED_ROTATE90
    // For 90 degree rotation, we map our internal matrix to oled matrix using fixed arrays
    // The OLED writes to it's memory horizontally, starting top left, but our memory starts bottom left in this mode
    #define OLED_SOURCE_MAP { 0, 8, 16, 24, 32, 40, 48, 56 }
    #define OLED_TARGET_MAP { 48, 32, 16, 0, 56, 40, 24, 8 }
  #endif
#endif

// Address to use for tthe i2d oled communication
#ifndef SSD1306_ADDRESS
#define SSD1306_ADDRESS 0x3C
#endif

// Custom font file to use
#ifndef OLED_FONT_H
#define OLED_FONT_H "glcdfont.c"
#endif
// unsigned char value of the first character in the font file
#ifndef OLED_FONT_START
#define OLED_FONT_START 0
#endif
// unsigned char value of the last character in the font file
#ifndef OLED_FONT_END
#define OLED_FONT_END 224
#endif
// Font render width
#ifndef OLED_FONT_WIDTH
#define OLED_FONT_WIDTH 6
#endif
// Font render height
#ifndef OLED_FONT_HEIGHT
#define OLED_FONT_HEIGHT 8
#endif

#ifndef OLED_ROTATE90
#define OLED_MAX_CHARS (OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH)
#define OLED_MAX_LINES (OLED_DISPLAY_HEIGHT / OLED_FONT_HEIGHT)
#else
#define OLED_MAX_CHARS (OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH)
#define OLED_MAX_LINES (OLED_DISPLAY_WIDTH / OLED_FONT_HEIGHT)
#endif

// Initialize the oled display
bool oled_init(bool flip180);

// Clears out a display buffer with 0, resets cursor to 0, and sets dirty to true
void oled_clear(void);

// Renders the buffer to i2c oled and sets dirty to false
void oled_render(void);

// Moves cursor to character position indicated by col and line, wraps if out of bounds
void oled_set_cursor(uint8_t col, uint8_t line);

// Advances the cursor to the next page, writing ' ' if true
// Wraps to the begining when out of bounds
void oled_advance_page(bool clearPageRemainder);

// Moves the cursor forward 1 character length
// Advance page if there is not enough room for the next character
// Wraps to the begining when out of bounds
void oled_advance_char(void);

// Writes a single character to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Main handler that writes character data to the display buffer
void oled_write_char(const char data, bool invert);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void oled_write(const char *data, bool invert);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void oled_write_ln(const char *data, bool invert);

#ifdef __AVR__
// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void oled_write_P(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void oled_write_ln_P(const char *data, bool invert);
#endif //__AVR__

// Can be used to manually turn on the screen if it is off
bool oled_on(void);

// Can be used to manually turn off the screen if it is on
bool oled_off(void);

// Basically it's oled_render, but with timeout management and user task calling!
void oled_task(void);

// Called at the start of oled_task, weak function
void oled_task_user(void);

// Scrolls the entire display right
// Note, display contents cannot be changed while scrolling
bool oled_scroll_right(void);

// Scrolls the entire display left
// Note, display contents cannot be changed while scrolling
bool oled_scroll_left(void);

// Turns off display scrolling
bool oled_scroll_off(void);


// compatibility defines, ARM never had these, so don't include them
#if !defined(IOTA_COMPATIBILITY_OFF) && defined(__AVR__)

struct CharacterMatrix {
  uint8_t display[0];
  bool dirty;
};

struct CharacterMatrix display;

#define iota_gfx_init(v) oled_init(v) // bool return, v is typical void, converts to bool
#define iota_gfx_off(v) oled_off() // bool return
#define iota_gfx_on(v) oled_on() // bool return
#define iota_gfx_flush(v) oled_render() // void return
#define iota_gfx_write_char(char_value) oled_write_char(char_value, false) // void return
#define iota_gfx_write(const_char_pointer) oled_write(const_char_pointer, false) // void return
#define iota_gfx_write_P(const_char_pointer) oled_write_P(const_char_pointer, false) // void return
#define iota_gfx_clear_screen(v) oled_clear() // void return
#define iota_gfx_task(v) oled_task() // void return

void iota_gfx_task_user(void); // void return

#define matrix_clear(matrix) // void return
#define matrix_write_char_inner(matrix, char_value) oled_write_char(char_value, false) // void return
#define matrix_write_char(matrix, char_value) oled_write_char(char_value, false) // void return
#define matrix_write(matrix, const_char_pointer) oled_write(const_char_pointer, false) // void return
#define matrix_write_ln(matrix, const_char_pointer) oled_write_ln(const_char_pointer, false) // void return
#define matrix_write_P(matrix, const_char_pointer) oled_write_P(const_char_pointer, false) // void return
#define matrix_write_ln_P(matrix, const_char_pointer) oled_write_ln_P(const_char_pointer, false) // void return
#define matrix_render(matrix) oled_render() // void return

#endif // !defined(IOTA_COMPATIBILITY_OFF) && defined(__AVR__)
