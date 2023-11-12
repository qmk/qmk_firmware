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

#if defined(OLED_TRANSPORT_SPI)
#    include "spi_master.h"
#elif defined(OLED_TRANSPORT_I2C)
#    include "i2c_master.h"
#    if defined(USE_I2C) && defined(SPLIT_KEYBOARD)
#        include "keyboard.h"
#    endif
#endif
#include "oled_driver.h"
#include OLED_FONT_H
#include "timer.h"
#include "print.h"
#include <string.h>
#include "progmem.h"
#include "wait.h"

// Used commands from spec sheet: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
// for SH1106: https://www.velleman.eu/downloads/29/infosheets/sh1106_datasheet.pdf
// for SH1107: https://www.displayfuture.com/Display/datasheet/controller/SH1107.pdf

// Fundamental Commands
#define CONTRAST 0x81
#define DISPLAY_ALL_ON 0xA5
#define DISPLAY_ALL_ON_RESUME 0xA4
#define NORMAL_DISPLAY 0xA6
#define INVERT_DISPLAY 0xA7
#define DISPLAY_ON 0xAF
#define DISPLAY_OFF 0xAE
#define NOP 0xE3

// Scrolling Commands
#define ACTIVATE_SCROLL 0x2F
#define DEACTIVATE_SCROLL 0x2E
#define SCROLL_RIGHT 0x26
#define SCROLL_LEFT 0x27
#define SCROLL_RIGHT_UP 0x29
#define SCROLL_LEFT_UP 0x2A

// Addressing Setting Commands
#define MEMORY_MODE 0x20
#define COLUMN_ADDR 0x21
#define PAGE_ADDR 0x22
#define PAM_SETCOLUMN_LSB 0x00
#define PAM_SETCOLUMN_MSB 0x10
#define PAM_PAGE_ADDR 0xB0 // 0xb0 -- 0xb7

// Hardware Configuration Commands
#define DISPLAY_START_LINE 0x40
#define SEGMENT_REMAP 0xA0
#define SEGMENT_REMAP_INV 0xA1
#define MULTIPLEX_RATIO 0xA8
#define COM_SCAN_INC 0xC0
#define COM_SCAN_DEC 0xC8
#define DISPLAY_OFFSET 0xD3
#define COM_PINS 0xDA
#define COM_PINS_SEQ 0x02
#define COM_PINS_ALT 0x12
#define COM_PINS_SEQ_LR 0x22
#define COM_PINS_ALT_LR 0x32

// Timing & Driving Commands
#define DISPLAY_CLOCK 0xD5
#define PRE_CHARGE_PERIOD 0xD9
#define VCOM_DETECT 0xDB

// Advance Graphic Commands
#define FADE_BLINK 0x23
#define ENABLE_FADE 0x20
#define ENABLE_BLINK 0x30

// Charge Pump Commands
#define CHARGE_PUMP 0x8D

// Commands specific to the SH1107 chip
#define SH1107_DISPLAY_START_LINE 0xDC
#define SH1107_MEMORY_MODE_PAGE 0x20
#define SH1107_MEMORY_MODE_VERTICAL 0x21

// Misc defines
#ifndef OLED_BLOCK_COUNT
#    define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)
#endif
#ifndef OLED_BLOCK_SIZE
#    define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)
#endif
// Default display clock
#if !defined(OLED_DISPLAY_CLOCK)
#    define OLED_DISPLAY_CLOCK 0x80
#endif
// Default VCOMH deselect value
#if !defined(OLED_VCOM_DETECT)
#    define OLED_VCOM_DETECT 0x20
#endif
#if !defined(OLED_PRE_CHARGE_PERIOD)
#    define OLED_PRE_CHARGE_PERIOD 0xF1
#endif

#define OLED_ALL_BLOCKS_MASK (((((OLED_BLOCK_TYPE)1 << (OLED_BLOCK_COUNT - 1)) - 1) << 1) | 1)

#define OLED_IC_HAS_HORIZONTAL_MODE (OLED_IC == OLED_IC_SSD1306)
#define OLED_IC_COM_PINS_ARE_COLUMNS (OLED_IC == OLED_IC_SH1107)

#ifndef OLED_COM_PIN_COUNT
#    if OLED_IC == OLED_IC_SSD1306
#        define OLED_COM_PIN_COUNT 64
#    elif OLED_IC == OLED_IC_SH1106
#        define OLED_COM_PIN_COUNT 64
#    elif OLED_IC == OLED_IC_SH1107
#        define OLED_COM_PIN_COUNT 128
#    else
#        error Invalid OLED_IC value
#    endif
#endif

#ifndef OLED_COM_PIN_OFFSET
#    define OLED_COM_PIN_OFFSET 0
#endif

// i2c defines
#define I2C_CMD 0x00
#define I2C_DATA 0x40

