/*
Copyright 2012 Jun Wako
Copyright 2014 Jack Humbert

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
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"

#ifdef MATRIX_HAS_GHOST
#   error "The universal matrix.c file cannot be used for this keyboard."
#endif

#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
/* matrix state */
#if DIODE_DIRECTION == COL2ROW
static matrix_row_t matrix[MATRIX_ROWS];
#else
static matrix_col_t matrix[MATRIX_COLS];
#endif
static int8_t debouncing_delay = -1;

#if DIODE_DIRECTION == COL2ROW
static void toggle_row(uint8_t row);
static matrix_row_t read_cols(void);
#else
static void toggle_col(uint8_t col);
static matrix_col_t read_rows(void);
#endif

__attribute__ ((weak))
void matrix_init_quantum(void) {
    matrix_init_kb();
}

__attribute__ ((weak))
void matrix_scan_quantum(void) {
    matrix_scan_kb();
}

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

void matrix_power_up(void) {
#if DIODE_DIRECTION == COL2ROW
    for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
        /* DDRxn */
        _SFR_IO8((row_pins[r] >> 4) + 1) |= _BV(row_pins[r] & 0xF);
        toggle_row(r);
    }
    for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
        /* PORTxn */
        _SFR_IO8((col_pins[c] >> 4) + 2) |= _BV(col_pins[c] & 0xF);
    }
#else
    for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
        /* DDRxn */
        _SFR_IO8((col_pins[c] >> 4) + 1) |= _BV(col_pins[c] & 0xF);
        toggle_col(c);
    }
    for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
        /* PORTxn */
        _SFR_IO8((row_pins[r] >> 4) + 2) |= _BV(row_pins[r] & 0xF);
    }
#endif
}

void matrix_init(void) {
    /* frees PORTF by setting the JTD bit twice within four cycles */
    #ifdef __AVR_ATmega32U4__
        MCUCR |= _BV(JTD);
        MCUCR |= _BV(JTD);
    #endif
    /* initializes the I/O pins */
#if DIODE_DIRECTION == COL2ROW
    for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
        /* DDRxn */
        _SFR_IO8((row_pins[r] >> 4) + 1) |= _BV(row_pins[r] & 0xF);
        toggle_row(r);
    }
    for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
        /* PORTxn */
        _SFR_IO8((col_pins[c] >> 4) + 2) |= _BV(col_pins[c] & 0xF);
    }
#else
    for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
        /* DDRxn */
        _SFR_IO8((col_pins[c] >> 4) + 1) |= _BV(col_pins[c] & 0xF);
        toggle_col(c);
    }
    for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
        /* PORTxn */
        _SFR_IO8((row_pins[r] >> 4) + 2) |= _BV(row_pins[r] & 0xF);
    }
#endif
    matrix_init_quantum();
}

#if DIODE_DIRECTION == COL2ROW
uint8_t matrix_scan(void) {
    static matrix_row_t debouncing_matrix[MATRIX_ROWS];
    for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
        toggle_row(r);
        matrix_row_t state = read_cols();
        if (debouncing_matrix[r] != state) {
            debouncing_matrix[r] = state;
            debouncing_delay = DEBOUNCING_DELAY;
        }
        toggle_row(r);
    }
    if (debouncing_delay >= 0) {
        dprintf("Debouncing delay remaining: %X\n", debouncing_delay);
        --debouncing_delay;
        if (debouncing_delay >= 0) {
            wait_ms(1);
        }
        else {
            for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
                matrix[r] = debouncing_matrix[r];
            }
        }
    }
    matrix_scan_quantum();
    return 1;
}

static void toggle_row(uint8_t row) {
    /* PINxn */
    _SFR_IO8((row_pins[row] >> 4)) = _BV(row_pins[row] & 0xF);
}

static matrix_row_t read_cols(void) {
    matrix_row_t state = 0;
    for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
        /* PINxn */
        if (!(_SFR_IO8((col_pins[c] >> 4)) & _BV(col_pins[c] & 0xF))) {
            state |= (matrix_row_t)1 << c;
        }
    }
    return state;
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

#else
uint8_t matrix_scan(void) {
    static matrix_col_t debouncing_matrix[MATRIX_COLS];
    for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
        toggle_col(c);
        matrix_col_t state = read_rows();
        if (debouncing_matrix[c] != state) {
            debouncing_matrix[c] = state;
            debouncing_delay = DEBOUNCING_DELAY;
        }
        toggle_col(c);
    }
    if (debouncing_delay >= 0) {
        dprintf("Debouncing delay remaining: %X\n", debouncing_delay);
        --debouncing_delay;
        if (debouncing_delay >= 0) {
            wait_ms(1);
        }
        else {
            for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
                matrix[c] = debouncing_matrix[c];
            }
        }
    }
    matrix_scan_quantum();
    return 1;
}

static void toggle_col(uint8_t col) {
    /* PINxn */
    _SFR_IO8((col_pins[col] >> 4)) = _BV(col_pins[col] & 0xF);
}

static matrix_col_t read_rows(void) {
    matrix_col_t state = 0;
    for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
        /* PINxn */
        if (!(_SFR_IO8((row_pins[r] >> 4)) & _BV(row_pins[r] & 0xF))) {
            state |= (matrix_col_t)1 << r;
        }
    }
    return state;
}

matrix_row_t matrix_get_row(uint8_t row) {
    matrix_row_t state = 0;
    matrix_col_t mask = (matrix_col_t)1 << row;
    for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
        if (matrix[c] & mask) {
            state |= (matrix_row_t)1 << c;
        }
    }
    return state;
}

#endif

bool matrix_is_modified(void) {
    if (debouncing_delay >= 0) return false;
    return true;
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return matrix_get_row(row) & (matrix_row_t)1 << col;
}

void matrix_print(void) {
    dprintln("Human-readable matrix state:");
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        dprintf("State of row %X: %016b\n", r, bitrev16(matrix_get_row(r)));
    }
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
        count += bitpop16(matrix_get_row(r));
    }
    return count;
}
