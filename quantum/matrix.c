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
#if defined(__AVR__)
#include <avr/io.h>
#endif
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"

/* Set 0 if debouncing isn't needed */

#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif
static uint8_t debouncing = DEBOUNCING_DELAY;

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

#if DIODE_DIRECTION == ROW2COL
    static matrix_row_t matrix_reversed[MATRIX_COLS];
    static matrix_row_t matrix_reversed_debouncing[MATRIX_COLS];
#endif

#if MATRIX_COLS > 16
    #define SHIFTER 1UL
#else
    #define SHIFTER 1
#endif

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

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

inline
uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

// void matrix_power_up(void) {
// #if DIODE_DIRECTION == COL2ROW
//     for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
//         /* DDRxn */
//         _SFR_IO8((row_pins[r] >> 4) + 1) |= _BV(row_pins[r] & 0xF);
//         toggle_row(r);
//     }
//     for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
//         /* PORTxn */
//         _SFR_IO8((col_pins[c] >> 4) + 2) |= _BV(col_pins[c] & 0xF);
//     }
// #else
//     for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
//         /* DDRxn */
//         _SFR_IO8((col_pins[c] >> 4) + 1) |= _BV(col_pins[c] & 0xF);
//         toggle_col(c);
//     }
//     for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
//         /* PORTxn */
//         _SFR_IO8((row_pins[r] >> 4) + 2) |= _BV(row_pins[r] & 0xF);
//     }
// #endif
// }

void matrix_init(void) {
    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
    #ifdef __AVR_ATmega32U4__
        MCUCR |= _BV(JTD);
        MCUCR |= _BV(JTD);
    #endif

    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{

#if DIODE_DIRECTION == COL2ROW
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        wait_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCING_DELAY;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            wait_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }
#else
    for (uint8_t i = 0; i < MATRIX_COLS; i++) {
        select_row(i);
        wait_us(30);  // without this wait read unstable value.
        matrix_row_t rows = read_cols();
        if (matrix_reversed_debouncing[i] != rows) {
            matrix_reversed_debouncing[i] = rows;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCING_DELAY;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            wait_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_COLS; i++) {
                matrix_reversed[i] = matrix_reversed_debouncing[i];
            }
        }
    }
    for (uint8_t y = 0; y < MATRIX_ROWS; y++) {
        matrix_row_t row = 0;
        for (uint8_t x = 0; x < MATRIX_COLS; x++) {
            row |= ((matrix_reversed[x] & (1<<y)) >> y) << x;
        }
        matrix[y] = row;
    }
#endif

    matrix_scan_quantum();

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop16(matrix[i]);
    }
    return count;
}

static void init_cols(void)
{
#if DIODE_DIRECTION == COL2ROW
    for(int x = 0; x < MATRIX_COLS; x++) {
        int pin = col_pins[x];
#else
    for(int x = 0; x < MATRIX_ROWS; x++) {
        int pin = row_pins[x];
#endif
        _SFR_IO8((pin >> 4) + 1) &=  ~_BV(pin & 0xF);
        _SFR_IO8((pin >> 4) + 2) |= _BV(pin & 0xF);
    }
}

static matrix_row_t read_cols(void)
{
    matrix_row_t result = 0;

#if DIODE_DIRECTION == COL2ROW
    for(int x = 0; x < MATRIX_COLS; x++) {     
        int pin = col_pins[x];
#else
    for(int x = 0; x < MATRIX_ROWS; x++) {
        int pin = row_pins[x];
#endif
        result |= (_SFR_IO8(pin >> 4) & _BV(pin & 0xF)) ? 0 : (SHIFTER << x);
    }
    return result;
}

static void unselect_rows(void)
{
#if DIODE_DIRECTION == COL2ROW
    for(int x = 0; x < MATRIX_ROWS; x++) { 
        int pin = row_pins[x];
#else
    for(int x = 0; x < MATRIX_COLS; x++) { 
        int pin = col_pins[x];
#endif
        _SFR_IO8((pin >> 4) + 1) &=  ~_BV(pin & 0xF);
        _SFR_IO8((pin >> 4) + 2) |= _BV(pin & 0xF);
    }
}

static void select_row(uint8_t row)
{

#if DIODE_DIRECTION == COL2ROW
    int pin = row_pins[row];
#else
    int pin = col_pins[row];
#endif
    _SFR_IO8((pin >> 4) + 1) |=  _BV(pin & 0xF);
    _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF);
}