#define HAS_FLAGS(bits, flags) ((bits & flags) == flags)

// Display buffer's is the same as the OLED memory layout
// this is so we don't end up with rounding errors with
// parts of the display unusable or don't get cleared correctly
// and also allows for drawing & inverting
uint8_t         oled_buffer[OLED_MATRIX_SIZE];
uint8_t *       oled_cursor;
OLED_BLOCK_TYPE oled_dirty          = 0;
bool            oled_initialized    = false;
bool            oled_active         = false;
bool            oled_scrolling      = false;
bool            oled_inverted       = false;
uint8_t         oled_brightness     = OLED_BRIGHTNESS;
oled_rotation_t oled_rotation       = 0;
uint8_t         oled_rotation_width = 0;
uint8_t         oled_scroll_speed   = 0; // this holds the speed after being remapped to ssd1306 internal values
uint8_t         oled_scroll_start   = 0;
uint8_t         oled_scroll_end     = 7;
#if OLED_TIMEOUT > 0
uint32_t oled_timeout;
#endif
#if OLED_SCROLL_TIMEOUT > 0
uint32_t oled_scroll_timeout;
#endif
#if OLED_UPDATE_INTERVAL > 0
uint16_t oled_update_timeout;
#endif

#if defined(OLED_TRANSPORT_SPI)
#    ifndef OLED_DC_PIN
#        error "The OLED driver in SPI needs a D/C pin defined"
#    endif
#    ifndef OLED_CS_PIN
#        error "The OLED driver in SPI needs a CS pin defined"
#    endif
#    ifndef OLED_SPI_MODE
#        define OLED_SPI_MODE 3
#    endif
#    ifndef OLED_SPI_DIVISOR
#        define OLED_SPI_DIVISOR 2
#    endif
#elif defined(OLED_TRANSPORT_I2C)
#    if !defined(OLED_DISPLAY_ADDRESS)
#        define OLED_DISPLAY_ADDRESS 0x3C
#    endif
#endif

// Transmit/Write Funcs.
__attribute__((weak)) bool oled_send_cmd(const uint8_t *data, uint16_t size) {
#if defined(OLED_TRANSPORT_SPI)
    if (!spi_start(OLED_CS_PIN, false, OLED_SPI_MODE, OLED_SPI_DIVISOR)) {
        return false;
    }
    // Command Mode
    writePinLow(OLED_DC_PIN);
    // Send the commands
    if (spi_transmit(&data[1], size - 1) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }
    spi_stop();
    return true;
#elif defined(OLED_TRANSPORT_I2C)
    i2c_status_t status = i2c_transmit((OLED_DISPLAY_ADDRESS << 1), data, size, OLED_I2C_TIMEOUT);

    return (status == I2C_STATUS_SUCCESS);
#endif
}

__attribute__((weak)) bool oled_send_cmd_P(const uint8_t *data, uint16_t size) {
#if defined(__AVR__)
#    if defined(OLED_TRANSPORT_SPI)
    if (!spi_start(OLED_CS_PIN, false, OLED_SPI_MODE, OLED_SPI_DIVISOR)) {
        return false;
    }
    spi_status_t status = SPI_STATUS_SUCCESS;
    // Command Mode
    writePinLow(OLED_DC_PIN);
    // Send the commands
    for (uint16_t i = 1; i < size && status >= 0; i++) {
        status = spi_write(pgm_read_byte((const char *)&data[i]));
    }
    spi_stop();
    return (status >= 0);
#    elif defined(OLED_TRANSPORT_I2C)
    i2c_status_t status = i2c_start((OLED_DISPLAY_ADDRESS << 1) | I2C_WRITE, OLED_I2C_TIMEOUT);

    for (uint16_t i = 0; i < size && status >= 0; i++) {
        status = i2c_write(pgm_read_byte((const char *)data++), OLED_I2C_TIMEOUT);
    }

    i2c_stop();

    return (status == I2C_STATUS_SUCCESS);
#    endif
#else
    return oled_send_cmd(data, size);
#endif
}

__attribute__((weak)) bool oled_send_data(const uint8_t *data, uint16_t size) {
#if defined(OLED_TRANSPORT_SPI)
    if (!spi_start(OLED_CS_PIN, false, OLED_SPI_MODE, OLED_SPI_DIVISOR)) {
        return false;
    }
    // Data Mode
    writePinHigh(OLED_DC_PIN);
    // Send the commands
    if (spi_transmit(data, size) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }
    spi_stop();
    return true;
#elif defined(OLED_TRANSPORT_I2C)
    i2c_status_t status = i2c_writeReg((OLED_DISPLAY_ADDRESS << 1), I2C_DATA, data, size, OLED_I2C_TIMEOUT);
    return (status == I2C_STATUS_SUCCESS);
#endif
}

