/*
Copyright 2012-2019 Jun Wako, Jack Humbert, Yiancar, Mathias Andersson <wraul@dbox.se>

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
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "pca9555.h"

/*
 *       IC1 (PCA9555)                  IC2 (PCA9555)
 *       ,----------.                   ,----------.
 * SDA --| SDA  P00 |-- P1        SDA --| SDA  P00 |-- P17
 * SCL --| SCL  P01 |-- P2        SCL --| SCL  P01 |-- P18
 * INT --| INT  P02 |-- P3        INT --| INT  P02 |-- P19
 *       |      P03 |-- P4              |      P03 |-- P20
 * GND --| A0   P04 |-- P5        VCC --| A0   P04 |-- P21
 * SJ1 --| A1   P05 |-- P6        SJ1 --| A1   P05 |-- P22
 * GND --| A2   P06 |-- P7        GND --| A2   P06 |-- P23
 *       |      P07 |-- P8              |      P07 |-- P24
 *       |          |                   |          |
 *       |      P10 |-- P9              |      P10 |-- P25
 *       |      P11 |-- P10             |      P11 |-- P26
 *       |      P12 |-- P11             |      P12 |-- P27
 *       |      P13 |-- P12             |      P13 |-- P28
 *       |      P14 |-- P13             |      P14 |-- P29
 *       |      P15 |-- P14             |      P15 |-- P30
 *       |      P16 |-- P15             |      P16 |-- P31
 *       |      P17 |-- P16             |      P17 |-- P32
 *       `----------'                   `----------'
 */

/*
 * | Row | Pin |   | Col | Pin |
 * | --- | --- |   | --- | --- |
 * | 0   | P1  |   | 0   | P25 |
 * | 1   | P2  |   | 1   | P26 |
 * | 2   | P3  |   | 2   | P27 |
 * | 3   | P4  |   | 3   | P28 |
 * | 4   | P5  |   | 4   | P29 |
 * | 5   | P6  |   | 5   | P30 |
 * | 6   | P7  |   | 6   | P20 |
 * | 7   | P8  |   | 7   | P21 |
 *                 | 8   | P22 |
 *                 | 9   | P23 |
 *                 | A   | P24 |
 */

// PCA9555 slave addresses
#define IC1 0x20
#define IC2 0x21

// PCA9555 column pin masks
#define PORT0_COLS_MASK 0b11111000
#define PORT1_COLS_MASK 0b00111111
#define COLS_MASK 0b0000011111111111

#if (MATRIX_COLS <= 8)
#  define print_matrix_header() print("\nr/c 01234567\n")
#  define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))
#  define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#  define print_matrix_header() print("\nr/c 0123456789ABCDEF\n")
#  define print_matrix_row(row) print_bin_reverse16(matrix_get_row(row))
#  define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#  define print_matrix_header() print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#  define print_matrix_row(row) print_bin_reverse32(matrix_get_row(row))
#  define ROW_SHIFTER ((uint32_t)1)
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values

__attribute__((weak)) void matrix_init_quantum(void) { matrix_init_kb(); }

__attribute__((weak)) void matrix_scan_quantum(void) { matrix_scan_kb(); }

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
  print_matrix_header();

  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    print_hex8(row);
    print(": ");
    print_matrix_row(row);
    print("\n");
  }
}

static void init_i2c(void) {
  pca9555_init(IC1);
  pca9555_init(IC2);
}

static void init_pins(void) {
  // init cols - IC2 port0 & IC2 port1 input
  pca9555_set_config(IC2, PCA9555_PORT0, ALL_INPUT);
  pca9555_set_config(IC2, PCA9555_PORT1, ALL_INPUT);

  // init rows - IC1 port0 output
  pca9555_set_config(IC1, PCA9555_PORT0, ALL_OUTPUT);
  pca9555_set_output(IC1, PCA9555_PORT0, ALL_HIGH);
}

static void select_row(uint8_t row) {
  // All rows are on the same IC and port
  uint8_t mask = 1 << row;

  // set active row low  : 0
  // set other rows hi-Z : 1
  pca9555_set_output(IC1, PCA9555_PORT0, ALL_HIGH & (~mask));
}

static uint16_t read_cols(void) {
  uint8_t state_1 = 0;
  uint8_t state_2 = 0;
  pca9555_readPins(IC2, PCA9555_PORT0, &state_1);
  pca9555_readPins(IC2, PCA9555_PORT1, &state_2);

  uint16_t state = (((uint16_t)state_1 & PORT0_COLS_MASK) << 3) | (((uint16_t)state_2 & PORT1_COLS_MASK));

  // A low pin indicates an active column
  return (~state) & COLS_MASK;
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
  // Store last value of row prior to reading
  matrix_row_t last_row_value = current_matrix[current_row];

  // Clear data in matrix row
  current_matrix[current_row] = 0;

  // Select row and wait for row selecton to stabilize
  select_row(current_row);
  wait_us(30);

  current_matrix[current_row] |= read_cols();

  // No need to unselect as `select_row` sets all the pins.

  return (last_row_value != current_matrix[current_row]);
}

void matrix_init(void) {
  // initialize i2c
  init_i2c();

  // initialize key pins
  init_pins();

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    raw_matrix[i] = 0;
    matrix[i]     = 0;
  }

  debounce_init(MATRIX_ROWS);

  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
  bool changed = false;

  for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
    changed |= read_cols_on_row(raw_matrix, current_row);
  }

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

  matrix_scan_quantum();

  return (uint8_t)changed;
}
