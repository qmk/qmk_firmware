/*
Copyright 2022

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

#include "hd44780.h"
#include "gpio.h"
#include "progmem.h"
#include "wait.h"

#ifndef HD44780_DATA_PINS
#    error hd44780: no data pins defined!
#endif

#ifndef HD44780_RS_PIN
#    error hd44780: no RS pin defined!
#endif

#ifndef HD44780_RW_PIN
#    error hd44780: no R/W pin defined!
#endif

#ifndef HD44780_E_PIN
#    error hd44780: no E pin defined!
#endif

static const pin_t data_pins[4] = HD44780_DATA_PINS;

#ifndef HD44780_DISPLAY_COLS
#    define HD44780_DISPLAY_COLS 16
#endif

#ifndef HD44780_DISPLAY_LINES
#    define HD44780_DISPLAY_LINES 2
#endif

#ifndef HD44780_DDRAM_LINE0_ADDR
#    define HD44780_DDRAM_LINE0_ADDR 0x00
#endif
#ifndef HD44780_DDRAM_LINE1_ADDR
#    define HD44780_DDRAM_LINE1_ADDR 0x40
#endif

#define HD44780_INIT_DELAY_MS 16
#define HD44780_ENABLE_DELAY_US 1

static void hd44780_latch(void) {
    writePinHigh(HD44780_E_PIN);
    wait_us(HD44780_ENABLE_DELAY_US);
    writePinLow(HD44780_E_PIN);
}

void hd44780_write(uint8_t data, bool isData) {
    writePin(HD44780_RS_PIN, isData);
    writePinLow(HD44780_RW_PIN);

    for (int i = 0; i < 4; i++) {
        setPinOutput(data_pins[i]);
    }

    // Write high nibble
    for (int i = 0; i < 4; i++) {
        writePin(data_pins[i], (data >> 4) & (1 << i));
    }
    hd44780_latch();

    // Write low nibble
    for (int i = 0; i < 4; i++) {
        writePin(data_pins[i], data & (1 << i));
    }
    hd44780_latch();

    for (int i = 0; i < 4; i++) {
        writePinHigh(data_pins[i]);
    }
}

uint8_t hd44780_read(bool isData) {
    uint8_t data = 0;

    writePin(HD44780_RS_PIN, isData);
    writePinHigh(HD44780_RW_PIN);

    for (int i = 0; i < 4; i++) {
        setPinInput(data_pins[i]);
    }

    writePinHigh(HD44780_E_PIN);
    wait_us(HD44780_ENABLE_DELAY_US);

    // Read high nibble
    for (int i = 0; i < 4; i++) {
        data |= (readPin(data_pins[i]) << i);
    }

    data <<= 4;

    writePinLow(HD44780_E_PIN);
    wait_us(HD44780_ENABLE_DELAY_US);
    writePinHigh(HD44780_E_PIN);
    wait_us(HD44780_ENABLE_DELAY_US);

    // Read low nibble
    for (int i = 0; i < 4; i++) {
        data |= (readPin(data_pins[i]) << i);
    }

    writePinLow(HD44780_E_PIN);

    return data;
}

bool hd44780_busy(void) {
    return hd44780_read(false) & HD44780_BUSY_FLAG;
}

void hd44780_command(uint8_t command) {
    while (hd44780_busy())
        ;
    hd44780_write(command, false);
}

void hd44780_data(uint8_t data) {
    while (hd44780_busy())
        ;
    hd44780_write(data, true);
}

void hd44780_clear(void) {
    hd44780_command(HD44780_CMD_CLEAR_DISPLAY);
}

void hd44780_home(void) {
    hd44780_command(HD44780_CMD_RETURN_HOME);
}

void hd44780_on(bool cursor, bool blink) {
    if (cursor) {
        if (blink) {
            hd44780_command(HD44780_CMD_DISPLAY | HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR | HD44780_DISPLAY_BLINK);
        } else {
            hd44780_command(HD44780_CMD_DISPLAY | HD44780_DISPLAY_ON | HD44780_DISPLAY_CURSOR);
        }
    } else {
        hd44780_command(HD44780_CMD_DISPLAY | HD44780_DISPLAY_ON);
    }
}

void hd44780_off() {
    hd44780_command(HD44780_CMD_DISPLAY);
}

void hd44780_set_cgram_address(uint8_t address) {
    hd44780_command(HD44780_CMD_SET_CGRAM_ADDRESS + (address & 0x3F));
}

void hd44780_set_ddram_address(uint8_t address) {
    hd44780_command(HD44780_CMD_SET_DDRAM_ADDRESS + (address & 0x7F));
}

void hd44780_init(bool cursor, bool blink) {
    setPinOutput(HD44780_RS_PIN);
    setPinOutput(HD44780_RW_PIN);
    setPinOutput(HD44780_E_PIN);

    for (int i = 0; i < 4; i++) {
        setPinOutput(data_pins[i]);
    }

    wait_ms(HD44780_INIT_DELAY_MS);

    // Manually configure for 4-bit mode - can't use hd44780_command() yet
    // HD44780U datasheet, Fig. 24 (p46)
    writePinHigh(data_pins[0]); // Function set
    writePinHigh(data_pins[1]); // DL = 1
    hd44780_latch();
    wait_ms(5);
    // Send again
    hd44780_latch();
    wait_us(64);
    // And again (?)
    hd44780_latch();
    wait_us(64);

    writePinLow(data_pins[0]); // DL = 0
    hd44780_latch();
    wait_us(64);

#if HD44780_DISPLAY_LINES == 1
    hd44780_command(HD44780_CMD_FUNCTION); // 4 bit, 1 line, 5x8 dots
#else
    hd44780_command(HD44780_CMD_FUNCTION | HD44780_FUNCTION_2_LINES); // 4 bit, 2 lines, 5x8 dots
#endif
    hd44780_on(cursor, blink);
    hd44780_clear();
    hd44780_home();
    hd44780_command(HD44780_CMD_ENTRY_MODE | HD44780_ENTRY_MODE_INC);
}

void hd44780_set_cursor(uint8_t col, uint8_t line) {
    register uint8_t address = col;

#if HD44780_DISPLAY_LINES == 1
    address += HD44780_DDRAM_LINE0_ADDR;
#elif HD44780_DISPLAY_LINES == 2
    if (line == 0) {
        address += HD44780_DDRAM_LINE0_ADDR;
    } else {
        address += HD44780_DDRAM_LINE1_ADDR;
    }
#endif

    hd44780_set_ddram_address(address);
}

void hd44780_define_char(uint8_t index, uint8_t *data) {
    hd44780_set_cgram_address((index & 0x7) << 3);
    for (uint8_t i = 0; i < 8; i++) {
        hd44780_data(data[i]);
    }
}

void hd44780_putc(char c) {
    while (hd44780_busy())
        ;
    uint8_t current_position = hd44780_read(false);

    if (c == '\n') {
        hd44780_set_cursor(0, current_position < HD44780_DDRAM_LINE1_ADDR ? 1 : 0);
    } else {
#if defined(HD44780_WRAP_LINES)
#    if HD44780_DISPLAY_LINES == 1
        if (current_position == HD44780_DDRAM_LINE0_ADDR + HD44780_DISPLAY_COLS) {
            // Go to start of line
            hd44780_set_cursor(0, 0);
        }
#    elif HD44780_DISPLAY_LINES == 2
        if (current_position == HD44780_DDRAM_LINE0_ADDR + HD44780_DISPLAY_COLS) {
            // Go to start of second line
            hd44780_set_cursor(0, 1);
        } else if (current_position == HD44780_DDRAM_LINE1_ADDR + HD44780_DISPLAY_COLS) {
            // Go to start of first line
            hd44780_set_cursor(0, 0);
        }
#    endif
#endif
        hd44780_data(c);
    }
}

void hd44780_puts(const char *s) {
    register char c;
    while ((c = *s++)) {
        hd44780_putc(c);
    }
}

#if defined(__AVR__)
void hd44780_define_char_P(uint8_t index, const uint8_t *data) {
    hd44780_set_cgram_address(index << 3);
    for (uint8_t i = 0; i < 8; i++) {
        hd44780_data(pgm_read_byte(data++));
    }
}

void hd44780_puts_P(const char *s) {
    register char c;
    while ((c = pgm_read_byte(s++))) {
        hd44780_putc(c);
    }
}
#endif