__attribute__((weak)) void oled_driver_init(void) {
#if defined(OLED_TRANSPORT_SPI)
    spi_init();
    setPinOutput(OLED_CS_PIN);
    writePinHigh(OLED_CS_PIN);

    setPinOutput(OLED_DC_PIN);
    writePinLow(OLED_DC_PIN);
#    ifdef OLED_RST_PIN
    /* Reset device */
    setPinOutput(OLED_RST_PIN);
    writePinLow(OLED_RST_PIN);
    wait_ms(20);
    writePinHigh(OLED_RST_PIN);
    wait_ms(20);
#    endif
#elif defined(OLED_TRANSPORT_I2C)
    i2c_init();
#endif
}

// Flips the rendering bits for a character at the current cursor position
static void InvertCharacter(uint8_t *cursor) {
    const uint8_t *end = cursor + OLED_FONT_WIDTH;
    while (cursor < end) {
        *cursor = ~(*cursor);
        cursor++;
    }
}

bool oled_init(oled_rotation_t rotation) {
#if defined(USE_I2C) && defined(SPLIT_KEYBOARD) && defined(OLED_TRANSPORT_I2C)
    if (!is_keyboard_master()) {
        return true;
    }
#endif

    oled_rotation = oled_init_user(oled_init_kb(rotation));
    if (!HAS_FLAGS(oled_rotation, OLED_ROTATION_90)) {
        oled_rotation_width = OLED_DISPLAY_WIDTH;
    } else {
        oled_rotation_width = OLED_DISPLAY_HEIGHT;
    }
    oled_driver_init();

    static const uint8_t PROGMEM display_setup1[] = {
        I2C_CMD,
        DISPLAY_OFF,
        DISPLAY_CLOCK,
        OLED_DISPLAY_CLOCK,
        MULTIPLEX_RATIO,
#if OLED_IC_COM_PINS_ARE_COLUMNS
        OLED_DISPLAY_WIDTH - 1,
#else
        OLED_DISPLAY_HEIGHT - 1,
#endif
#if OLED_IC == OLED_IC_SH1107
        SH1107_DISPLAY_START_LINE,
        0x00,
#else
        DISPLAY_START_LINE | 0x00,
#endif
        CHARGE_PUMP,
        0x14,
#if OLED_IC_HAS_HORIZONTAL_MODE
        // MEMORY_MODE is unsupported on SH1106 (Page Addressing only)
        MEMORY_MODE,
        0x00, // Horizontal addressing mode
#elif OLED_IC == OLED_IC_SH1107
        // Page addressing mode
        SH1107_MEMORY_MODE_PAGE,
#endif
    };
    if (!oled_send_cmd_P(display_setup1, ARRAY_SIZE(display_setup1))) {
        print("oled_init cmd set 1 failed\n");
        return false;
    }

    if (!HAS_FLAGS(oled_rotation, OLED_ROTATION_180)) {
        static const uint8_t PROGMEM display_normal[] = {
            I2C_CMD, SEGMENT_REMAP_INV, COM_SCAN_DEC, DISPLAY_OFFSET, OLED_COM_PIN_OFFSET,
        };
        if (!oled_send_cmd_P(display_normal, ARRAY_SIZE(display_normal))) {
            print("oled_init cmd normal rotation failed\n");
            return false;
        }
    } else {
        static const uint8_t PROGMEM display_flipped[] = {
            I2C_CMD, SEGMENT_REMAP, COM_SCAN_INC, DISPLAY_OFFSET, (OLED_COM_PIN_COUNT - OLED_COM_PIN_OFFSET) % OLED_COM_PIN_COUNT,
        };
        if (!oled_send_cmd_P(display_flipped, ARRAY_SIZE(display_flipped))) {
            print("display_flipped failed\n");
            return false;
        }
    }

    static const uint8_t PROGMEM display_setup2[] = {I2C_CMD, COM_PINS, OLED_COM_PINS, CONTRAST, OLED_BRIGHTNESS, PRE_CHARGE_PERIOD, OLED_PRE_CHARGE_PERIOD, VCOM_DETECT, OLED_VCOM_DETECT, DISPLAY_ALL_ON_RESUME, NORMAL_DISPLAY, DEACTIVATE_SCROLL, DISPLAY_ON};
    if (!oled_send_cmd_P(display_setup2, ARRAY_SIZE(display_setup2))) {
        print("display_setup2 failed\n");
        return false;
    }

#if OLED_TIMEOUT > 0
    oled_timeout = timer_read32() + OLED_TIMEOUT;
#endif
#if OLED_SCROLL_TIMEOUT > 0
    oled_scroll_timeout = timer_read32() + OLED_SCROLL_TIMEOUT;
#endif

    oled_clear();
    oled_initialized = true;
    oled_active      = true;
    oled_scrolling   = false;
    return true;
}

