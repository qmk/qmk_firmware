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

// an enumeration of the chips this driver supports
#define OLED_IC_SSD1306 0
#define OLED_IC_SH1106 1

#if defined(OLED_DISPLAY_CUSTOM)
// Expected user to implement the necessary defines
#elif defined(OLED_DISPLAY_128X64)
// Double height 128x64
#    ifndef OLED_DISPLAY_WIDTH
#        define OLED_DISPLAY_WIDTH 128
#    endif
#    ifndef OLED_DISPLAY_HEIGHT
#        define OLED_DISPLAY_HEIGHT 64
#    endif
#    ifndef OLED_MATRIX_SIZE
#        define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)  // 1024 (compile time mathed)
#    endif
#    ifndef OLED_BLOCK_TYPE
#        define OLED_BLOCK_TYPE uint16_t
#    endif
#    ifndef OLED_BLOCK_COUNT
#        define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)  // 32 (compile time mathed)
#    endif
#    ifndef OLED_BLOCK_SIZE
#        define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)  // 32 (compile time mathed)
#    endif
#    ifndef OLED_COM_PINS
#        define OLED_COM_PINS COM_PINS_ALT
#    endif

// For 90 degree rotation, we map our internal matrix to oled matrix using fixed arrays
// The OLED writes to it's memory horizontally, starting top left, but our memory starts bottom left in this mode
#    ifndef OLED_SOURCE_MAP
#        define OLED_SOURCE_MAP \
            { 0, 8, 16, 24, 32, 40, 48, 56 }
#    endif
#    ifndef OLED_TARGET_MAP
#        define OLED_TARGET_MAP \
            { 56, 48, 40, 32, 24, 16, 8, 0 }
#    endif
// If OLED_BLOCK_TYPE is uint32_t, these tables would look like:
// #define OLED_SOURCE_MAP { 32, 40, 48, 56 }
// #define OLED_TARGET_MAP { 24, 16, 8, 0 }
// If OLED_BLOCK_TYPE is uint16_t, these tables would look like:
// #define OLED_SOURCE_MAP { 0, 8, 16, 24, 32, 40, 48, 56 }
// #define OLED_TARGET_MAP { 56, 48, 40, 32, 24, 16, 8, 0 }
// If OLED_BLOCK_TYPE is uint8_t, these tables would look like:
// #define OLED_SOURCE_MAP { 0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120 }
// #define OLED_TARGET_MAP { 56, 120, 48, 112, 40, 104, 32, 96, 24, 88, 16, 80, 8, 72, 0, 64 }
#else  // defined(OLED_DISPLAY_128X64)
// Default 128x32
#    ifndef OLED_DISPLAY_WIDTH
#        define OLED_DISPLAY_WIDTH 128
#    endif
#    ifndef OLED_DISPLAY_HEIGHT
#        define OLED_DISPLAY_HEIGHT 32
#    endif
#    ifndef OLED_MATRIX_SIZE
#        define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)  // 512 (compile time mathed)
#    endif
#    ifndef OLED_BLOCK_TYPE
#        define OLED_BLOCK_TYPE uint16_t  // Type to use for segmenting the oled display for smart rendering, use unsigned types only
#    endif
#    ifndef OLED_BLOCK_COUNT
#        define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)  // 16 (compile time mathed)
#    endif
#    ifndef OLED_BLOCK_SIZE
#        define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)  // 32 (compile time mathed)
#    endif
#    ifndef OLED_COM_PINS
#        define OLED_COM_PINS COM_PINS_SEQ
#    endif

// For 90 degree rotation, we map our internal matrix to oled matrix using fixed arrays
// The OLED writes to it's memory horizontally, starting top left, but our memory starts bottom left in this mode
#    ifndef OLED_SOURCE_MAP
#        define OLED_SOURCE_MAP \
            { 0, 8, 16, 24 }
#    endif
#    ifndef OLED_TARGET_MAP
#        define OLED_TARGET_MAP \
            { 24, 16, 8, 0 }
#    endif
// If OLED_BLOCK_TYPE is uint8_t, these tables would look like:
// #define OLED_SOURCE_MAP { 0, 8, 16, 24, 32, 40, 48, 56 }
// #define OLED_TARGET_MAP { 48, 32, 16, 0, 56, 40, 24, 8 }
#endif  // defined(OLED_DISPLAY_CUSTOM)

#if !defined(OLED_IC)
#    define OLED_IC OLED_IC_SSD1306
#endif

// the column address corresponding to the first column in the display hardware
#if !defined(OLED_COLUMN_OFFSET)
#    define OLED_COLUMN_OFFSET 0
#endif

// Address to use for the i2c oled communication
#if !defined(OLED_DISPLAY_ADDRESS)
#    define OLED_DISPLAY_ADDRESS 0x3C
#endif

