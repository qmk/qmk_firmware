#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "hotdox.h"
#include "left.h"

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

  //eeprom_update_word(EECONFIG_MAGIC, 0x0000);

  // initialize matrix state: all keys off
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
    for (uint8_t j=0; j < MATRIX_COLS; ++j) {
      debounce_matrix[i * MATRIX_COLS + j] = 0;
    }
  }

  matrix_init_kb();
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
  left_scan();

  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    select_row(i);
    wait_us(30);  // without this wait read unstable value.
    matrix_row_t mask = debounce_mask(i);
    matrix_row_t cols = (read_cols(i) & mask) | (matrix[i] & ~mask);
    debounce_report(cols ^ matrix[i], i);
    matrix[i] = cols;

    unselect_rows();
  }

  matrix_scan_kb();

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

static void init_cols(void)
{
  // Pro Micro
  gpio_set_pin_input_high(B0);
  gpio_set_pin_input_high(B1);
  gpio_set_pin_input_high(B2);
  gpio_set_pin_input_high(B3);

  gpio_set_pin_input_high(D2);
  gpio_set_pin_input_high(D3);

  gpio_set_pin_input_high(C6);

  left_init();
}

static matrix_row_t read_cols(uint8_t row)
{
  matrix_row_t cols0 = 0x00, cols1 = 0x00;

  cols0 = left_read_cols();

  cols1 = (PINC&(1<<PC6) ? 0 : (1<<(0+7))) |
          (PIND&(1<<PD3) ? 0 : (1<<(1+7))) |
          (PIND&(1<<PD2) ? 0 : (1<<(2+7))) |
          (PINB&(1<<PB3) ? 0 : (1<<(3+7))) |
          (PINB&(1<<PB2) ? 0 : (1<<(4+7))) |
          (PINB&(1<<PB1) ? 0 : (1<<(5+7))) |
          (PINB&(1<<PB0) ? 0 : (1<<(6+7))) ;

  return (cols0 | cols1);
}

static void unselect_rows(void)
{
  // Pro Micro
  gpio_set_pin_input(F0);
  gpio_set_pin_input(F1);
  gpio_set_pin_input(F4);
  gpio_set_pin_input(F5);
  gpio_set_pin_input(F6);
  gpio_set_pin_input(F7);

  left_unselect_rows();
}

static void select_row(uint8_t row)
{
  // Pro Micro
  switch (row) {
  case 5:
    gpio_set_pin_output(F0);
    gpio_write_pin_low(F0);
    break;
  case 4:
    gpio_set_pin_output(F1);
    gpio_write_pin_low(F1);
    break;
  case 3:
    gpio_set_pin_output(F4);
    gpio_write_pin_low(F4);
    break;
  case 2:
    gpio_set_pin_output(F5);
    gpio_write_pin_low(F5);
    break;
  case 1:
    gpio_set_pin_output(F6);
    gpio_write_pin_low(F6);
    break;
  case 0:
    gpio_set_pin_output(F7);
    gpio_write_pin_low(F7);
    break;
  }

  left_select_row(row);
}

