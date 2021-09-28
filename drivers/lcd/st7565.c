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

#include "st7565.h"

#include <string.h>

#include "keyboard.h"
#include "progmem.h"
#include "timer.h"
#include "wait.h"

#include ST7565_FONT_H

// Fundamental Commands
#define CONTRAST 0x81
#define DISPLAY_ALL_ON 0xA5
#define DISPLAY_ALL_ON_RESUME 0xA4
#define NORMAL_DISPLAY 0xA6
#define INVERT_DISPLAY 0xA7
#define DISPLAY_ON 0xAF
#define DISPLAY_OFF 0xAE
#define NOP 0xE3

// Addressing Setting Commands
#define PAM_SETCOLUMN_LSB 0x00
#define PAM_SETCOLUMN_MSB 0x10
#define PAM_PAGE_ADDR 0xB0  // 0xb0 -- 0xb7

// Hardware Configuration Commands
#define DISPLAY_START_LINE 0x40
#define SEGMENT_REMAP 0xA0
#define SEGMENT_REMAP_INV 0xA1
#define COM_SCAN_INC 0xC0
#define COM_SCAN_DEC 0xC8
#define LCD_BIAS_7 0xA3
#define LCD_BIAS_9 0xA2
#define RESISTOR_RATIO 0x20
#define POWER_CONTROL 0x28

// Misc defines
#ifndef ST7565_BLOCK_COUNT
#    define ST7565_BLOCK_COUNT (sizeof(ST7565_BLOCK_TYPE) * 8)
#endif
#ifndef ST7565_BLOCK_SIZE
#    define ST7565_BLOCK_SIZE (ST7565_MATRIX_SIZE / ST7565_BLOCK_COUNT)
#endif

#define ST7565_ALL_BLOCKS_MASK (((((ST7565_BLOCK_TYPE)1 << (ST7565_BLOCK_COUNT - 1)) - 1) << 1) | 1)

#define HAS_FLAGS(bits, flags) ((bits & flags) == flags)

// Display buffer's is the same as the display memory layout
// this is so we don't end up with rounding errors with
// parts of the display unusable or don't get cleared correctly
// and also allows for drawing & inverting
uint8_t            st7565_buffer[ST7565_MATRIX_SIZE];
uint8_t *          st7565_cursor;
ST7565_BLOCK_TYPE  st7565_dirty       = 0;
bool               st7565_initialized = false;
bool               st7565_active      = false;
bool               st7565_inverted    = false;
display_rotation_t st7565_rotation    = DISPLAY_ROTATION_0;
#if ST7565_TIMEOUT > 0
uint32_t st7565_timeout;
#endif
#if ST7565_UPDATE_INTERVAL > 0
uint16_t st7565_update_timeout;
#endif

// Flips the rendering bits for a character at the current cursor position
static void InvertCharacter(uint8_t *cursor) {
    const uint8_t *end = cursor + ST7565_FONT_WIDTH;
    while (cursor < end) {
        *cursor = ~(*cursor);
        cursor++;
    }
}

bool st7565_init(display_rotation_t rotation) {
    setPinOutput(ST7565_A0_PIN);
    writePinHigh(ST7565_A0_PIN);
    setPinOutput(ST7565_RST_PIN);
    writePinHigh(ST7565_RST_PIN);

    st7565_rotation = st7565_init_user(rotation);

    spi_init();
    spi_start(ST7565_SS_PIN, false, 0, ST7565_SPI_CLK_DIVISOR);

    st7565_reset();

    st7565_send_cmd(LCD_BIAS_7);
    if (!HAS_FLAGS(st7565_rotation, DISPLAY_ROTATION_180)) {
        st7565_send_cmd(SEGMENT_REMAP);
        st7565_send_cmd(COM_SCAN_DEC);
    } else {
        st7565_send_cmd(SEGMENT_REMAP_INV);
        st7565_send_cmd(COM_SCAN_INC);
    }
    st7565_send_cmd(DISPLAY_START_LINE | 0x00);
    st7565_send_cmd(CONTRAST);
    st7565_send_cmd(ST7565_CONTRAST);
    st7565_send_cmd(RESISTOR_RATIO | 0x01);
    st7565_send_cmd(POWER_CONTROL | 0x04);
    wait_ms(50);
    st7565_send_cmd(POWER_CONTROL | 0x06);
    wait_ms(50);
    st7565_send_cmd(POWER_CONTROL | 0x07);
    wait_ms(10);
    st7565_send_cmd(DISPLAY_ON);
    st7565_send_cmd(DISPLAY_ALL_ON_RESUME);
    st7565_send_cmd(NORMAL_DISPLAY);

    spi_stop();

#if ST7565_TIMEOUT > 0
    st7565_timeout = timer_read32() + ST7565_TIMEOUT;
#endif

    st7565_clear();
    st7565_initialized = true;
    st7565_active      = true;
    return true;
}