__attribute__((weak)) oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return rotation;
}
__attribute__((weak)) oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
}

void oled_clear(void) {
    memset(oled_buffer, 0, sizeof(oled_buffer));
    oled_cursor = &oled_buffer[0];
    oled_dirty  = OLED_ALL_BLOCKS_MASK;
}

static void calc_bounds(uint8_t update_start, uint8_t *cmd_array) {
    // Calculate commands to set memory addressing bounds.
    uint8_t start_page   = OLED_BLOCK_SIZE * update_start / OLED_DISPLAY_WIDTH;
    uint8_t start_column = OLED_BLOCK_SIZE * update_start % OLED_DISPLAY_WIDTH;
#if !OLED_IC_HAS_HORIZONTAL_MODE
    // Commands for Page Addressing Mode. Sets starting page and column; has no end bound.
    // Column value must be split into high and low nybble and sent as two commands.
    cmd_array[0] = PAM_PAGE_ADDR | start_page;
    cmd_array[1] = PAM_SETCOLUMN_LSB | ((OLED_COLUMN_OFFSET + start_column) & 0x0f);
    cmd_array[2] = PAM_SETCOLUMN_MSB | ((OLED_COLUMN_OFFSET + start_column) >> 4 & 0x0f);
#else
    // Commands for use in Horizontal Addressing mode.
    cmd_array[1] = start_column + OLED_COLUMN_OFFSET;
    cmd_array[4] = start_page;
    cmd_array[2] = (OLED_BLOCK_SIZE + OLED_DISPLAY_WIDTH - 1) % OLED_DISPLAY_WIDTH + cmd_array[1];
    cmd_array[5] = (OLED_BLOCK_SIZE + OLED_DISPLAY_WIDTH - 1) / OLED_DISPLAY_WIDTH - 1 + cmd_array[4];
#endif
}

static void calc_bounds_90(uint8_t update_start, uint8_t *cmd_array) {
    // Block numbering starts from the bottom left corner, going up and then to
    // the right.  The controller needs the page and column numbers for the top
    // left and bottom right corners of that block.

    // Total number of pages across the screen height.
    const uint8_t height_in_pages = OLED_DISPLAY_HEIGHT / 8;

    // Difference of starting page numbers for adjacent blocks; may be 0 if
    // blocks are large enough to occupy one or more whole 8px columns.
    const uint8_t page_inc_per_block = OLED_BLOCK_SIZE % OLED_DISPLAY_HEIGHT / 8;

    // Top page number for a block which is at the bottom edge of the screen.
    const uint8_t bottom_block_top_page = (height_in_pages - page_inc_per_block) % height_in_pages;

#if !OLED_IC_HAS_HORIZONTAL_MODE
    // Only the Page Addressing Mode is supported
    uint8_t start_page   = bottom_block_top_page - (OLED_BLOCK_SIZE * update_start % OLED_DISPLAY_HEIGHT / 8);
    uint8_t start_column = OLED_BLOCK_SIZE * update_start / OLED_DISPLAY_HEIGHT * 8;
    cmd_array[0]         = PAM_PAGE_ADDR | start_page;
    cmd_array[1]         = PAM_SETCOLUMN_LSB | ((OLED_COLUMN_OFFSET + start_column) & 0x0f);
    cmd_array[2]         = PAM_SETCOLUMN_MSB | ((OLED_COLUMN_OFFSET + start_column) >> 4 & 0x0f);
#else
    cmd_array[1] = OLED_BLOCK_SIZE * update_start / OLED_DISPLAY_HEIGHT * 8 + OLED_COLUMN_OFFSET;
    cmd_array[4] = bottom_block_top_page - (OLED_BLOCK_SIZE * update_start % OLED_DISPLAY_HEIGHT / 8);
    cmd_array[2] = (OLED_BLOCK_SIZE + OLED_DISPLAY_HEIGHT - 1) / OLED_DISPLAY_HEIGHT * 8 - 1 + cmd_array[1];
    cmd_array[5] = (OLED_BLOCK_SIZE + OLED_DISPLAY_HEIGHT - 1) % OLED_DISPLAY_HEIGHT / 8 + cmd_array[4];
#endif
}

uint8_t crot(uint8_t a, int8_t n) {
    const uint8_t mask = 0x7;
    n &= mask;
    return a << n | a >> (-n & mask);
}

static void rotate_90(const uint8_t *src, uint8_t *dest) {
    for (uint8_t i = 0, shift = 7; i < 8; ++i, --shift) {
        uint8_t selector = (1 << i);
        for (uint8_t j = 0; j < 8; ++j) {
            dest[i] |= crot(src[j] & selector, shift - (int8_t)j);
        }
    }
}

