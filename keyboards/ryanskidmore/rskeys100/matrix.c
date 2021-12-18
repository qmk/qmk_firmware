/*
Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>

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

Modified by Ryan Skidmore (@ryanskidmore, rskeys@ryanskidmore.co.uk) to support three shift registers in series.
*/

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "led.h"
#include "config.h"
#include "matrix.h"
#include "quantum.h"

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif


static const uint32_t col_values[24] = SHR_COLS;

static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static void    select_col(uint8_t col);

static void    shift_pulse(void);
static void    shift_out_single(uint8_t value);
static void    shift_out(uint32_t value);

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

void matrix_init(void) {
  setPinInput(ROW_A);
  setPinInput(ROW_B);
  setPinInput(ROW_C);
  setPinInput(ROW_D);
  setPinInput(ROW_E);
  setPinInput(ROW_F);

  setPinOutput(SHR_DATA);
  setPinOutput(SHR_LATCH);
  setPinOutput(SHR_CLOCK);

  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
      matrix[i]            = 0;
      matrix_debouncing[i] = 0;
  }
  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
      select_col(col);
      _delay_us(1);
      uint8_t rows = read_rows();
      for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
          bool prev_bit = ((uint32_t)(matrix_debouncing[row]) & (matrix_row_t)(1UL << col)) ? 1 : 0;
          bool curr_bit = ((uint32_t)rows & (uint32_t)(1UL << row)) ? 1 : 0;
          if (prev_bit != curr_bit) {
              matrix_debouncing[row] = (uint32_t)(matrix_debouncing[row]) ^ (uint32_t)(1UL << col);
              debouncing = DEBOUNCE;
          }
      }
  }

  if (debouncing) {
      if (--debouncing) {
          _delay_ms(1);
      } else {
          for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
              matrix[i] = matrix_debouncing[i];
          }
      }
  }
  matrix_scan_quantum();
  return 1;
}

bool matrix_is_modified(void) {
  if (debouncing)
      return false;
  else
      return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)(1 << col))); }

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {

}

uint8_t matrix_key_count(void) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
      count += bitpop32(matrix[i]);
  }
  return count;
}

static uint8_t read_rows(void) {
  return (readPin(ROW_F) << 5)
         | (readPin(ROW_E) << 4)
         | (readPin(ROW_D) << 3)
         | (readPin(ROW_C) << 2)
         | (readPin(ROW_B) << 1)
         | (readPin(ROW_A) );
}

static inline void shift_pulse(void) {
  writePinHigh(SHR_CLOCK);
  writePinLow(SHR_CLOCK);
}

static void shift_out_single(uint8_t value) {
  for (uint8_t i = 0; i < 8; i++) {
      if (value & 0b10000000) {
          writePinHigh(SHR_DATA);
      } else {
          writePinLow(SHR_DATA);
      }

      shift_pulse();
      value = value << 1;
  }
}

static void shift_out(uint32_t value) {
  writePinLow(SHR_LATCH);
  uint8_t first_byte  = (value >> 16) & 0xFF;
  uint8_t second_byte  = (value >> 8) & 0xFF;
  uint8_t third_byte = (uint8_t)(value & 0xFF);

  shift_out_single(first_byte);
  shift_out_single(second_byte);
  shift_out_single(third_byte);
  writePinHigh(SHR_LATCH);
   /* We delay here to prevent multiple consecutive keys being triggered with a single switch press */
  _delay_us(10);
}

static void select_col(uint8_t col) {
    shift_out(col_values[col]);
}