__attribute__((weak)) display_rotation_t st7565_init_user(display_rotation_t rotation) { return rotation; }

void st7565_clear(void) {
    memset(st7565_buffer, 0, sizeof(st7565_buffer));
    st7565_cursor = &st7565_buffer[0];
    st7565_dirty  = ST7565_ALL_BLOCKS_MASK;
}

uint8_t crot(uint8_t a, int8_t n) {
    const uint8_t mask = 0x7;
    n &= mask;
    return a << n | a >> (-n & mask);
}

void st7565_render(void) {
    if (!st7565_initialized) {
        return;
    }

    // Do we have work to do?
    st7565_dirty &= ST7565_ALL_BLOCKS_MASK;
    if (!st7565_dirty) {
        return;
    }

    // Find first dirty block
    uint8_t update_start = 0;
    while (!(st7565_dirty & ((ST7565_BLOCK_TYPE)1 << update_start))) {
        ++update_start;
    }

    // Calculate commands to set memory addressing bounds.
    uint8_t start_page   = ST7565_BLOCK_SIZE * update_start / ST7565_DISPLAY_WIDTH;
    uint8_t start_column = ST7565_BLOCK_SIZE * update_start % ST7565_DISPLAY_WIDTH;
    // IC has 132 segment drivers, for panels with less width we need to offset the starting column
    if (HAS_FLAGS(st7565_rotation, DISPLAY_ROTATION_180)) {
        start_column += (132 - ST7565_DISPLAY_WIDTH);
    }

    spi_start(ST7565_SS_PIN, false, 0, ST7565_SPI_CLK_DIVISOR);

    st7565_send_cmd(PAM_PAGE_ADDR | start_page);
    st7565_send_cmd(PAM_SETCOLUMN_LSB | ((ST7565_COLUMN_OFFSET + start_column) & 0x0f));
    st7565_send_cmd(PAM_SETCOLUMN_MSB | ((ST7565_COLUMN_OFFSET + start_column) >> 4 & 0x0f));

    st7565_send_data(&st7565_buffer[ST7565_BLOCK_SIZE * update_start], ST7565_BLOCK_SIZE);

    // Turn on display if it is off
    st7565_on();

    // Clear dirty flag
    st7565_dirty &= ~((ST7565_BLOCK_TYPE)1 << update_start);
}

void st7565_set_cursor(uint8_t col, uint8_t line) {
    uint16_t index = line * ST7565_DISPLAY_WIDTH + col * ST7565_FONT_WIDTH;

    // Out of bounds?
    if (index >= ST7565_MATRIX_SIZE) {
        index = 0;
    }

    st7565_cursor = &st7565_buffer[index];
}

void st7565_advance_page(bool clearPageRemainder) {
    uint16_t index     = st7565_cursor - &st7565_buffer[0];
    uint8_t  remaining = ST7565_DISPLAY_WIDTH - (index % ST7565_DISPLAY_WIDTH);

    if (clearPageRemainder) {
        // Remaining Char count
        remaining = remaining / ST7565_FONT_WIDTH;

        // Write empty character until next line
        while (remaining--) st7565_write_char(' ', false);
    } else {
        // Next page index out of bounds?
        if (index + remaining >= ST7565_MATRIX_SIZE) {
            index     = 0;
            remaining = 0;
        }

        st7565_cursor = &st7565_buffer[index + remaining];
    }
}

void st7565_advance_char(void) {
    uint16_t nextIndex      = st7565_cursor - &st7565_buffer[0] + ST7565_FONT_WIDTH;
    uint8_t  remainingSpace = ST7565_DISPLAY_WIDTH - (nextIndex % ST7565_DISPLAY_WIDTH);

    // Do we have enough space on the current line for the next character
    if (remainingSpace < ST7565_FONT_WIDTH) {
        nextIndex += remainingSpace;
    }

    // Did we go out of bounds
    if (nextIndex >= ST7565_MATRIX_SIZE) {
        nextIndex = 0;
    }

    // Update cursor position
    st7565_cursor = &st7565_buffer[nextIndex];
}