void oled_render(void) {
    // Do we have work to do?
    oled_dirty &= OLED_ALL_BLOCKS_MASK;
    if (!oled_dirty || !oled_initialized || oled_scrolling) {
        return;
    }

    // Turn on display if it is off
    oled_on();

    uint8_t update_start  = 0;
    uint8_t num_processed = 0;
    while (oled_dirty && num_processed++ < OLED_UPDATE_PROCESS_LIMIT) { // render all dirty blocks (up to the configured limit)
        // Find next dirty block
        while (!(oled_dirty & ((OLED_BLOCK_TYPE)1 << update_start))) {
            ++update_start;
        }

        // Set column & page position
#if OLED_IC_HAS_HORIZONTAL_MODE
        static uint8_t display_start[] = {I2C_CMD, COLUMN_ADDR, 0, OLED_DISPLAY_WIDTH - 1, PAGE_ADDR, 0, OLED_DISPLAY_HEIGHT / 8 - 1};
#else
        static uint8_t display_start[] = {I2C_CMD, PAM_PAGE_ADDR, PAM_SETCOLUMN_LSB, PAM_SETCOLUMN_MSB};
#endif
        if (!HAS_FLAGS(oled_rotation, OLED_ROTATION_90)) {
            calc_bounds(update_start, &display_start[1]); // Offset from I2C_CMD byte at the start
        } else {
            calc_bounds_90(update_start, &display_start[1]); // Offset from I2C_CMD byte at the start
        }

        // Send column & page position
        if (!oled_send_cmd(display_start, ARRAY_SIZE(display_start))) {
            print("oled_render offset command failed\n");
            return;
        }

        if (!HAS_FLAGS(oled_rotation, OLED_ROTATION_90)) {
            // Send render data chunk as is
            if (!oled_send_data(&oled_buffer[OLED_BLOCK_SIZE * update_start], OLED_BLOCK_SIZE)) {
                print("oled_render data failed\n");
                return;
            }
        } else {
            // Rotate the render chunks
            const static uint8_t source_map[] = OLED_SOURCE_MAP;
            const static uint8_t target_map[] = OLED_TARGET_MAP;

            static uint8_t temp_buffer[OLED_BLOCK_SIZE];
            memset(temp_buffer, 0, sizeof(temp_buffer));
            for (uint8_t i = 0; i < sizeof(source_map); ++i) {
                rotate_90(&oled_buffer[OLED_BLOCK_SIZE * update_start + source_map[i]], &temp_buffer[target_map[i]]);
            }

#if OLED_IC_HAS_HORIZONTAL_MODE
            // Send render data chunk after rotating
            if (!oled_send_data(&temp_buffer[0], OLED_BLOCK_SIZE)) {
                print("oled_render90 data failed\n");
                return;
            }
#else
            // For SH1106 or SH1107 the data chunk must be split into separate pieces for each page
            const uint8_t columns_in_block = (OLED_BLOCK_SIZE + OLED_DISPLAY_HEIGHT - 1) / OLED_DISPLAY_HEIGHT * 8;
            const uint8_t num_pages        = OLED_BLOCK_SIZE / columns_in_block;
            for (uint8_t i = 0; i < num_pages; ++i) {
                // Send column & page position for all pages except the first one
                if (i > 0) {
                    display_start[1]++;
                    if (!oled_send_cmd(display_start, ARRAY_SIZE(display_start))) {
                        print("oled_render offset command failed\n");
                        return;
                    }
                }
                // Send data for the page
                if (!oled_send_data(&temp_buffer[columns_in_block * i], columns_in_block)) {
                    print("oled_render90 data failed\n");
                    return;
                }
            }
#endif
        }

        // Clear dirty flag of just rendered block
        oled_dirty &= ~((OLED_BLOCK_TYPE)1 << update_start);
    }
}

void oled_set_cursor(uint8_t col, uint8_t line) {
    uint16_t index = line * oled_rotation_width + col * OLED_FONT_WIDTH;

    // Out of bounds?
    if (index >= OLED_MATRIX_SIZE) {
        index = 0;
    }

    oled_cursor = &oled_buffer[index];
}

void oled_advance_page(bool clearPageRemainder) {
    uint16_t index     = oled_cursor - &oled_buffer[0];
    uint8_t  remaining = oled_rotation_width - (index % oled_rotation_width);

    if (clearPageRemainder) {
        // Remaining Char count
        remaining = remaining / OLED_FONT_WIDTH;

        // Write empty character until next line
        while (remaining--)
            oled_write_char(' ', false);
    } else {
        // Next page index out of bounds?
        if (index + remaining >= OLED_MATRIX_SIZE) {
            index     = 0;
            remaining = 0;
        }

        oled_cursor = &oled_buffer[index + remaining];
    }
}

