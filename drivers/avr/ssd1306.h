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

// Defines that can be overridden based on oled and font values
#ifndef OLED_DISPLAY_HEIGHT
#define OLED_DISPLAY_HEIGHT 32
#endif
#ifndef OLED_DISPLAY_WIDTH
#define OLED_DISPLAY_WIDTH 128
#endif


#ifndef OLED_FONT_H
#define OLED_FONT_H "glcdfont.c"
#endif
#ifndef OLED_FONT_START
#define OLED_FONT_START 0
#endif
#ifndef OLED_FONT_END
#define OLED_FONT_END 224
#endif
#ifndef OLED_FONT_WIDTH
#define OLED_FONT_WIDTH 6
#endif
#ifndef OLED_FONT_HEIGHT
#define OLED_FONT_HEIGHT 8
#endif

#define OLED_MAX_CHARS (OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH)
#define OLED_MAX_LINES (OLED_DISPLAY_HEIGHT / OLED_FONT_HEIGHT)

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

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void oled_write_P(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void oled_write_ln_P(const char *data, bool invert);

// Lets you know if the display is ready to use
bool oled_ready(void);

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


// compatibility defines
#ifdef SSD1306OLED

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

#define matrix_clear(matrix) oled_set_cursor(0, 0) // void return
#define matrix_write_char_inner(matrix, char_value) oled_write_char(char_value, false) // void return
#define matrix_write_char(matrix, char_value) oled_write_char(char_value, false) // void return
#define matrix_write(matrix, const_char_pointer) oled_write(const_char_pointer, false) // void return
#define matrix_write_ln(matrix, const_char_pointer) oled_write_ln(const_char_pointer, false) // void return
#define matrix_write_P(matrix, const_char_pointer) oled_write_P(const_char_pointer, false) // void return
#define matrix_write_ln_P(matrix, const_char_pointer) oled_write_ln_P(const_char_pointer, false) // void return
#define matrix_render(matrix) oled_render() // void return

#endif
