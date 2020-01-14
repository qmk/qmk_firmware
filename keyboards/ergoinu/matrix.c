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
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "split_util.h"

#include "serial.h"

// from pro_micro.h
#define TX_RX_LED_INIT  DDRD |= (1<<5), DDRB |= (1<<0)

#ifndef DISABLE_PROMICRO_LEDs
  #define TXLED0          PORTD |= (1<<5)
  #define TXLED1          PORTD &= ~(1<<5)
  #define RXLED0          PORTB |= (1<<0)
  #define RXLED1          PORTB &= ~(1<<0)
#else
  #define TXLED0
  #define TXLED1
  #define RXLED0
  #define RXLED1
#endif

#ifndef DEBOUNCE
#  define DEBOUNCE	5
#endif

#define ERROR_DISCONNECT_COUNT 5

static uint8_t debouncing = DEBOUNCE;
static const int ROWS_PER_HAND = MATRIX_ROWS/2;
static uint8_t error_count = 0;
uint8_t is_master = 0 ;

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);
static uint8_t matrix_master_scan(void);


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
uint8_t matrix_rows(void) {
  return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
  return MATRIX_COLS;
}

void matrix_init(void) {
  debug_enable = true;
  debug_matrix = true;
  debug_mouse = true;
  // initialize row and col
  unselect_rows();
  init_cols();

  TX_RX_LED_INIT;

  #ifdef DISABLE_PROMICRO_LEDs
    PORTD |= (1<<5);
    PORTB |= (1<<0);
  #endif

  // initialize matrix state: all keys off
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
      matrix[i] = 0;
      matrix_debouncing[i] = 0;
  }

  is_master = has_usb();

  matrix_init_quantum();
}

uint8_t _matrix_scan(void) {
  // Right hand is stored after the left in the matirx so, we need to offset it
  int offset = isLeftHand ? 0 : (ROWS_PER_HAND);

  for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
      select_row(i);
      _delay_us(30);  // without this wait read unstable value.
      matrix_row_t cols = read_cols();
      if (matrix_debouncing[i+offset] != cols) {
          matrix_debouncing[i+offset] = cols;
          debouncing = DEBOUNCE;
      }
      unselect_rows();
  }

  if (debouncing) {
      if (--debouncing) {
          _delay_ms(1);
      } else {
          for (uint8_t i = 0; i < ROWS_PER_HAND; i++) {
              matrix[i+offset] = matrix_debouncing[i+offset];
          }
      }
  }

  return 1;
}

int serial_transaction(void) {
  int slaveOffset = (isLeftHand) ? (ROWS_PER_HAND) : 0;
  int ret=serial_update_buffers();
  if (ret ) {
      if(ret==2)RXLED1;
      return 1;
  }
RXLED0;
  for (int i = 0; i < ROWS_PER_HAND; ++i) {
      matrix[slaveOffset+i] = serial_slave_buffer[i];
  }
  return 0;
}

uint8_t matrix_scan(void) {
  if (is_master) {
    matrix_master_scan();
  }else{
    matrix_slave_scan();

    int offset = (isLeftHand) ? ROWS_PER_HAND : 0;

    for (int i = 0; i < ROWS_PER_HAND; ++i) {
      matrix[offset+i] = serial_master_buffer[i];
    }

    matrix_scan_quantum();
  }
  return 1;
}


uint8_t matrix_master_scan(void) {

  int ret = _matrix_scan();

  int offset = (isLeftHand) ? 0 : ROWS_PER_HAND;

  for (int i = 0; i < ROWS_PER_HAND; ++i) {
    serial_master_buffer[i] = matrix[offset+i];
  }

  if( serial_transaction() ) {
    // turn on the indicator led when halves are disconnected
    TXLED1;

    error_count++;

    if (error_count > ERROR_DISCONNECT_COUNT) {
        // reset other half if disconnected
      int slaveOffset = (isLeftHand) ? (ROWS_PER_HAND) : 0;
      for (int i = 0; i < ROWS_PER_HAND; ++i) {
          matrix[slaveOffset+i] = 0;
      }
    }
  } else {
    // turn off the indicator led on no error
    TXLED0;
    error_count = 0;
  }
  matrix_scan_quantum();
  return ret;
}

void matrix_slave_scan(void) {
  _matrix_scan();

  int offset = (isLeftHand) ? 0 : ROWS_PER_HAND;

  for (int i = 0; i < ROWS_PER_HAND; ++i) {
    serial_slave_buffer[i] = matrix[offset+i];
  }
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

static void  init_cols(void)
{
  for(int x = 0; x < MATRIX_COLS; x++) {
    _SFR_IO8((col_pins[x] >> 4) + 1) &=  ~_BV(col_pins[x] & 0xF);
    _SFR_IO8((col_pins[x] >> 4) + 2) |= _BV(col_pins[x] & 0xF);
  }
}

static matrix_row_t read_cols(void)
{
  matrix_row_t result = 0;
  for(int x = 0; x < MATRIX_COLS; x++) {
    result |= (_SFR_IO8(col_pins[x] >> 4) & _BV(col_pins[x] & 0xF)) ? 0 : (1 << x);
  }
  return result;
}

static void unselect_rows(void)
{
  for(int x = 0; x < ROWS_PER_HAND; x++) {
    _SFR_IO8((row_pins[x] >> 4) + 1) &=  ~_BV(row_pins[x] & 0xF);
    _SFR_IO8((row_pins[x] >> 4) + 2) |= _BV(row_pins[x] & 0xF);
  }
}

static void select_row(uint8_t row)
{
  _SFR_IO8((row_pins[row] >> 4) + 1) |=  _BV(row_pins[row] & 0xF);
  _SFR_IO8((row_pins[row] >> 4) + 2) &= ~_BV(row_pins[row] & 0xF);
}
