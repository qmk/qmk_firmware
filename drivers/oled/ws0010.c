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

#include "ws0010.h"
#include "gpio.h"
#include "progmem.h"
#include "wait.h"

#ifndef WS0010_DATA_PINS
#    error ws0010: no data pins defined!
#endif

#ifndef WS0010_RS_PIN
#    error ws0010: no RS pin defined!
#endif

#ifndef WS0010_RW_PIN
#    error ws0010: no R/W pin defined!
#endif

#ifndef WS0010_E_PIN
#    error ws0010: no E pin defined!
#endif

static const pin_t data_pins[4] = WS0010_DATA_PINS;

#ifndef WS0010_DISPLAY_COLS
#    define WS0010_DISPLAY_COLS 16
#endif

#ifndef WS0010_DISPLAY_LINES
#    define WS0010_DISPLAY_LINES 2
#endif

#ifndef WS0010_DDRAM_LINE0_ADDR
#    define WS0010_DDRAM_LINE0_ADDR 0x00
#endif
#ifndef WS0010_DDRAM_LINE1_ADDR
#    define WS0010_DDRAM_LINE1_ADDR 0x40
#endif

#define WS0010_INIT_DELAY_MS 100
#define WS0010_ENABLE_DELAY_US 1
#define WS0010_INIT_NEXT_US 200

static void ws0010_latch(void) {
    gpio_write_pin_high(WS0010_E_PIN);
    wait_us(WS0010_ENABLE_DELAY_US);
    gpio_write_pin_low(WS0010_E_PIN);
}

void ws0010_write(uint8_t data, bool isData) {
    gpio_write_pin(WS0010_RS_PIN, isData);
    gpio_write_pin_low(WS0010_RW_PIN);

    for (int i = 0; i < 4; i++) {
        gpio_set_pin_output(data_pins[i]);
    }

    // Write high nibble
    for (int i = 0; i < 4; i++) {
        gpio_write_pin(data_pins[i], (data >> 4) & (1 << i));
    }
    ws0010_latch();

    // Write low nibble
    for (int i = 0; i < 4; i++) {
        gpio_write_pin(data_pins[i], data & (1 << i));
    }
    ws0010_latch();

    for (int i = 0; i < 4; i++) {
        gpio_write_pin_high(data_pins[i]);
    }
}

uint8_t ws0010_read(bool isData) {
    uint8_t data = 0;

    gpio_write_pin(WS0010_RS_PIN, isData);
    gpio_write_pin_high(WS0010_RW_PIN);

    for (int i = 0; i < 4; i++) {
        gpio_set_pin_input(data_pins[i]);
    }

    gpio_write_pin_high(WS0010_E_PIN);
    wait_us(WS0010_ENABLE_DELAY_US);

    // Read high nibble
    for (int i = 0; i < 4; i++) {
        data |= (gpio_read_pin(data_pins[i]) << i);
    }

    data <<= 4;

    gpio_write_pin_low(WS0010_E_PIN);
    wait_us(WS0010_ENABLE_DELAY_US);
    gpio_write_pin_high(WS0010_E_PIN);
    wait_us(WS0010_ENABLE_DELAY_US);

    // Read low nibble
    for (int i = 0; i < 4; i++) {
        data |= (gpio_read_pin(data_pins[i]) << i);
    }

    gpio_write_pin_low(WS0010_E_PIN);

    return data;
}

bool ws0010_busy(void) {
    return ws0010_read(false) & WS0010_BUSY_FLAG;
}

void ws0010_command(uint8_t command) {
    while (ws0010_busy())
        ;
    ws0010_write(command, false);
}

void ws0010_data(uint8_t data) {
    while (ws0010_busy())
        ;
    ws0010_write(data, true);
}

void ws0010_clear(void) {
    ws0010_command(WS0010_CMD_CLEAR_DISPLAY);
    wait_ms(10);
}

void ws0010_home(void) {
    ws0010_command(WS0010_CMD_RETURN_HOME);
}

void ws0010_on(bool cursor, bool blink) {
    if (cursor) {
        if (blink) {
            ws0010_command(WS0010_CMD_DISPLAY | WS0010_DISPLAY_ON | WS0010_DISPLAY_CURSOR | WS0010_DISPLAY_BLINK);
        } else {
            ws0010_command(WS0010_CMD_DISPLAY | WS0010_DISPLAY_ON | WS0010_DISPLAY_CURSOR);
        }
    } else {
        ws0010_command(WS0010_CMD_DISPLAY | WS0010_DISPLAY_ON);
    }
}

void ws0010_off(void) {
    ws0010_command(WS0010_CMD_DISPLAY);
}

void ws0010_set_cgram_address(uint8_t address) {
    ws0010_command(WS0010_CMD_SET_CGRAM_ADDRESS + (address & 0x3F));
}

void ws0010_set_ddram_address(uint8_t address) {
    ws0010_command(WS0010_CMD_SET_DDRAM_ADDRESS + (address & 0x7F));
}

