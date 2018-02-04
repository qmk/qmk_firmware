/*
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2017 Erin Call <hello@erincall.com>

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
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "dactyl.h"
#include "i2cmaster.h"
#include "timer.h"


/* Set 0 if debouncing isn't needed */

#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif

#if (DEBOUNCING_DELAY > 0)
    static uint16_t debouncing_time;
    static bool debouncing = false;
#endif

#ifdef MATRIX_MASKED
    extern const matrix_row_t matrix_mask[];
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static void init_rows(void);
static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col);
static void unselect_cols(void);
static void select_col(uint8_t col);
static void unselect_col(uint8_t col);

static uint8_t mcp23018_reset_loop;

#ifdef DEBUG_MATRIX_SCAN_RATE
uint32_t matrix_timer;
uint32_t matrix_scan_count;
#endif

#define ROW_SHIFTER ((matrix_row_t)1)

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    mcp23018_status = init_mcp23018();


    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    matrix_timer = timer_read32();
    matrix_scan_count = 0;
#endif

    matrix_init_quantum();
}

void matrix_power_up(void) {
    mcp23018_status = init_mcp23018();

    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    matrix_timer = timer_read32();
    matrix_scan_count = 0;
#endif
}

uint8_t matrix_scan(void)
{
    if (mcp23018_status) { // if there was an error
        if (++mcp23018_reset_loop == 0) {
            // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            print("trying to reset mcp23018\n");
            mcp23018_status = init_mcp23018();
            if (mcp23018_status) {
                print("left side not responding\n");
            } else {
                print("left side attached\n");
            }
        }
    }

#ifdef DEBUG_MATRIX_SCAN_RATE
    matrix_scan_count++;

    uint32_t timer_now = timer_read32();
    if (TIMER_DIFF_32(timer_now, matrix_timer)>1000) {
        print("matrix scan frequency: ");
        pdec(matrix_scan_count);
        print("\n");

        matrix_timer = timer_now;
        matrix_scan_count = 0;
    }
#endif

    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
#       if (DEBOUNCING_DELAY > 0)
            bool matrix_changed = read_rows_on_col(matrix_debouncing, current_col);

            if (matrix_changed) {
                debouncing = true;
                debouncing_time = timer_read();
            }
#       else
            read_rows_on_col(matrix, current_col);
#       endif

    }

#   if (DEBOUNCING_DELAY > 0)
        if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCING_DELAY)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
            debouncing = false;
        }
#   endif

    matrix_scan_quantum();
    return 1;
}

