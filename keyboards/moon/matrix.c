// Copyright 2019 Mathias Andersson <wraul@dbox.se>
// SPDX-License-Identifier: GPL-2.0-or-later
#include "matrix.h"
#include "pca9555.h"
#include "wait.h"

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
  pca9555_read_pins(IC2, PCA9555_PORT0, &state_1);
  pca9555_read_pins(IC2, PCA9555_PORT1, &state_2);

  uint16_t state = (((uint16_t)state_1 & PORT0_COLS_MASK) << 3) | (((uint16_t)state_2 & PORT1_COLS_MASK));

  // A low pin indicates an active column
  return (~state) & COLS_MASK;
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
  // Store last value of row prior to reading
  matrix_row_t last_row_value = current_matrix[current_row];

  // Clear data in matrix row
  current_matrix[current_row] = 0;

  // Select row and wait for row selection to stabilize
  select_row(current_row);
  wait_us(30);

  current_matrix[current_row] = read_cols();

  // No need to unselect as `select_row` sets all the pins.

  return (last_row_value != current_matrix[current_row]);
}

void matrix_init_custom(void) {
  pca9555_init(IC1);
  pca9555_init(IC2);

  init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
  bool changed = false;
  for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
    changed |= read_cols_on_row(current_matrix, current_row);
  }
  return changed;
}
