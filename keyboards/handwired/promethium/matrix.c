/*
Copyright 2012 Jun Wako
Copyright 2014 Jack Humbert
Copyright 2017 Priyadi Iman Nurcahyo

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
#    define matrix_bitpop(i)       bitpop(matrix[i])
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop16(matrix[i])
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop32(matrix[i])
#    define ROW_SHIFTER  ((uint32_t)1)
#endif

#ifdef MATRIX_MASKED
    extern const matrix_row_t matrix_mask[];
#endif

static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static const uint8_t tp_pins[3] = TRACKPOINT_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static void init_cols(void);
static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
static void unselect_rows(void);
static void select_row(uint8_t row);
static void unselect_row(uint8_t row);


__attribute__ ((weak))
void matrix_init_kb(void) {
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
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
    // Set row, read cols
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

    matrix_scan_quantum();
    return 1;
}

bool matrix_is_modified(void)
{
#if (DEBOUNCE > 0)
    if (debouncing) return false;
#endif
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)

{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
    // switch blocker installed and the switch is always pressed.
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
        phex(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += matrix_bitpop(i);
    }
    return count;
}


#define ROW_MASK 0b11100000

static const uint8_t row_bit[MATRIX_ROWS] = {
  //  76543210
    0b00000000,
    0b00100000,
    0b01000000,
    0b01100000,
    0b10000000,
    0b10100000,
    0b11000000,
    0b11100000,
};

static void init_cols(void)
{
    // columns
    for(uint8_t x = 0; x < MATRIX_COLS; x++) {
        uint8_t pin = col_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
    }

    // rows
    DDRF  |=  ROW_MASK;
    PORTF &= ~ROW_MASK;

    // trackpoint
    for(uint8_t x = 0; x < 3; x++) {
        uint8_t pin = tp_pins[x];
        _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
        _SFR_IO8((pin >> 4) + 2) |=  _BV(pin & 0xF); // HI
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
    {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[current_row];

        // Clear data in matrix row
        current_matrix[current_row] = 0;

        // special case for trackpoint
        if (current_row == 8) {
            for(uint8_t tp_index = 0; tp_index < 3; tp_index++) {

                // Select the TP pin to read (active low)
                uint8_t pin = tp_pins[tp_index];
                uint8_t pin_state = (_SFR_IO8(pin >> 4) & _BV(pin & 0xF));

                // Populate the matrix row with the state of the col pin
                current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << tp_index);
            }
            return (last_row_value != current_matrix[current_row]);
        }

        // Select row and wait for row selecton to stabilize
        select_row(current_row);
        _delay_us(5);       // without this wait it won't read stable value.
        // wait_us(50);

        // For each col...
        for(uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

            // Select the col pin to read (active low)
            uint8_t pin = col_pins[col_index];
            uint8_t pin_state = (_SFR_IO8(pin >> 4) & _BV(pin & 0xF));

            // Populate the matrix row with the state of the col pin
            current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << col_index);
        }

        // Unselect row
        unselect_row(current_row);

        return (last_row_value != current_matrix[current_row]);
}

static void select_row(uint8_t row)
{
    PORTF = row_bit[row] | (PORTF & ~ROW_MASK);
}

static void unselect_row(uint8_t row)
{
}

static void unselect_rows(void)
{
}
