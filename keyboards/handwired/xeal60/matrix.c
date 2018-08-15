/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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
#include <avr/io.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "split_util.h"
#include "pro_micro.h"
#include "config.h"
#include "timer.h"

#ifdef USE_I2C
# error "Only Serial supported"
#else // USE_SERIAL
#  include "serial.h"
#endif

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
#else
#    error "Currently only supports 8 COLS"
#endif
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

#define ERROR_DISCONNECT_COUNT 5

#define ROWS_PER_HAND (MATRIX_ROWS/2)

static uint8_t error_count = 0;

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

#if (DIODE_DIRECTION == COL2ROW)
static void init_cols(void);
static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
static void unselect_rows(void);
static void select_row(uint8_t row);
static void unselect_row(uint8_t row);
#elif (DIODE_DIRECTION == ROW2COL)
error "Only support Row2Col"
#endif

__attribute__((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
}

__attribute__((weak))
void matrix_init_user(void) {
}

__attribute__((weak))
void matrix_scan_user(void) {
}

__attribute__((weak))
void matrix_slave_scan_user(void) {
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

//Returns first row for the *other* hand, so 0 for left, Rows_PER_HAND for right hand
inline
uint8_t other_hand_row_offset(void)
{
  return (isLeftHand) ? (ROWS_PER_HAND) : 0;
}

inline
uint8_t my_hand_row_offset(void)
{
  return (isLeftHand) ? 0 : ROWS_PER_HAND;
}

void matrix_init(void)
{
#ifdef DISABLE_JTAG
  // JTAG disable for PORT F. write JTD bit twice within four cycles.
  MCUCR |= (1 << JTD);
  MCUCR |= (1 << JTD);
#endif

  debug_enable = true;
  debug_matrix = true;
  debug_mouse = true;
  // initialize row and col

  unselect_rows();
  init_cols();

  TX_RX_LED_INIT;

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_init_quantum();

}

uint8_t _matrix_scan(void)
{
  uint8_t offset = my_hand_row_offset();

  // Set row, read cols
  for (uint8_t current_row = 0; current_row < ROWS_PER_HAND; current_row++) {
#   if (DEBOUNCING_DELAY > 0)
    bool matrix_changed = read_cols_on_row(matrix_debouncing + offset, current_row);

    if (matrix_changed) {
      debouncing = true;
      debouncing_time = timer_read();
    }
#   else
    read_cols_on_row(matrix + offset, current_row);
#   endif

  }

#   if (DEBOUNCING_DELAY > 0)
  if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCING_DELAY)) {
    for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
      matrix[i + offset] = matrix_debouncing[i + offset];
    }
    debouncing = false;
  }
#   endif

  return 1;
}



int serial_transaction(void) {
  int slaveOffset = (isLeftHand) ? (ROWS_PER_HAND) : 0;

  if (serial_update_buffers()) {
    return 1;
  }

  for (uint8_t i = 0; i < ROWS_PER_HAND; ++i) {
    matrix[slaveOffset + i] = serial_slave_buffer[i];
  }
  return 0;
}



uint8_t matrix_scan(void)
{
  uint8_t ret = _matrix_scan();

  if (serial_transaction()) {
    // turn on the indicator led when halves are disconnected
    TXLED1;

    error_count++;

    if (error_count > ERROR_DISCONNECT_COUNT) {
      // reset other half if disconnected
      int offset = other_hand_row_offset();
      for (uint8_t i = 0; i < ROWS_PER_HAND; ++i) {
        matrix[offset + i] = 0;
      }
    }
  }
  else {
    // turn off the indicator led on no error
    TXLED0;
    error_count = 0;
  }
  matrix_scan_quantum();
  return ret;
}

void matrix_slave_scan(void) {
  _matrix_scan();

  int offset = my_hand_row_offset();

  for (uint8_t i = 0; i < ROWS_PER_HAND; ++i) {
    serial_slave_buffer[i] = matrix[offset + i];
  }

  matrix_slave_scan_user();
}

bool matrix_is_modified(void)
{
  if (debouncing) return false;
  return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
  return (matrix[row] & ((matrix_row_t)1 << col));
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

static void init_cols(void)
{
  for (uint8_t x = 0; x < MATRIX_COLS; x++) {
    uint8_t pin = col_pins[x];
    _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
    _SFR_IO8((pin >> 4) + 2) |= _BV(pin & 0xF); // HI
  }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
{
  // Store last value of row prior to reading
  matrix_row_t last_row_value = current_matrix[current_row];

  // Clear data in matrix row
  current_matrix[current_row] = 0;

  // Select row and wait for row selecton to stabilize
  select_row(current_row);
  wait_us(30);

  // For each col...
  for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

    // Select the col pin to read (active low)
    uint8_t pin = col_pins[col_index];
    uint8_t pin_state = (_SFR_IO8(pin >> 4) & _BV(pin & 0xF));

    // Populate the matrix row with the state of the col pin
    current_matrix[current_row] |= pin_state ? 0 : (ROW_SHIFTER << col_index);
  }

  // Unselect row
  unselect_row(current_row);

  return (last_row_value != current_matrix[current_row]);
}

static void select_row(uint8_t row)
{
  uint8_t pin = row_pins[row];
  _SFR_IO8((pin >> 4) + 1) |= _BV(pin & 0xF); // OUT
  _SFR_IO8((pin >> 4) + 2) &= ~_BV(pin & 0xF); // LOW
}

static void unselect_row(uint8_t row)
{
  uint8_t pin = row_pins[row];
  _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
  _SFR_IO8((pin >> 4) + 2) |= _BV(pin & 0xF); // HI
}

static void unselect_rows(void)
{
  for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
    uint8_t pin = row_pins[x];
    _SFR_IO8((pin >> 4) + 1) &= ~_BV(pin & 0xF); // IN
    _SFR_IO8((pin >> 4) + 2) |= _BV(pin & 0xF); // HI
  }
}
