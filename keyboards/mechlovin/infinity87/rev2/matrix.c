/* Copyright 2020 Team Mechlovin'
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

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
  //setPinOutput(F0);
  //writePinHigh(F0);

  init_cols();
  init_rows();

  for (uint8_t i=0; i < MATRIX_ROWS; i++)  {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_init_quantum();
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

  matrix_scan_quantum();
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
 * row: 0    1    2    3    4    5
 * pin: PA3  PD5  PC3  PC2  PB3  PB4
 */
static void init_rows(void)
{
  setPinInputHigh(A3);
  setPinInputHigh(D5);
  setPinInputHigh(C3);
  setPinInputHigh(C2);
  setPinInputHigh(B3);
  setPinInputHigh(B4);
}

static uint8_t read_rows()
{
  return ((readPin(A3) ? 0 : (1 << 0)) |
          (readPin(D5) ? 0 : (1 << 1)) |
          (readPin(C3) ? 0 : (1 << 2)) |
          (readPin(C2) ? 0 : (1 << 3)) |
          (readPin(B3) ? 0 : (1 << 4)) |
          (readPin(B4) ? 0 : (1 << 5)));
}

/*
 * Columns 0 - 15, Col16 PC4
 * These columns uses two 74HC138 3 to 8 bit demultiplexers.
 * EN Pin, PD6, PD7
 *
 * col / pin:    PA0  PA1  PA2  PD6  PD7  PC4
 * 0:             0    0    0    1    0    0
 * 1:             0    0    1    1    0    0    
 * 2:             0    1    0    1    0    0  
 * 3:             0    1    1    1    0    0  
 * 4:             1    0    0    1    0    0  
 * 5:             1    0    1    1    0    0  
 * 6:             1    1    0    1    0    0  
 * 7:             1    1    1    1    0    0  
 * 8:             0    0    0    0    1    0  
 * 9:             0    0    1    0    1    0  
 * 10:            0    1    0    0    1    0  
 * 11:            0    1    1    0    1    0  
 * 12:            1    0    0    0    1    0  
 * 13:            1    0    1    0    1    0  
 * 14:            1    1    1    0    1    0  
 * 15:            1    1    0    0    1    0  
 * 16:            0    0    0    0    0    1  
 *
 */
static void init_cols(void)
{
  setPinOutput(A0);
  setPinOutput(A1);
  setPinOutput(A2);

  setPinOutput(C4);

  setPinOutput(D6);
  setPinOutput(D7);

  unselect_cols();
}

static void unselect_cols(void)
{
  writePinLow(D6);
  writePinLow(D7);
  writePinLow(C4);

  writePinHigh(A0);
  writePinHigh(A1);
  writePinHigh(A2);
}

static void select_col(uint8_t col) {

   switch (col) {
        case 0:
          writePinLow(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinHigh(D6);
          break;
        case 1:
          writePinLow(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinHigh(D6);
          break;
        case 2:
          writePinLow(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinHigh(D6);
          break;
        case 3:
          writePinLow(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinHigh(D6);
          break;
        case 4:
          writePinHigh(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinHigh(D6);
          break;
        case 5:
          writePinHigh(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinHigh(D6);
          break;
        case 6:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinHigh(D6);
          break;
        case 7:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinHigh(D6);
          break;
        case 8:
          writePinLow(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinHigh(D7);
          break;
        case 9:
          writePinLow(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinHigh(D7);
          break;
        case 10:
          writePinLow(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinHigh(D7);
          break;
        case 11:
          writePinLow(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinHigh(D7);
          break;
        case 12:
          writePinHigh(A0);
          writePinLow(A1);
          writePinLow(A2);
          writePinHigh(D7);
          break;
        case 13:
          writePinHigh(A0);
          writePinLow(A1);
          writePinHigh(A2);
          writePinHigh(D7);
          break;
        case 14:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinHigh(A2);
          writePinHigh(D7);
          break;
        case 15:
          writePinHigh(A0);
          writePinHigh(A1);
          writePinLow(A2);
          writePinHigh(D7);
          break;
        case 16:
          writePinLow(C4);
          break;
    }
}