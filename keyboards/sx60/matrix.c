/*
Copyright 2012-2017 Jun Wako, Jack Humbert

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
#include "timer.h"
#include "sx60.h"


/* Set 0 if debouncing isn't needed */

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif

#if (DEBOUNCE > 0)
    static uint16_t debouncing_time;
    static bool debouncing = false;
#endif

#if (MATRIX_COLS <= 8)
#    define print_matrix_header()  print("\nr/c 01234567\n")
#    define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#    define ROW_SHIFTER  ((uint32_t)1)
#endif

#ifdef MATRIX_MASKED
    extern const matrix_row_t matrix_mask[];
#endif

static const uint8_t col_pins[ATMEGA_COLS] = MATRIX_COL_PINS;
static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static uint8_t mcp23018_reset_loop;


static void init_cols(void);
static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
static void unselect_rows(void);
static void select_row(uint8_t row);

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

void matrix_init(void) {
    mcp23018_status = true;

    /* initialize row and col */
    unselect_rows();
    init_cols();

    /* initialize matrix state: all keys off */
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    matrix_init_kb();
}

uint8_t matrix_scan(void)
{
    if (mcp23018_status) {
        /* if there was an error */
        if (++mcp23018_reset_loop == 0) {
            /* since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
               this will be approx bit more frequent than once per second */
            print("trying to reset mcp23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                print("left side not responding\n");
            } else {
                print("left side attached\n");
            }
        }
    }

    /* Set row, read cols */
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
#       if (DEBOUNCE > 0)
            bool matrix_changed = read_cols_on_row(matrix_debouncing, current_row);

            if (matrix_changed) {
                debouncing = true;
                debouncing_time = timer_read();
            }
#       else
            read_cols_on_row(matrix, current_row);
#       endif
    }

#   if (DEBOUNCE > 0)
        if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCE)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
            debouncing = false;
        }
#   endif

    matrix_scan_kb();
    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    /* Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
       switch blocker installed and the switch is always pressed. */
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}

void matrix_print(void)
{
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

static void init_cols(void)
{
    for(uint8_t x = 0; x < ATMEGA_COLS; x++) {
        uint8_t pin = col_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); /* IN */
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); /* HI */
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
{
    /* Store last value of row prior to reading */
    matrix_row_t last_row_value = current_matrix[current_row];

    /* Clear data in matrix row */
    current_matrix[current_row] = 0;

    /* Select row and wait for row selecton to stabilize */
    select_row(current_row);
    wait_us(30);

    if (mcp23018_status) {
        /* if there was an error */
        return 0;
    } else {
        uint8_t data = 0;
        mcp23018_status = i2c_readReg(I2C_ADDR, GPIOA, &data, 1, I2C_TIMEOUT);
        if (!mcp23018_status) {
            current_matrix[current_row] |= (~((uint16_t)data) << 8);
        }
    }

    /* For each col... */
    for(uint8_t col_index = 0; col_index < ATMEGA_COLS; col_index++) {
        /* Select the col pin to read (active low) */
        uint8_t pin = col_pins[col_index];
        uint8_t pin_state = (_SFR_IO8(pin >> 4) & _BV(pin & 0xF));

        /* Populate the matrix row with the state of the col pin */
        current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << col_index);
    }

    /* Unselect row */
    unselect_rows();

    return (last_row_value != current_matrix[current_row]);
}

static void select_row(uint8_t row)
{
    if (mcp23018_status) {
        /* if there was an error do nothing */
    } else {
        /* set active row low  : 0
           set active row output : 1
           set other rows hi-Z : 1 */
        uint8_t port = 0xFF & ~(1<<abs(row-4));
        mcp23018_status = i2c_writeReg(I2C_ADDR, GPIOB, &port, 1, I2C_TIMEOUT);
    }

    uint8_t pin = row_pins[row];
    _SFR_IO8((pin >> 4) + 1) |=  _BV(pin & 0xF); /*  OUT  */
    _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); /* LOW  */
}

static void unselect_rows(void)
{
    for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
        uint8_t pin = row_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); /* IN */
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); /* HI */
    }
}