bool matrix_is_modified(void) // deprecated and evidently not called.
{
#if (DEBOUNCING_DELAY > 0)
    if (debouncing) return false;
#endif
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (ROW_SHIFTER << col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
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

/* Row pin configuration
 *
 * Teensy
 * row: 0   1   2   3   4   5
 * pin: F0  F1  F4  F5  F6  F7
 *
 * MCP23018
 * row: 0   1   2   3   4   5
 * pin: B5  B4  B3  B2  B1  B0
 */
static void init_rows(void)
{
    // init on mcp23018
    // not needed, already done as part of init_mcp23018()

    // init on teensy
    // Input with pull-up(DDR:0, PORT:1)
    DDRF  &= ~(1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<1 | 1<<0);
    PORTF |=  (1<<7 | 1<<6 | 1<<5 | 1<<4 | 1<<1 | 1<<0);
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    uint8_t column_state = 0;

    //select col and wait for selection to stabilize
    select_col(current_col);
    wait_us(30);

    if (current_col < 6) {
        // read rows from mcp23018
        if (mcp23018_status) {
            // it's already in an error state; nothing we can do
            return false;
        }

        mcp23018_status = i2c_start(I2C_ADDR_WRITE); if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(GPIOB);          if (mcp23018_status) goto out;
        mcp23018_status = i2c_start(I2C_ADDR_READ);  if (mcp23018_status) goto out;
        column_state = i2c_readNak();

        out:
            i2c_stop();

        column_state = ~column_state;
    } else {
        // read rows from teensy
        column_state = (
            (PINF&(1<<0) ? 0 : (1<<0)) |
            (PINF&(1<<1) ? 0 : (1<<1)) |
            (PINF&(1<<4) ? 0 : (1<<2)) |
            (PINF&(1<<5) ? 0 : (1<<3)) |
            (PINF&(1<<6) ? 0 : (1<<4)) |
            (PINF&(1<<7) ? 0 : (1<<5)) );
    }

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[current_row];

        if (column_state & (1 << current_row)) {
            // key closed; set state bit in matrix
            current_matrix[current_row] |= (ROW_SHIFTER << current_col);
        } else {
            // key open; clear state bit in matrix
            current_matrix[current_row] &= ~(ROW_SHIFTER << current_col);
        }

        // Determine whether the matrix changed state
        if ((last_row_value != current_matrix[current_row]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    unselect_col(current_col);

    return matrix_changed;
}

/* Column pin configuration
 *
 * Teensy
 * col: 6   7   8   9   10  11
 * pin: B1  B2  B3  D2  D3  C6
 *
 * MCP23018
 * col: 0   1   2   3   4   5
 * pin: A0  A1  A2  A3  A4  A5
 */
static void select_col(uint8_t col)
{
    if (col < 6) {
        // select on mcp23018
        if (mcp23018_status) { // if there was an error
            // do nothing
        } else {
            // set active col low  : 0
            // set other cols hi-Z : 1
            mcp23018_status = i2c_start(I2C_ADDR_WRITE);   if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOA);            if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(0xFF & ~(1<<col)); if (mcp23018_status) goto out;
        out:
            i2c_stop();
        }
    } else {
        // select on teensy
        // Output low(DDR:1, PORT:0) to select
        switch (col) {
            case 6:
                DDRB  |= (1<<1);
                PORTB &= ~(1<<1);
                break;
            case 7:
                DDRB  |= (1<<2);
                PORTB &= ~(1<<2);
                break;
            case 8:
                DDRB  |= (1<<3);
                PORTB &= ~(1<<3);
                break;
            case 9:
                DDRD  |= (1<<2);
                PORTD &= ~(1<<3);
                break;
            case 10:
                DDRD  |= (1<<3);
                PORTD &= ~(1<<3);
                break;
            case 11:
                DDRC  |= (1<<6);
                PORTC &= ~(1<<6);
                break;
        }
    }
}

/* Column pin configuration
 *
 * Teensy
 * col: 6   7   8   9   10  11
 * pin: B1  B2  B3  D2  D3  C6
 *
 * MCP23018
 * col: 0   1   2   3   4   5
 * pin: A0  A1  A2  A3  A4  A5
 */
static void unselect_col(uint8_t col)
{
    if (col < 6) {
        // No need to explicitly unselect mcp23018 pins--their I/O state is
        // set simultaneously, with a single bitmask sent to i2c_write. When
        // select_col selects a single pin, it implicitly unselects all the
        // other ones.
    } else {
        // unselect on teensy
        switch (col) {
            case 6:
                DDRB  &= ~(1<<1);
                PORTB &= ~(1<<1);
                break;
            case 7:
                DDRB  &= ~(1<<2);
                PORTB &= ~(1<<2);
                break;
            case 8:
                DDRB  &= ~(1<<3);
                PORTB &= ~(1<<3);
                break;
            case 9:
                DDRD  &= ~(1<<2);
                PORTD &= ~(1<<2);
                break;
            case 10:
                DDRD  &= ~(1<<3);
                PORTD &= ~(1<<3);
                break;
            case 11:
                DDRC  &= ~(1<<6);
                PORTC &= ~(1<<6);
                break;
        }
    }
}

static void unselect_cols(void)
{
    for(uint8_t x = 0; x < MATRIX_COLS; x++) {
        unselect_col(x);
    }
}

