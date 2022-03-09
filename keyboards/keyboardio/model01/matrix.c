/* Copyright 2018 James Laird-Wah
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
#include "i2c_master.h"
#include <string.h>
#include "model01.h"

/* If no key events have occurred, the scanners will time out on reads.
 * So we don't want to be too permissive here. */
#define I2C_TIMEOUT     10

static matrix_row_t rows[MATRIX_ROWS];
#define ROWS_PER_HAND (MATRIX_ROWS / 2)

// user-defined overridable functions

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

// helper functions
inline
uint8_t matrix_rows(void) {
  return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
  return MATRIX_COLS;
}

static int i2c_read_hand(int hand) {
  uint8_t buf[5];
  i2c_status_t ret = i2c_receive(I2C_ADDR(hand), buf, sizeof(buf), I2C_TIMEOUT);
  if (ret != I2C_STATUS_SUCCESS)
    return 1;

  if (buf[0] != TWI_REPLY_KEYDATA)
    return 2;

  int start_row = hand ? ROWS_PER_HAND : 0;
  uint8_t *out = &rows[start_row];
  memcpy(out, &buf[1], 4);
  return 0;
}

static int i2c_set_keyscan_interval(int hand, int delay) {
  uint8_t buf[] = {TWI_CMD_KEYSCAN_INTERVAL, delay};
  i2c_status_t ret = i2c_transmit(I2C_ADDR(hand), buf, sizeof(buf), I2C_TIMEOUT);
  return ret;
}

void matrix_init(void) {
  /* Ensure scanner power is on - else right hand will not work */
  DDRC |= _BV(7);
  PORTC |= _BV(7);

  i2c_init();
  i2c_set_keyscan_interval(LEFT, 2);
  i2c_set_keyscan_interval(RIGHT, 2);
  memset(rows, 0, sizeof(rows));

  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
  uint8_t ret = 0;
  ret |= i2c_read_hand(LEFT);
  ret |= i2c_read_hand(RIGHT);
  matrix_scan_quantum();
  return ret;
}

inline
matrix_row_t matrix_get_row(uint8_t row) {
  return rows[row];
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    print_hex8(row); print(": ");
    print_bin_reverse16(matrix_get_row(row));
    print("\n");
  }
}

/* vim: set ts=2 sw=2 et: */