// Custom font file to use
#if !defined(OLED_FONT_H)
#    define OLED_FONT_H "glcdfont.c"
#endif
// unsigned char value of the first character in the font file
#if !defined(OLED_FONT_START)
#    define OLED_FONT_START 0
#endif
// unsigned char value of the last character in the font file
#if !defined(OLED_FONT_END)
#    define OLED_FONT_END 223
#endif
// Font render width
#if !defined(OLED_FONT_WIDTH)
#    define OLED_FONT_WIDTH 6
#endif
// Font render height
#if !defined(OLED_FONT_HEIGHT)
#    define OLED_FONT_HEIGHT 8
#endif

#if !defined(OLED_TIMEOUT)
#    if defined(OLED_DISABLE_TIMEOUT)
#        define OLED_TIMEOUT 0
#    else
#        define OLED_TIMEOUT 60000
#    endif
#endif

// OLED Rotation enum values are flags
typedef enum {
    OLED_ROTATION_0   = 0,
    OLED_ROTATION_90  = 1,
    OLED_ROTATION_180 = 2,
    OLED_ROTATION_270 = 3,  // OLED_ROTATION_90 | OLED_ROTATION_180
} oled_rotation_t;

// Initialize the oled display, rotating the rendered output based on the define passed in.
// Returns true if the OLED was initialized successfully
bool oled_init(oled_rotation_t rotation);

// Called at the start of oled_init, weak function overridable by the user
// rotation - the value passed into oled_init
// Return new oled_rotation_t if you want to override default rotation
oled_rotation_t oled_init_user(oled_rotation_t rotation);

// Clears the display buffer, resets cursor position to 0, and sets the buffer to dirty for rendering
void oled_clear(void);

// Renders the dirty chunks of the buffer to oled display
void oled_render(void);

// Moves cursor to character position indicated by column and line, wraps if out of bounds
// Max column denoted by 'oled_max_chars()' and max lines by 'oled_max_lines()' functions
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
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
void oled_write_ln(const char *data, bool invert);

// Pans the buffer to the right (or left by passing true) by moving contents of the buffer
void oled_pan(bool left);

void oled_write_raw(const char *data, uint16_t size);
void oled_write_raw_byte(const char data, uint16_t index);

#if defined(__AVR__)
// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Remapped to call 'void oled_write(const char *data, bool invert);' on ARM
void oled_write_P(const char *data, bool invert);

// Writes a PROGMEM string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
// Remapped to call 'void oled_write_ln(const char *data, bool invert);' on ARM
void oled_write_ln_P(const char *data, bool invert);

void oled_write_raw_P(const char *data, uint16_t size);
#else
// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
#    define oled_write_P(data, invert) oled_write(data, invert)

// Writes a string to the buffer at current cursor position
// Advances the cursor while writing, inverts the pixels if true
// Advances the cursor to the next page, wiring ' ' to the remainder of the current page
#    define oled_write_ln_P(data, invert) oled_write(data, invert)

#    define oled_write_raw_P(data, size) oled_write_raw(data, size)
#endif  // defined(__AVR__)

// Can be used to manually turn on the screen if it is off
// Returns true if the screen was on or turns on
bool oled_on(void);

// Can be used to manually turn off the screen if it is on
// Returns true if the screen was off or turns off
bool oled_off(void);

// Basically it's oled_render, but with timeout management and oled_task_user calling!
void oled_task(void);

// Called at the start of oled_task, weak function overridable by the user
void oled_task_user(void);

// Set the specific 8 lines rows of the screen to scroll.
// 0 is the default for start, and 7 for end, which is the entire
// height of the screen.  For 128x32 screens, rows 4-7 are not used.
void oled_scroll_set_area(uint8_t start_line, uint8_t end_line);

// Sets scroll speed, 0-7, fastest to slowest. Default is three.
// Does not take effect until scrolling is either started or restarted
// the ssd1306 supports 8 speeds with the delay
// listed below betwen each frame of the scrolling effect
// 0=2, 1=3, 2=4, 3=5, 4=25, 5=64, 6=128, 7=256
void oled_scroll_set_speed(uint8_t speed);

// Scrolls the entire display right
// Returns true if the screen was scrolling or starts scrolling
// NOTE: display contents cannot be changed while scrolling
bool oled_scroll_right(void);

// Scrolls the entire display left
// Returns true if the screen was scrolling or starts scrolling
// NOTE: display contents cannot be changed while scrolling
bool oled_scroll_left(void);

// Turns off display scrolling
// Returns true if the screen was not scrolling or stops scrolling
bool oled_scroll_off(void);

// Returns the maximum number of characters that will fit on a line
uint8_t oled_max_chars(void);

// Returns the maximum number of lines that will fit on the oled
uint8_t oled_max_lines(void);
