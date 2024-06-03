/**
 * matrix.c
 *
  Copyright 2020 astro <yuleiz@gmail.com>
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
#include "matrix.h"
#include "print.h"
#include "bitwise.h"
#include "wait.h"

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

static uint8_t debouncing = DEBOUNCE;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static void init_rows(void);
static void init_cols(void);
static void unselect_cols(void);
static void select_col(uint8_t col);


__attribute__ ((weak))
void matrix_init_kb(void)
{
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void)
{
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

void matrix_init(void)
{
  //gpio_set_pin_output(F0);
  //gpio_write_pin_high(F0);
  gpio_set_pin_output(B4);
  gpio_write_pin_low(B4);

  init_cols();
  init_rows();

  for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_init_kb();
}

uint8_t matrix_scan(void)
{
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_col(col);
    _delay_us(3);

    uint8_t rows = read_rows();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
      bool curr_bit = rows & (1<<row);
      if (prev_bit != curr_bit) {
        matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
        debouncing = DEBOUNCE;
      }
    }
    unselect_cols();
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

  matrix_scan_kb();
  return 1;
}

inline matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
  }
}

/*
 * Row pin configuration
 * row: 0    1    2    3    4
 * pin: PE6  PF6  PF7  PB7  PD4
 */
static void init_rows(void)
{
  gpio_set_pin_input_high(E6);
  gpio_set_pin_input_high(F6);
  gpio_set_pin_input_high(F7);
  gpio_set_pin_input_high(B7);
  gpio_set_pin_input_high(D4);
}

static uint8_t read_rows(void)
{
  return ((gpio_read_pin(E6) ? 0 : (1 << 0)) |
          (gpio_read_pin(F6) ? 0 : (1 << 1)) |
          (gpio_read_pin(F7) ? 0 : (1 << 2)) |
          (gpio_read_pin(B7) ? 0 : (1 << 3)) |
          (gpio_read_pin(D4) ? 0 : (1 << 4)));
}

/*
 * Columns 0 - 13
 * These columns uses two 74LVC138 3 to 8 bit demultiplexers.
 * EN Pin, PF5, PD6
 *
 * col / pin:    PF0  PF1  PF4
 * 0:             0    0    0
 * 1:             1    0    0
 * 2:             0    1    0
 * 3:             1    1    0
 * 4:             0    0    1
 * 5:             1    0    1
 * 6:             0    1    1
 *               PD2  PD3  PD5
 * 7:             0    0    0
 * 8:             1    0    0
 * 9:             0    1    0
 * 10:            1    1    0
 * 11:            0    0    1
 * 12:            1    0    1
 * 13:            0    1    1
 *
 */
static void init_cols(void)
{
  gpio_set_pin_output(F0);
  gpio_set_pin_output(F1);
  gpio_set_pin_output(F4);
  gpio_set_pin_output(F5);

  gpio_set_pin_output(D2);
  gpio_set_pin_output(D3);
  gpio_set_pin_output(D5);
  gpio_set_pin_output(D6);

  unselect_cols();
}

static void unselect_cols(void)
{
  gpio_write_pin_high(F0);
  gpio_write_pin_high(F1);
  gpio_write_pin_high(F4);
  gpio_write_pin_high(F5);

  gpio_write_pin_high(D2);
  gpio_write_pin_high(D3);
  gpio_write_pin_high(D5);
  gpio_write_pin_high(D6);
}

static void select_col(uint8_t col) {

   switch (col) {
        case 0:
          gpio_write_pin_low(F0);
          gpio_write_pin_low(F1);
          gpio_write_pin_low(F4);
          break;
        case 1:
          gpio_write_pin_high(F0);
          gpio_write_pin_low(F1);
          gpio_write_pin_low(F4);
          break;
        case 2:
          gpio_write_pin_low(F0);
          gpio_write_pin_high(F1);
          gpio_write_pin_low(F4);
          break;
        case 3:
          gpio_write_pin_high(F0);
          gpio_write_pin_high(F1);
          gpio_write_pin_low(F4);
          break;
        case 4:
          gpio_write_pin_low(F0);
          gpio_write_pin_low(F1);
          gpio_write_pin_high(F4);
          break;
        case 5:
          gpio_write_pin_high(F0);
          gpio_write_pin_low(F1);
          gpio_write_pin_high(F4);
          break;
        case 6:
          gpio_write_pin_low(F0);
          gpio_write_pin_high(F1);
          gpio_write_pin_high(F4);
          break;
        case 7:
          gpio_write_pin_low(D2);
          gpio_write_pin_low(D3);
          gpio_write_pin_low(D5);
          break;
        case 8:
          gpio_write_pin_high(D2);
          gpio_write_pin_low(D3);
          gpio_write_pin_low(D5);
          break;
        case 9:
          gpio_write_pin_low(D2);
          gpio_write_pin_high(D3);
          gpio_write_pin_low(D5);
          break;
        case 10:
          gpio_write_pin_high(D2);
          gpio_write_pin_high(D3);
          gpio_write_pin_low(D5);
          break;
        case 11:
          gpio_write_pin_low(D2);
          gpio_write_pin_low(D3);
          gpio_write_pin_high(D5);
          break;
        case 12:
          gpio_write_pin_high(D2);
          gpio_write_pin_low(D3);
          gpio_write_pin_high(D5);
          break;
        case 13:
          gpio_write_pin_low(D2);
          gpio_write_pin_high(D3);
          gpio_write_pin_high(D5);
          break;
    }
}