void oled_advance_char(void) {
    uint16_t nextIndex      = oled_cursor - &oled_buffer[0] + OLED_FONT_WIDTH;
    uint8_t  remainingSpace = oled_rotation_width - (nextIndex % oled_rotation_width);

    // Do we have enough space on the current line for the next character
    if (remainingSpace < OLED_FONT_WIDTH) {
        nextIndex += remainingSpace;
    }

    // Did we go out of bounds
    if (nextIndex >= OLED_MATRIX_SIZE) {
        nextIndex = 0;
    }

    // Update cursor position
    oled_cursor = &oled_buffer[nextIndex];
}

// Main handler that writes character data to the display buffer
void oled_write_char(const char data, bool invert) {
    // Advance to the next line if newline
    if (data == '\n') {
        // Old source wrote ' ' until end of line...
        oled_advance_page(true);
        return;
    }

    if (data == '\r') {
        oled_advance_page(false);
        return;
    }

    // copy the current render buffer to check for dirty after
    static uint8_t oled_temp_buffer[OLED_FONT_WIDTH];
    memcpy(&oled_temp_buffer, oled_cursor, OLED_FONT_WIDTH);

    _Static_assert(sizeof(font) >= ((OLED_FONT_END + 1 - OLED_FONT_START) * OLED_FONT_WIDTH), "OLED_FONT_END references outside array");

    // set the reder buffer data
    uint8_t cast_data = (uint8_t)data; // font based on unsigned type for index
    if (cast_data < OLED_FONT_START || cast_data > OLED_FONT_END) {
        memset(oled_cursor, 0x00, OLED_FONT_WIDTH);
    } else {
        const uint8_t *glyph = &font[(cast_data - OLED_FONT_START) * OLED_FONT_WIDTH];
        memcpy_P(oled_cursor, glyph, OLED_FONT_WIDTH);
    }

    // Invert if needed
    if (invert) {
        InvertCharacter(oled_cursor);
    }

    // Dirty check
    if (memcmp(&oled_temp_buffer, oled_cursor, OLED_FONT_WIDTH)) {
        uint16_t index = oled_cursor - &oled_buffer[0];
        oled_dirty |= ((OLED_BLOCK_TYPE)1 << (index / OLED_BLOCK_SIZE));
        // Edgecase check if the written data spans the 2 chunks
        oled_dirty |= ((OLED_BLOCK_TYPE)1 << ((index + OLED_FONT_WIDTH - 1) / OLED_BLOCK_SIZE));
    }

    // Finally move to the next char
    oled_advance_char();
}

void oled_write(const char *data, bool invert) {
    const char *end = data + strlen(data);
    while (data < end) {
        oled_write_char(*data, invert);
        data++;
    }
}

void oled_write_ln(const char *data, bool invert) {
    oled_write(data, invert);
    oled_advance_page(true);
}

void oled_pan(bool left) {
    uint16_t i = 0;
    for (uint16_t y = 0; y < OLED_DISPLAY_HEIGHT / 8; y++) {
        if (left) {
            for (uint16_t x = 0; x < OLED_DISPLAY_WIDTH - 1; x++) {
                i              = y * OLED_DISPLAY_WIDTH + x;
                oled_buffer[i] = oled_buffer[i + 1];
            }
        } else {
            for (uint16_t x = OLED_DISPLAY_WIDTH - 1; x > 0; x--) {
                i              = y * OLED_DISPLAY_WIDTH + x;
                oled_buffer[i] = oled_buffer[i - 1];
            }
        }
    }
    oled_dirty = OLED_ALL_BLOCKS_MASK;
}

oled_buffer_reader_t oled_read_raw(uint16_t start_index) {
    if (start_index > OLED_MATRIX_SIZE) start_index = OLED_MATRIX_SIZE;
    oled_buffer_reader_t ret_reader;
    ret_reader.current_element         = &oled_buffer[start_index];
    ret_reader.remaining_element_count = OLED_MATRIX_SIZE - start_index;
    return ret_reader;
}

void oled_write_raw_byte(const char data, uint16_t index) {
    if (index > OLED_MATRIX_SIZE) index = OLED_MATRIX_SIZE;
    if (oled_buffer[index] == data) return;
    oled_buffer[index] = data;
    oled_dirty |= ((OLED_BLOCK_TYPE)1 << (index / OLED_BLOCK_SIZE));
}

void oled_write_raw(const char *data, uint16_t size) {
    uint16_t cursor_start_index = oled_cursor - &oled_buffer[0];
    if ((size + cursor_start_index) > OLED_MATRIX_SIZE) size = OLED_MATRIX_SIZE - cursor_start_index;
    for (uint16_t i = cursor_start_index; i < cursor_start_index + size; i++) {
        uint8_t c = *data++;
        if (oled_buffer[i] == c) continue;
        oled_buffer[i] = c;
        oled_dirty |= ((OLED_BLOCK_TYPE)1 << (i / OLED_BLOCK_SIZE));
    }
}