// Main handler that writes character data to the display buffer
void st7565_write_char(const char data, bool invert) {
    // Advance to the next line if newline
    if (data == '\n') {
        // Old source wrote ' ' until end of line...
        st7565_advance_page(true);
        return;
    }

    if (data == '\r') {
        st7565_advance_page(false);
        return;
    }

    // copy the current render buffer to check for dirty after
    static uint8_t st7565_temp_buffer[ST7565_FONT_WIDTH];
    memcpy(&st7565_temp_buffer, st7565_cursor, ST7565_FONT_WIDTH);

    _Static_assert(sizeof(font) >= ((ST7565_FONT_END + 1 - ST7565_FONT_START) * ST7565_FONT_WIDTH), "ST7565_FONT_END references outside array");

    // set the reder buffer data
    uint8_t cast_data = (uint8_t)data;  // font based on unsigned type for index
    if (cast_data < ST7565_FONT_START || cast_data > ST7565_FONT_END) {
        memset(st7565_cursor, 0x00, ST7565_FONT_WIDTH);
    } else {
        const uint8_t *glyph = &font[(cast_data - ST7565_FONT_START) * ST7565_FONT_WIDTH];
        memcpy_P(st7565_cursor, glyph, ST7565_FONT_WIDTH);
    }

    // Invert if needed
    if (invert) {
        InvertCharacter(st7565_cursor);
    }

    // Dirty check
    if (memcmp(&st7565_temp_buffer, st7565_cursor, ST7565_FONT_WIDTH)) {
        uint16_t index = st7565_cursor - &st7565_buffer[0];
        st7565_dirty |= ((ST7565_BLOCK_TYPE)1 << (index / ST7565_BLOCK_SIZE));
        // Edgecase check if the written data spans the 2 chunks
        st7565_dirty |= ((ST7565_BLOCK_TYPE)1 << ((index + ST7565_FONT_WIDTH - 1) / ST7565_BLOCK_SIZE));
    }

    // Finally move to the next char
    st7565_advance_char();
}

void st7565_write(const char *data, bool invert) {
    const char *end = data + strlen(data);
    while (data < end) {
        st7565_write_char(*data, invert);
        data++;
    }
}

void st7565_write_ln(const char *data, bool invert) {
    st7565_write(data, invert);
    st7565_advance_page(true);
}

void st7565_pan(bool left) {
    uint16_t i = 0;
    for (uint16_t y = 0; y < ST7565_DISPLAY_HEIGHT / 8; y++) {
        if (left) {
            for (uint16_t x = 0; x < ST7565_DISPLAY_WIDTH - 1; x++) {
                i                = y * ST7565_DISPLAY_WIDTH + x;
                st7565_buffer[i] = st7565_buffer[i + 1];
            }
        } else {
            for (uint16_t x = ST7565_DISPLAY_WIDTH - 1; x > 0; x--) {
                i                = y * ST7565_DISPLAY_WIDTH + x;
                st7565_buffer[i] = st7565_buffer[i - 1];
            }
        }
    }
    st7565_dirty = ST7565_ALL_BLOCKS_MASK;
}

display_buffer_reader_t st7565_read_raw(uint16_t start_index) {
    if (start_index > ST7565_MATRIX_SIZE) start_index = ST7565_MATRIX_SIZE;
    display_buffer_reader_t ret_reader;
    ret_reader.current_element         = &st7565_buffer[start_index];
    ret_reader.remaining_element_count = ST7565_MATRIX_SIZE - start_index;
    return ret_reader;
}

void st7565_write_raw_byte(const char data, uint16_t index) {
    if (index > ST7565_MATRIX_SIZE) index = ST7565_MATRIX_SIZE;
    if (st7565_buffer[index] == data) return;
    st7565_buffer[index] = data;
    st7565_dirty |= ((ST7565_BLOCK_TYPE)1 << (index / ST7565_BLOCK_SIZE));
}

void st7565_write_raw(const char *data, uint16_t size) {
    uint16_t cursor_start_index = st7565_cursor - &st7565_buffer[0];
    if ((size + cursor_start_index) > ST7565_MATRIX_SIZE) size = ST7565_MATRIX_SIZE - cursor_start_index;
    for (uint16_t i = cursor_start_index; i < cursor_start_index + size; i++) {
        uint8_t c = *data++;
        if (st7565_buffer[i] == c) continue;
        st7565_buffer[i] = c;
        st7565_dirty |= ((ST7565_BLOCK_TYPE)1 << (i / ST7565_BLOCK_SIZE));
    }
}

