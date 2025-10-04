/*
Copyright 2021

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

#include "spi_master.h"

#ifndef ST7565_DISPLAY_WIDTH
#    define ST7565_DISPLAY_WIDTH 128
#endif
#ifndef ST7565_DISPLAY_HEIGHT
#    define ST7565_DISPLAY_HEIGHT 32
#endif
#ifndef ST7565_MATRIX_SIZE
#    define ST7565_MATRIX_SIZE (ST7565_DISPLAY_HEIGHT / 8 * ST7565_DISPLAY_WIDTH) // 1024 (compile time mathed)
#endif
#ifndef ST7565_BLOCK_TYPE
#    define ST7565_BLOCK_TYPE uint16_t
#endif
#ifndef ST7565_BLOCK_COUNT
#    define ST7565_BLOCK_COUNT (sizeof(ST7565_BLOCK_TYPE) * 8) // 32 (compile time mathed)
#endif
#ifndef ST7565_BLOCK_SIZE
#    define ST7565_BLOCK_SIZE (ST7565_MATRIX_SIZE / ST7565_BLOCK_COUNT) // 32 (compile time mathed)
#endif

// the column address corresponding to the first column in the display hardware
#if !defined(ST7565_COLUMN_OFFSET)
#    define ST7565_COLUMN_OFFSET 0
#endif

// spi clock divisor
#if !defined(ST7565_SPI_CLK_DIVISOR)
#    define ST7565_SPI_CLK_DIVISOR 4
#endif

// Custom font file to use
#if !defined(ST7565_FONT_H)
#    define ST7565_FONT_H "glcdfont.c"
#endif
// unsigned char value of the first character in the font file
#if !defined(ST7565_FONT_START)
#    define ST7565_FONT_START 0
#endif
// unsigned char value of the last character in the font file
#if !defined(ST7565_FONT_END)
#    define ST7565_FONT_END 223
#endif
// Font render width
#if !defined(ST7565_FONT_WIDTH)
#    define ST7565_FONT_WIDTH 6
#endif
// Font render height
#if !defined(ST7565_FONT_HEIGHT)
#    define ST7565_FONT_HEIGHT 8
#endif
// Default contrast level
#if !defined(ST7565_CONTRAST)
#    define ST7565_CONTRAST 32
#endif

#if !defined(ST7565_TIMEOUT)
#    if defined(ST7565_DISABLE_TIMEOUT)
#        define ST7565_TIMEOUT 0
#    else
#        define ST7565_TIMEOUT 60000
#    endif
#endif

#if !defined(ST7565_UPDATE_INTERVAL) && defined(SPLIT_KEYBOARD)
#    define ST7565_UPDATE_INTERVAL 50
#endif

typedef struct __attribute__((__packed__)) {
    uint8_t *current_element;
    uint16_t remaining_element_count;
} display_buffer_reader_t;

// Rotation enum values are flags
typedef enum { DISPLAY_ROTATION_0, DISPLAY_ROTATION_180 } display_rotation_t;

// Initialize the display, rotating the rendered output based on the define passed in.
// Returns true if the display was initialized successfully
bool st7565_init(display_rotation_t rotation);

// Called at the start of st7565_init, weak function overridable by the user
// rotation - the value passed into st7565_init
// Return new display_rotation_t if you want to override default rotation
display_rotation_t st7565_init_user(display_rotation_t rotation);

// Clears the display buffer, resets cursor position to 0, and sets the buffer to dirty for rendering
void st7565_clear(void);

// Renders the dirty chunks of the buffer to display
void st7565_render(void);

// Moves cursor to character position indicated by column and line, wraps if out of bounds
// Max column denoted by 'st7565_max_chars()' and max lines by 'st7565_max_lines()' functions
void st7565_set_cursor(uint8_t col, uint8_t line);

// Advances the cursor to the next page, writing ' ' if true
// Wraps to the beginning when out of bounds
void st7565_advance_page(bool clearPageRemainder);

// Moves the cursor forward 1 character length
// Advance page if there is not enough room for the next character
// Wraps to the beginning when out of bounds
void st7565_advance_char(void);

// Writes a single character to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Main handler that writes character data to the display buffer
void st7565_write_char(const char data, bool invert);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void st7565_write(const char *data, bool invert);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
void st7565_write_ln(const char *data, bool invert);

// Pans the buffer to the right (or left by passing true) by moving contents of the buffer
// Useful for moving the screen in preparation for new drawing
void st7565_pan(bool left);

// Returns a pointer to the requested start index in the buffer plus remaining
// buffer length as struct
display_buffer_reader_t st7565_read_raw(uint16_t start_index);

// Writes a string to the buffer at current cursor position
void st7565_write_raw(const char *data, uint16_t size);

// Writes a single byte into the buffer at the specified index
void st7565_write_raw_byte(const char data, uint16_t index);

// Sets a specific pixel on or off
// Coordinates start at top-left and go right and down for positive x and y
void st7565_write_pixel(uint8_t x, uint8_t y, bool on);

#if defined(__AVR__)
// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Remapped to call 'void st7565_write(const char *data, bool invert);' on ARM
void st7565_write_P(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
// Remapped to call 'void st7565_write_ln(const char *data, bool invert);' on ARM
void st7565_write_ln_P(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
void st7565_write_raw_P(const char *data, uint16_t size);
#else
#    define st7565_write_P(data, invert) st7565_write(data, invert)
#    define st7565_write_ln_P(data, invert) st7565_write_ln(data, invert)
#    define st7565_write_raw_P(data, size) st7565_write_raw(data, size)
#endif // defined(__AVR__)

// Can be used to manually turn on the screen if it is off
// Returns true if the screen was on or turns on
bool st7565_on(void);

// Called when st7565_on() turns on the screen, weak function overridable by the user
// Not called if the screen is already on
void st7565_on_user(void);

// Can be used to manually turn off the screen if it is on
// Returns true if the screen was off or turns off
bool st7565_off(void);

// Called when st7565_off() turns off the screen, weak function overridable by the user
// Not called if the screen is already off
void st7565_off_user(void);

// Returns true if the screen is currently on, false if it is
// not
bool st7565_is_on(void);

// Basically it's st7565_render, but with timeout management and st7565_task_user calling!
void st7565_task(void);

// Called at the start of st7565_task, weak function overridable by the user
void st7565_task_user(void);

// Inverts the display
// Returns true if the screen was or is inverted
bool st7565_invert(bool invert);

// Returns the maximum number of characters that will fit on a line
uint8_t st7565_max_chars(void);

// Returns the maximum number of lines that will fit on the display
uint8_t st7565_max_lines(void);

void st7565_reset(void);

spi_status_t st7565_send_cmd(uint8_t cmd);

spi_status_t st7565_send_data(uint8_t *data, uint16_t length);
