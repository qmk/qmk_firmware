#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "ergodone.h"
#include "expander.h"

/*
 * This constant define not debouncing time in msecs, but amount of matrix
 * scan loops which should be made to get stable debounced results.
 *
 * On Ergodox matrix scan rate is relatively low, because of slow I2C.
 * Now it's only 317 scans/second, or about 3.15 msec/scan.
 * According to Cherry specs, debouncing time is 5 msec.
 *
 * And so, there is no sense to have DEBOUNCE higher than 2.
 */

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];

// Debouncing: store for each key the number of scans until it's eligible to
// change.  When scanning the matrix, ignore any changes in keys that have
// already changed in the last DEBOUNCE scans.
static uint8_t debounce_matrix[MATRIX_ROWS * MATRIX_COLS];

static matrix_row_t read_cols(uint8_t row);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

__attribute__ ((weak))
void matrix_init_user(void) {}

__attribute__ ((weak))
void matrix_scan_user(void) {}

__attribute__ ((weak))
void matrix_init_kb(void) {
  matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
  matrix_scan_user();
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
  unselect_rows();
  init_cols();

  // initialize matrix state: all keys off
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    for (uint8_t j=0; j < MATRIX_COLS; ++j) {
      debounce_matrix[i * MATRIX_COLS + j] = 0;
    }
  }

  matrix_init_quantum();
}

void matrix_power_up(void) {
  unselect_rows();
  init_cols();

  // initialize matrix state: all keys off
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
  }
}

// Returns a matrix_row_t whose bits are set if the corresponding key should be
// eligible to change in this scan.
matrix_row_t debounce_mask(uint8_t row) {
  matrix_row_t result = 0;
  for (uint8_t j=0; j < MATRIX_COLS; ++j) {
    if (debounce_matrix[row * MATRIX_COLS + j]) {
      --debounce_matrix[row * MATRIX_COLS + j];
    } else {
      result |= (1 << j);
    }
  }
  return result;
}

// Report changed keys in the given row.  Resets the debounce countdowns
// corresponding to each set bit in 'change' to DEBOUNCE.
void debounce_report(matrix_row_t change, uint8_t row) {
  for (uint8_t i = 0; i < MATRIX_COLS; ++i) {
    if (change & (1 << i)) {
      debounce_matrix[row * MATRIX_COLS + i] = DEBOUNCE;
    }
  }
}

uint8_t matrix_scan(void)
{
  expander_scan();

  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    select_row(i);
    wait_us(30);  // without this wait read unstable value.
    matrix_row_t mask = debounce_mask(i);
    matrix_row_t cols = (read_cols(i) & mask) | (matrix[i] & ~mask);
    debounce_report(cols ^ matrix[i], i);
    matrix[i] = cols;

    unselect_rows();
  }

  matrix_scan_quantum();

  return 1;
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
    print_hex8(row); print(": ");
    print_bin_reverse16(matrix_get_row(row));
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

/* Column pin configuration
 *
 * Pro Micro: 6    5    4    3    2    1    0
 *            PD3  PD2  PD4  PC6  PD7  PE6  PB4
 *
 * Expander:  13   12   11   10   9    8    7
 */
static void  init_cols(void)
{
  // Pro Micro
  DDRE  &= ~(1<<PE6);
  PORTE |=  (1<<PE6);
  DDRD  &= ~(1<<PD2 | 1<<PD3 | 1<<PD4 | 1<<PD7);
  PORTD |=  (1<<PD2 | 1<<PD3 | 1<<PD4 | 1<<PD7);
  DDRC  &= ~(1<<PC6);
  PORTC |=  (1<<PC6);
  DDRB  &= ~(1<<PB4);
  PORTB |=  (1<<PB4);

  // MCP23017
  expander_init();
}

static matrix_row_t read_cols(uint8_t row)
{
  return expander_read_row() |
    (PIND&(1<<PD3) ? 0 : (1<<6)) |
    (PIND&(1<<PD2) ? 0 : (1<<5)) |
    (PIND&(1<<PD4) ? 0 : (1<<4)) |
    (PINC&(1<<PC6) ? 0 : (1<<3)) |
    (PIND&(1<<PD7) ? 0 : (1<<2)) |
    (PINE&(1<<PE6) ? 0 : (1<<1)) |
    (PINB&(1<<PB4) ? 0 : (1<<0)) ;
}

/* Row pin configuration
 *
 * Pro Micro: 0   1   2   3   4   5
 *            F4  F5  F6  F7  B1  B2
 *
 * Expander:  0   1   2   3   4   5
 */
static void unselect_rows(void)
{
  // Pro Micro
  DDRF  &= ~(1<<PF4 | 1<<PF5 | 1<<PF6 | 1<<PF7);
  PORTF &= ~(1<<PF4 | 1<<PF5 | 1<<PF6 | 1<<PF7);
  DDRB  &= ~(1<<PB1 | 1<<PB2);
  PORTB &= ~(1<<PB1 | 1<<PB2);

  // Expander
  expander_unselect_rows();
}

static void select_row(uint8_t row)
{
  // Pro Micro
  switch (row) {
  case 0:
    DDRF  |=  (1<<PF4);
    PORTF &= ~(1<<PF4);
    break;
  case 1:
    DDRF  |=  (1<<PF5);
    PORTF &= ~(1<<PF5);
    break;
  case 2:
    DDRF  |=  (1<<PF6);
    PORTF &= ~(1<<PF6);
    break;
  case 3:
    DDRF  |=  (1<<PF7);
    PORTF &= ~(1<<PF7);
    break;
  case 4:
    DDRB  |=  (1<<PB1);
    PORTB &= ~(1<<PB1);
    break;
  case 5:
    DDRB  |=  (1<<PB2);
    PORTB &= ~(1<<PB2);
    break;
  }

  expander_select_row(row);
}