void oled_write_pixel(uint8_t x, uint8_t y, bool on) {
    if (x >= oled_rotation_width) {
        return;
    }
    uint16_t index = x + (y / 8) * oled_rotation_width;
    if (index >= OLED_MATRIX_SIZE) {
        return;
    }
    uint8_t data = oled_buffer[index];
    if (on) {
        data |= (1 << (y % 8));
    } else {
        data &= ~(1 << (y % 8));
    }
    if (oled_buffer[index] != data) {
        oled_buffer[index] = data;
        oled_dirty |= ((OLED_BLOCK_TYPE)1 << (index / OLED_BLOCK_SIZE));
    }
}

#if defined(__AVR__)
void oled_write_P(const char *data, bool invert) {
    uint8_t c = pgm_read_byte(data);
    while (c != 0) {
        oled_write_char(c, invert);
        c = pgm_read_byte(++data);
    }
}

void oled_write_ln_P(const char *data, bool invert) {
    oled_write_P(data, invert);
    oled_advance_page(true);
}

void oled_write_raw_P(const char *data, uint16_t size) {
    uint16_t cursor_start_index = oled_cursor - &oled_buffer[0];
    if ((size + cursor_start_index) > OLED_MATRIX_SIZE) size = OLED_MATRIX_SIZE - cursor_start_index;
    for (uint16_t i = cursor_start_index; i < cursor_start_index + size; i++) {
        uint8_t c = pgm_read_byte(data++);
        if (oled_buffer[i] == c) continue;
        oled_buffer[i] = c;
        oled_dirty |= ((OLED_BLOCK_TYPE)1 << (i / OLED_BLOCK_SIZE));
    }
}
#endif // defined(__AVR__)

bool oled_on(void) {
    if (!oled_initialized) {
        return oled_active;
    }

#if OLED_TIMEOUT > 0
    oled_timeout = timer_read32() + OLED_TIMEOUT;
#endif

    static const uint8_t PROGMEM display_on[] =
#ifdef OLED_FADE_OUT
        {I2C_CMD, FADE_BLINK, 0x00};
#else
        {I2C_CMD, DISPLAY_ON};
#endif

    if (!oled_active) {
        if (!oled_send_cmd_P(display_on, ARRAY_SIZE(display_on))) {
            print("oled_on cmd failed\n");
            return oled_active;
        }
        oled_active = true;
    }
    return oled_active;
}

bool oled_off(void) {
    if (!oled_initialized) {
        return !oled_active;
    }

    static const uint8_t PROGMEM display_off[] =
#ifdef OLED_FADE_OUT
        {I2C_CMD, FADE_BLINK, ENABLE_FADE | OLED_FADE_OUT_INTERVAL};
#else
        {I2C_CMD, DISPLAY_OFF};
#endif

    if (oled_active) {
        if (!oled_send_cmd_P(display_off, ARRAY_SIZE(display_off))) {
            print("oled_off cmd failed\n");
            return oled_active;
        }
        oled_active = false;
    }
    return !oled_active;
}

bool is_oled_on(void) {
    return oled_active;
}

uint8_t oled_set_brightness(uint8_t level) {
    if (!oled_initialized) {
        return oled_brightness;
    }

    uint8_t set_contrast[] = {I2C_CMD, CONTRAST, level};
    if (oled_brightness != level) {
        if (!oled_send_cmd(set_contrast, ARRAY_SIZE(set_contrast))) {
            print("set_brightness cmd failed\n");
            return oled_brightness;
        }
        oled_brightness = level;
    }
    return oled_brightness;
}

uint8_t oled_get_brightness(void) {
    return oled_brightness;
}

// Set the specific 8 lines rows of the screen to scroll.
// 0 is the default for start, and 7 for end, which is the entire
// height of the screen.  For 128x32 screens, rows 4-7 are not used.
void oled_scroll_set_area(uint8_t start_line, uint8_t end_line) {
    oled_scroll_start = start_line;
    oled_scroll_end   = end_line;
}

void oled_scroll_set_speed(uint8_t speed) {
    // Sets the speed for scrolling... does not take effect
    // until scrolling is either started or restarted
    // the ssd1306 supports 8 speeds
    // FrameRate2   speed = 7
    // FrameRate3   speed = 4
    // FrameRate4   speed = 5
    // FrameRate5   speed = 0
    // FrameRate25  speed = 6
    // FrameRate64  speed = 1
    // FrameRate128 speed = 2
    // FrameRate256 speed = 3
    // for ease of use these are remaped here to be in order
    static const uint8_t scroll_remap[8] = {7, 4, 5, 0, 6, 1, 2, 3};
    oled_scroll_speed                    = scroll_remap[speed];
}

