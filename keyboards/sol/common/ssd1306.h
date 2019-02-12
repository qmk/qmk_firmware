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

#define OLED_DISPLAY_HEIGHT 32
#define OLED_DISPLAY_WIDTH 128

#define OLED_FONT_START 0
#define OLED_FONT_END 224
#define OLED_FONT_WIDTH 6
#define OLED_FONT_HEIGHT 8

#define OLED_MAX_CHARS (OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH)
#define OLED_MAX_LINES (OLED_DISPLAY_HEIGHT / OLED_FONT_HEIGHT)

// Initialize the oled display
bool oled_init(bool flip180);

// Clears out a display buffer with 0, resets cursor to 0, and sets dirty to true
void oled_clear(void);

// Moves cursor to character position indicated by col and line, wraps if out of bounds
void oled_set_cursor(uint8_t col, uint8_t line);

// Renders the buffer to i2c oled and sets dirty to false
void oled_render(void);

// Writes a single character to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Main handler that writes character data to the display buffer
void oled_write_char(const char data, bool invert);

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void oled_write(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
void oled_write_P(const char *data, bool invert);

// Lets you know if the display is ready to use
bool oled_ready(void);

// Can be used to manually turn on the screen if it is off
bool oled_on(void);

// Can be used to manually turn off the screen if it is on
bool oled_off(void);


// compatibility defines
#ifdef SSD1306OLED

#define iota_gfx_init(v) oled_init(v) // bool return, v is typical void, converts to bool
#define iota_gfx_task(v) oled_render() // void return
#define iota_gfx_off(v) // bool return
#define iota_gfx_on(v) // bool return
#define iota_gfx_flush(v) oled_render() // void return
#define iota_gfx_write_char(char_value) oled_write_char(char_value, false) // void return
#define iota_gfx_write(const_char_pointer) oled_write(const_char_pointer, false) // void return
#define iota_gfx_write_P(const_char_pointer) oled_write_P(const_char_pointer, false) // void return
#define iota_gfx_clear_screen(v) oled_clear() // void return

#endif