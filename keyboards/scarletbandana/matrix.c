/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2017 Cole Markham <cole@ccmcomputing.net>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#if defined(__AVR__)
#include <avr/io.h>
#include "pincontrol.h"
#endif
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "config.h"
#include "timer.h"
//#include "audio.h"

#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif

#if (DEBOUNCING_DELAY > 0)
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

static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[4] = MATRIX_COL_PINS;
static const uint8_t xcol_pins[MATRIX_COLS - 16] = MATRIX_XCOL_PINS;
//
//float init_song[][2]     = SONG(QWERTY_SOUND);

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static void init_rows(void);
static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col);
static void unselect_cols(void);
static void init_cols(void);
static void select_col(uint8_t col);
//static void demux_enable(bool enabled);

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
    debug_enable = true;
    debug_matrix = true;
    debug_mouse = true;
    dprintf("matrix init");
    // initialize row and col
    init_cols();
    init_rows();


//    PLAY_NOTE_ARRAY(init_song, false, 0);


    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    matrix_init_quantum();

}

uint8_t _matrix_scan(void)
{
    // Set col, read rows
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

    // Unselect cols
    unselect_cols();

#   if (DEBOUNCING_DELAY > 0)
        if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCING_DELAY)) {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
            debouncing = false;
        }
#   endif

	return 1;
}

uint8_t matrix_scan(void)
{
	uint8_t ret = _matrix_scan();
	matrix_scan_quantum();
	return ret;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
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


static void init_rows(void)
{
    for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
        uint8_t pin = row_pins[x];
        pinMode(pin, PinDirectionInput);
        digitalWrite(pin, PinLevelHigh);
    }
}


static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    // Select col and wait for col selection to stabilize
    select_col(current_col);
    wait_us(30);
//    wait_ms(1000);
//    PLAY_NOTE_ARRAY(init_song, false, 0);

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++)
    {

        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        uint8_t pin = row_pins[row_index];
        if (digitalRead(pin) == 0)
        {
            // Pin LO, set col bit
            current_matrix[row_index] |= (ROW_SHIFTER << current_col);
        }
        else
        {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    return matrix_changed;
}

static void select_col(uint8_t col)
{
  for (uint8_t y = 16; y < MATRIX_COLS; y++) {
    uint8_t pin = xcol_pins[y-16];
    if (y == col) {
      digitalWrite(pin, PinLevelLow);
    } else {
      digitalWrite(pin, PinLevelHigh);
    }
  }
  if (col >= 16) {
//    demux_enable(false);
//    digitalWrite(MATRIX_EN_PIN, PinLevelHigh);
  } else {
    for(uint8_t x = 0; x < 4; x++) {
      uint8_t pin = col_pins[x];
      pinMode(pin, PinDirectionOutput);
      digitalWrite(pin, (col >> x) & 0x1);
    }
//    demux_enable(true);
    digitalWrite(MATRIX_EN_PIN, PinLevelLow);
  }
}

static void init_cols(void) {
  for (uint8_t y = 16; y < MATRIX_COLS; y++) {
      uint8_t pin = xcol_pins[y-16];
      pinMode(pin, PinDirectionOutput);
    }
  for(uint8_t x = 0; x < 4; x++) {
        uint8_t pin = col_pins[x];
        pinMode(pin, PinDirectionOutput);
  }
  pinMode(MATRIX_EN_PIN, PinDirectionOutput);
//  digitalWrite(MATRIX_EN_PIN, PinLevelHigh);
  unselect_cols();
}

static void unselect_cols(void)
{
  for (uint8_t y = 16; y < MATRIX_COLS; y++) {
    uint8_t pin = xcol_pins[y-16];
    digitalWrite(pin, PinLevelHigh);
  }
//  demux_enable(false);
//  digitalWrite(MATRIX_EN_PIN, PinLevelHigh);
}

//static void demux_enable(uint8_t state)
//{
//  if (enabled){
//    digitalWrite(F7, PinLevelLow);
//  } else {
//    digitalWrite(F7, PinLevelHigh);
//  }
//}