void st7565_write_pixel(uint8_t x, uint8_t y, bool on) {
    if (x >= ST7565_DISPLAY_WIDTH) {
        return;
    }
    uint16_t index = x + (y / 8) * ST7565_DISPLAY_WIDTH;
    if (index >= ST7565_MATRIX_SIZE) {
        return;
    }
    uint8_t data = st7565_buffer[index];
    if (on) {
        data |= (1 << (y % 8));
    } else {
        data &= ~(1 << (y % 8));
    }
    if (st7565_buffer[index] != data) {
        st7565_buffer[index] = data;
        st7565_dirty |= ((ST7565_BLOCK_TYPE)1 << (index / ST7565_BLOCK_SIZE));
    }
}

#if defined(__AVR__)
void st7565_write_P(const char *data, bool invert) {
    uint8_t c = pgm_read_byte(data);
    while (c != 0) {
        st7565_write_char(c, invert);
        c = pgm_read_byte(++data);
    }
}

void st7565_write_ln_P(const char *data, bool invert) {
    st7565_write_P(data, invert);
    st7565_advance_page(true);
}

void st7565_write_raw_P(const char *data, uint16_t size) {
    uint16_t cursor_start_index = st7565_cursor - &st7565_buffer[0];
    if ((size + cursor_start_index) > ST7565_MATRIX_SIZE) size = ST7565_MATRIX_SIZE - cursor_start_index;
    for (uint16_t i = cursor_start_index; i < cursor_start_index + size; i++) {
        uint8_t c = pgm_read_byte(data++);
        if (st7565_buffer[i] == c) continue;
        st7565_buffer[i] = c;
        st7565_dirty |= ((ST7565_BLOCK_TYPE)1 << (i / ST7565_BLOCK_SIZE));
    }
}
#endif  // defined(__AVR__)

bool st7565_on(void) {
    if (!st7565_initialized) {
        return st7565_active;
    }

#if ST7565_TIMEOUT > 0
    st7565_timeout = timer_read32() + ST7565_TIMEOUT;
#endif

    if (!st7565_active) {
        spi_start(ST7565_SS_PIN, false, 0, ST7565_SPI_CLK_DIVISOR);
        st7565_send_cmd(DISPLAY_ON);
        spi_stop();
        st7565_active = true;
        st7565_on_user();
    }
    return st7565_active;
}

__attribute__((weak)) void st7565_on_user(void) {}

bool st7565_off(void) {
    if (!st7565_initialized) {
        return !st7565_active;
    }

    if (st7565_active) {
        spi_start(ST7565_SS_PIN, false, 0, ST7565_SPI_CLK_DIVISOR);
        st7565_send_cmd(DISPLAY_OFF);
        spi_stop();
        st7565_active = false;
        st7565_off_user();
    }
    return !st7565_active;
}

__attribute__((weak)) void st7565_off_user(void) {}

bool st7565_is_on(void) { return st7565_active; }

bool st7565_invert(bool invert) {
    if (!st7565_initialized) {
        return st7565_inverted;
    }

    if (invert != st7565_inverted) {
        spi_start(ST7565_SS_PIN, false, 0, ST7565_SPI_CLK_DIVISOR);
        st7565_send_cmd(invert ? INVERT_DISPLAY : NORMAL_DISPLAY);
        spi_stop();
        st7565_inverted = invert;
    }
    return st7565_inverted;
}

uint8_t st7565_max_chars(void) { return ST7565_DISPLAY_WIDTH / ST7565_FONT_WIDTH; }

uint8_t st7565_max_lines(void) { return ST7565_DISPLAY_HEIGHT / ST7565_FONT_HEIGHT; }

void st7565_task(void) {
    if (!st7565_initialized) {
        return;
    }

#if ST7565_UPDATE_INTERVAL > 0
    if (timer_elapsed(st7565_update_timeout) >= ST7565_UPDATE_INTERVAL) {
        st7565_update_timeout = timer_read();
        st7565_set_cursor(0, 0);
        st7565_task_user();
    }
#else
    st7565_set_cursor(0, 0);
    st7565_task_user();
#endif

    // Smart render system, no need to check for dirty
    st7565_render();

    // Display timeout check
#if ST7565_TIMEOUT > 0
    if (st7565_active && timer_expired32(timer_read32(), st7565_timeout)) {
        st7565_off();
    }
#endif
}

__attribute__((weak)) void st7565_task_user(void) {}

void st7565_reset(void) {
    writePinLow(ST7565_RST_PIN);
    wait_ms(20);
    writePinHigh(ST7565_RST_PIN);
    wait_ms(20);
}

spi_status_t st7565_send_cmd(uint8_t cmd) {
    writePinLow(ST7565_A0_PIN);
    return spi_write(cmd);
}

spi_status_t st7565_send_data(uint8_t *data, uint16_t length) {
    writePinHigh(ST7565_A0_PIN);
    return spi_transmit(data, length);
}
