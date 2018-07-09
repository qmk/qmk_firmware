#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"

#ifndef DEBOUNCING_DELAY
#   define DEBOUNCING_DELAY 5
#endif
static uint8_t debouncing = DEBOUNCING_DELAY;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static uint8_t read_rows(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);

inline uint8_t matrix_rows(void) {
  return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
  return MATRIX_COLS;
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

void matrix_init(void) {
  // initialize row and col
    unselect_cols();
    init_rows();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
  matrix_init_quantum();
}

uint8_t matrix_scan(void) {
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    select_col(col);
    _delay_us(3);
    uint8_t rows = read_rows();
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
      bool curr_bit = rows & (1<<row);
      if (prev_bit != curr_bit) {
        matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
        debouncing = DEBOUNCING_DELAY;
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

bool matrix_is_modified(void) {
  if (debouncing)
    return false;
  else
    return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) {
  return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
  }
}

uint8_t matrix_key_count(void) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    count += bitpop32(matrix[i]);
  }
  return count;
}

/* Row pin configuration
 *
 * row: 0    1    2    3    4    5
 * pin: C7   B1   B2   C6   B4   B5
 *
 */
static void init_rows(void)
{
  DDRC &= ~0b11000000;
  DDRB &= ~0b00110110;
  PORTC |= 0b11000000;
  PORTB |= 0b00110110;
}

static uint8_t read_rows(void) {
  return (PINC&(1<<PC7) ? 0 : (1<<0)) |
    (PINB&(1<<PB1) ? 0 : (1<<1)) |
    (PINB&(1<<PB2) ? 0 : (1<<2)) |
    (PINC&(1<<PC6) ? 0 : (1<<3)) |
    (PINB&(1<<PB4) ? 0 : (1<<4)) |
    (PINB&(1<<PB5) ? 0 : (1<<5));
}

/* Row pin configuration
 * pin:     D3  D7  D6  D5  D4
 * row: off  0   x   x   x   x
 *      0    1   0   0   0   0
 *      1    1   0   0   0   1
 *      2    1   0   0   1   0
 *      3    1   0   0   1   1
 *      4    1   0   1   0   0
 *      5    1   0   1   0   1
 *      6    1   0   1   1   0
 *      7    1   0   1   1   1
 *      8    1   1   0   0   0
 *      9    1   1   0   0   1
 *      10   1   1   0   1   0
 *      11   1   1   0   1   1
 *      12   1   1   1   0   0
 *      13   1   1   1   0   1
 *      14   1   1   1   1   0
 *      15   1   1   1   1   1
 */
static void  unselect_cols(void)
{
  // output high(DDR:1, PORT:1) to unselect
  DDRB  |= (1 << PD3);
  PORTB |= (1 << PD3);
}

static void select_col(uint8_t col) {
  DDRD  |= (1<<PD3 | 1<<PD4 | 1<<PD5 | 1<<PD6 | 1<<PD7);

  PORTD &= ~(1<<PD3);

  if (col & (1<<0)) {
    PORTD |= (1<<PD4);
  }
  else {
    PORTD &= ~(1<<PD4);
  }
  if (col & (1<<1)) {
    PORTD |= (1<<PD5);
  }
  else {
    PORTD &= ~(1<<PD5);
  }
  if (col & (1<<2)) {
    PORTD |= (1<<PD6);
  }
  else {
    PORTD &= ~(1<<PD6);
  }
  if (col & (1<<3)) {
    PORTD |= (1<<PD7);
  }
  else {
    PORTD &= ~(1<<PD7);
  }
}