bool oled_scroll_right(void) {
    if (!oled_initialized) {
        return oled_scrolling;
    }

    // Dont enable scrolling if we need to update the display
    // This prevents scrolling of bad data from starting the scroll too early after init
    if (!oled_dirty && !oled_scrolling) {
        uint8_t display_scroll_right[] = {I2C_CMD, SCROLL_RIGHT, 0x00, oled_scroll_start, oled_scroll_speed, oled_scroll_end, 0x00, 0xFF, ACTIVATE_SCROLL};
        if (!oled_send_cmd(display_scroll_right, ARRAY_SIZE(display_scroll_right))) {
            print("oled_scroll_right cmd failed\n");
            return oled_scrolling;
        }
        oled_scrolling = true;
    }
    return oled_scrolling;
}

bool oled_scroll_left(void) {
    if (!oled_initialized) {
        return oled_scrolling;
    }

    // Dont enable scrolling if we need to update the display
    // This prevents scrolling of bad data from starting the scroll too early after init
    if (!oled_dirty && !oled_scrolling) {
        uint8_t display_scroll_left[] = {I2C_CMD, SCROLL_LEFT, 0x00, oled_scroll_start, oled_scroll_speed, oled_scroll_end, 0x00, 0xFF, ACTIVATE_SCROLL};
        if (!oled_send_cmd(display_scroll_left, ARRAY_SIZE(display_scroll_left))) {
            print("oled_scroll_left cmd failed\n");
            return oled_scrolling;
        }
        oled_scrolling = true;
    }
    return oled_scrolling;
}

bool oled_scroll_off(void) {
    if (!oled_initialized) {
        return !oled_scrolling;
    }

    if (oled_scrolling) {
        static const uint8_t PROGMEM display_scroll_off[] = {I2C_CMD, DEACTIVATE_SCROLL};
        if (!oled_send_cmd_P(display_scroll_off, ARRAY_SIZE(display_scroll_off))) {
            print("oled_scroll_off cmd failed\n");
            return oled_scrolling;
        }
        oled_scrolling = false;
        oled_dirty     = OLED_ALL_BLOCKS_MASK;
    }
    return !oled_scrolling;
}

bool is_oled_scrolling(void) {
    return oled_scrolling;
}

bool oled_invert(bool invert) {
    if (!oled_initialized) {
        return oled_inverted;
    }

    if (invert && !oled_inverted) {
        static const uint8_t PROGMEM display_inverted[] = {I2C_CMD, INVERT_DISPLAY};
        if (!oled_send_cmd_P(display_inverted, ARRAY_SIZE(display_inverted))) {
            print("oled_invert cmd failed\n");
            return oled_inverted;
        }
        oled_inverted = true;
    } else if (!invert && oled_inverted) {
        static const uint8_t PROGMEM display_normal[] = {I2C_CMD, NORMAL_DISPLAY};
        if (!oled_send_cmd_P(display_normal, ARRAY_SIZE(display_normal))) {
            print("oled_invert cmd failed\n");
            return oled_inverted;
        }
        oled_inverted = false;
    }

    return oled_inverted;
}

uint8_t oled_max_chars(void) {
    if (!HAS_FLAGS(oled_rotation, OLED_ROTATION_90)) {
        return OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH;
    }
    return OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH;
}

uint8_t oled_max_lines(void) {
    if (!HAS_FLAGS(oled_rotation, OLED_ROTATION_90)) {
        return OLED_DISPLAY_HEIGHT / OLED_FONT_HEIGHT;
    }
    return OLED_DISPLAY_WIDTH / OLED_FONT_HEIGHT;
}

void oled_task(void) {
    if (!oled_initialized) {
        return;
    }

#if OLED_UPDATE_INTERVAL > 0
    if (timer_elapsed(oled_update_timeout) >= OLED_UPDATE_INTERVAL) {
        oled_update_timeout = timer_read();
        oled_set_cursor(0, 0);
        oled_task_kb();
    }
#else
    oled_set_cursor(0, 0);
    oled_task_kb();
#endif

#if OLED_SCROLL_TIMEOUT > 0
    if (oled_dirty && oled_scrolling) {
        oled_scroll_timeout = timer_read32() + OLED_SCROLL_TIMEOUT;
        oled_scroll_off();
    }
#endif

    // Smart render system, no need to check for dirty
    oled_render();

    // Display timeout check
#if OLED_TIMEOUT > 0
    if (oled_active && timer_expired32(timer_read32(), oled_timeout)) {
        oled_off();
    }
#endif

#if OLED_SCROLL_TIMEOUT > 0
    if (!oled_scrolling && timer_expired32(timer_read32(), oled_scroll_timeout)) {
#    ifdef OLED_SCROLL_TIMEOUT_RIGHT
        oled_scroll_right();
#    else
        oled_scroll_left();
#    endif
    }
#endif
}

__attribute__((weak)) bool oled_task_kb(void) {
    return oled_task_user();
}
__attribute__((weak)) bool oled_task_user(void) {
    return true;
}