void ws0010_init(bool cursor, bool blink, bool shift) {
    gpio_set_pin_output(WS0010_RS_PIN);
    gpio_set_pin_output(WS0010_RW_PIN);
    gpio_set_pin_output(WS0010_E_PIN);

    wait_ms(WS0010_INIT_DELAY_MS); // Wait for power stabilization

    // Send WS0010 bus reset commands (needed for warm restarts)
    ws0010_command(0x0);
    wait_us(WS0010_INIT_NEXT_US);
    ws0010_command(0x0);
    wait_us(WS0010_INIT_NEXT_US);
    ws0010_command(0x0);
    wait_us(WS0010_INIT_NEXT_US);
    ws0010_command(0x0);
    wait_us(WS0010_INIT_NEXT_US);
    ws0010_command(0x0);
    wait_us(WS0010_INIT_NEXT_US);

    // There should be some timing inbetween commands but the docs just say check busy inbetween, this is built into the command function.
    ws0010_command(0x2); // 0010 nibble
#if WS0010_DISPLAY_LINES == 1
    ws0010_command(WS0010_CMD_FUNCTION); // 4 bit, 1 line, 5x8 dots
#else
    ws0010_command(WS0010_CMD_FUNCTION | WS0010_FUNCTION_2_LINES); // 4 bit, 2 lines, 5x8 dots
#endif
    ws0010_command(WS0010_CMD_DISPLAY);       // Turn off display
    ws0010_command(WS0010_CMD_CLEAR_DISPLAY); // Clear the display
    if (shift) {
        ws0010_command(WS0010_CMD_ENTRY_MODE | WS0010_ENTRY_MODE_INC | WS0010_ENTRY_MODE_SHIFT); // Set entry mode right to left
    } else {
        ws0010_command(WS0010_CMD_ENTRY_MODE | WS0010_ENTRY_MODE_INC); // Set entry mode left to right
    }
    ws0010_command(WS0010_CMD_RETURN_HOME); // Home command
    // turn on the display and cursor and blink if appliable
    if (cursor) {
        if (blink) {
            ws0010_command(WS0010_CMD_DISPLAY | WS0010_DISPLAY_ON | WS0010_DISPLAY_CURSOR | WS0010_DISPLAY_BLINK);
        } else {
            ws0010_command(WS0010_CMD_DISPLAY | WS0010_DISPLAY_ON | WS0010_DISPLAY_CURSOR);
        }
    } else {
        ws0010_command(WS0010_CMD_DISPLAY | WS0010_DISPLAY_ON);
    }
    // init finished. call init on a soft reset to reset the screen.
}

void ws0010_set_cursor(uint8_t col, uint8_t line) {
    register uint8_t address = col;

#if WS0010_DISPLAY_LINES == 1
    address += WS0010_DDRAM_LINE0_ADDR;
#elif WS0010_DISPLAY_LINES == 2
    if (line == 0) {
        address += WS0010_DDRAM_LINE0_ADDR;
    } else {
        address += WS0010_DDRAM_LINE1_ADDR;
    }
#endif

    ws0010_set_ddram_address(address);
}

void ws0010_define_char(uint8_t index, uint8_t *data) {
    ws0010_set_cgram_address((index & 0x7) << 3);
    for (uint8_t i = 0; i < 8; i++) {
        ws0010_data(data[i]);
    }
}

void ws0010_putc(char c) {
    while (ws0010_busy())
        ;
    uint8_t current_position = ws0010_read(false);

    if (c == '\n') {
        ws0010_set_cursor(0, current_position < WS0010_DDRAM_LINE1_ADDR ? 1 : 0);
    } else {
#if defined(WS0010_WRAP_LINES)
#    if WS0010_DISPLAY_LINES == 1
        if (current_position == WS0010_DDRAM_LINE0_ADDR + WS0010_DISPLAY_COLS) {
            // Go to start of line
            ws0010_set_cursor(0, 0);
        }
#    elif WS0010_DISPLAY_LINES == 2
        if (current_position == WS0010_DDRAM_LINE0_ADDR + WS0010_DISPLAY_COLS) {
            // Go to start of second line
            ws0010_set_cursor(0, 1);
        } else if (current_position == WS0010_DDRAM_LINE1_ADDR + WS0010_DISPLAY_COLS) {
            // Go to start of first line
            ws0010_set_cursor(0, 0);
        }
#    endif
#endif
        ws0010_data(c);
    }
}

void ws0010_puts(const char *s) {
    register char c;
    while ((c = *s++)) {
        ws0010_putc(c);
    }
}

#if defined(__AVR__)
void ws0010_define_char_P(uint8_t index, const uint8_t *data) {
    ws0010_set_cgram_address(index << 3);
    for (uint8_t i = 0; i < 8; i++) {
        ws0010_data(pgm_read_byte(data++));
    }
}

void ws0010_puts_P(const char *s) {
    register char c;
    while ((c = pgm_read_byte(s++))) {
        ws0010_putc(c);
    }
}
#endif
