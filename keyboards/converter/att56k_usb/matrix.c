/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2019 engicoder (engicoder@engicoder.com)

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

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <print.h>
#include "debug.h"
#include "matrix.h"
#if defined(ATT56K_USE_ASYNC) || defined(ATT56K_USE_SYNC)
#    include "att56k_if.h"
#else
#    error No protocol defined for ATT56K
#endif

#define DD_LED_INIT() (DDRD |= (1 << PD5))
#define DD_LED_ON() (PORTD &= ~(1 << PD5))
#define DD_LED_OFF() (PORTD |= (1 << PD5))
#define DD_LED_TOGGLE() (PORTD ^= (1 << PD5))

#define TX_LED_INIT() (DDRB |= (1 << PB0))
#define TX_LED_ON() (PORTB &= ~(1 << PB0))
#define TX_LED_OFF() (PORTB |= (1 << PB0))
#define TX_LED_TOGGLE() (PORTB ^= (1 << PB0))

#ifndef DEBOUNCE
#    define DEBOUNCE 0
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

static void        matrix_clear(matrix_row_t*);
static inline void matrix_make(uint8_t row, uint8_t col);
static inline void matrix_break(uint8_t row, uint8_t col);

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

void matrix_setup(void) {
    DD_LED_OFF();
    DD_LED_INIT();

    TX_LED_OFF();
    TX_LED_INIT();

    att56k_init();

    xprintf("ATT 56K converter setup\n");
}

void matrix_init(void) {
    debug_config.enable = true;

    // initialize matrix state: all keys off
    matrix_clear(matrix);

    xprintf("Matrix init\n");
}

#define ROW(pos) (pos >> 4)
#define COL(pos) (pos & 0xF)

uint8_t matrix_scan(void) {
    if (att56k_device_detected()) DD_LED_ON();

    uint8_t scan_code;
    while (att56k_has_data()) {
        scan_code        = att56k_recv();
        bool    is_make  = ((scan_code & (1 << 7)) == 0);
        uint8_t position = (scan_code & 0x7f);
        uint8_t row      = ROW(position);
        uint8_t col      = COL(position);

        xprintf("[%02X:%01X]", position, is_make);

        if (is_make) {
            TX_LED_ON();
            matrix_make(row, col);
        } else {
            TX_LED_OFF();
            matrix_break(row, col);
        }
    }
    return 1;
}

static inline void matrix_make(uint8_t row, uint8_t col) {
    xprintf(" [%X, %X] make\n", row, col);
    matrix[row] |= (1 << col);
}

static inline void matrix_break(uint8_t row, uint8_t col) {
    xprintf(" [%X, %X] break\n", row, col);
    matrix[row] &= ~(1 << col);
}

inline matrix_row_t matrix_get_row(uint8_t row) {
    matrix_row_t value = matrix[row];
    return value;
}

void matrix_print(void) {
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        xprintf("%02X: %16b\n", row, bitrev(matrix_get_row(row)));
    }
}

void matrix_clear(matrix_row_t* matrix) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}
