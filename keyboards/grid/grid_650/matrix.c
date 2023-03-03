#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
// #include QMK_KEYBOARD_H

#include "config.h"
// #include "i2c_master.h"
#include "grid_650.h"

/*
 * This constant define not debouncing time in msecs, assuming eager_pr.
 *
 * On Ergodox matrix scan rate is relatively low, because of slow I2C.
 * Now it's only 317 scans/second, or about 3.15 msec/scan.
 * According to Cherry specs, debouncing time is 5 msec.
 *
 * However, some switches seem to have higher debouncing requirements, or
 * something else might be wrong. (Also, the scan speed has improved since
 * that comment was written.)
 */

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static matrix_row_t read_cols(uint8_t row);
// static void         init_cols(void);
static void         unselect_rows(void);
static void         select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;
// static uint16_t mcp23018_reset_loop;

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

void matrix_init(void) {
  // initialize row and col

  mcp23018_status = init_mcp23018();

  unselect_rows();
//   init_cols();

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i]     = 0;
    raw_matrix[i] = 0;
  }

  debounce_init(MATRIX_ROWS);
  matrix_init_quantum();
}

void matrix_power_up(void) {
  mcp23018_status = init_mcp23018();

  unselect_rows();
//   init_cols();

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
  }
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_raw_matrix_row(uint8_t index) {
  matrix_row_t temp = read_cols(index);
  if (raw_matrix[index] != temp) {
    raw_matrix[index] = temp;
    return true;
  }
  return false;
}

uint8_t matrix_scan(void) {
  if (mcp23018_status) {  // if there was an error
    if (++mcp23018_reset_loop == 0) {
      // if (++mcp23018_reset_loop >= 1300) {
      // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
      // this will be approx bit more frequent than once per second
      //print("trying to reset mcp23018\n");
      mcp23018_status = init_mcp23018();
      // if (mcp23018_status) {
      //   print("matrix not responding\n");
      // } else {
      //   print("matrix normal\n");
      //   // ergodox_blink_all_leds();

      // }
    }
  }
  bool changed = false;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    //hyk 
    // select rows
    uint8_t index = i;    
    select_row(index);
    
    // we don't need a 30us delay anymore, because selecting a
    // left-hand row requires more than 30us for i2c.

    changed |= store_raw_matrix_row(index);
    
    unselect_rows();
  }

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
  matrix_scan_quantum();

  return 1;
}


bool matrix_is_modified(void)  // deprecated and evidently not called.
{
  return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
  // xprintf("\nr/c 0123456789ABCDEF\n");
  // for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
  //   phex(row);
  //   print(": ");
  //   pbin_reverse16(matrix_get_row(row));
  //   print("\n");
  // }
}

uint8_t matrix_key_count(void) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    count += bitpop16(matrix[i]);
  }
  return count;
}

static matrix_row_t read_cols(uint8_t row) {
    //hyk

    if (mcp23018_status) {  // if there was an error
      return 0;
    } else {
      uint16_t data    = 0;
      // reading GPIOA&GPIOB (column port) since in mcp23018's sequential mode
      
      mcp23018_status = i2c_start(I2C_ADDR_WRITE, I2C_TIMEOUT);
      if (mcp23018_status) goto out;
      mcp23018_status = i2c_write(GPIOA, I2C_TIMEOUT);
      if (mcp23018_status) goto out;
      mcp23018_status = i2c_start(I2C_ADDR_READ, I2C_TIMEOUT);
      if (mcp23018_status) goto out;    
      mcp23018_status = i2c_read_ack(I2C_TIMEOUT);
      if (mcp23018_status < 0) goto out;
      data            = mcp23018_status; //(uint16_t)
      mcp23018_status = i2c_read_nack(I2C_TIMEOUT);
      if (mcp23018_status < 0) goto out;
      data            |= mcp23018_status << 8; //(uint16_t)
      data = ~data;
      mcp23018_status = I2C_STATUS_SUCCESS;
    out:
      i2c_stop();
      return data;
    }
  
}

/* Row pin configuration
 *
 * Atmega32u4
 * row: 0   1   2   3   4   5  
 * pin: F0  F1  F4  F5  F6  F7  
 *
 */
static void unselect_rows(void) {
  //hyk
  //unselect on atmega32u4
  //   Hi-Z(DDR:0, PORT:0) to unselect
  // DDRF &= ~(1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 1 | 1 << 0);
  // PORTF |= 1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 1 | 1 << 0;

  setPinInputHigh(F7);
  setPinInputHigh(F6);
  setPinInputHigh(F5);
  setPinInputHigh(F4);
  setPinInputHigh(F1);
  setPinInputHigh(F0);
}

static void select_row(uint8_t row) {
    //hyk
    // select on atmega32u4
    // Output low(DDR:1, PORT:0) to select
    switch (row) {
      case 0:
        setPinOutput(F0);
        writePinLow(F0);
        break;
      case 1:
        setPinOutput(F1);
        writePinLow(F1);
        break;
      case 2:
        setPinOutput(F4);
        writePinLow(F4);
        break;
      case 3:
        setPinOutput(F5);
        writePinLow(F5);
        break;
      case 4:
        setPinOutput(F6);
        writePinLow(F6);
        break;
      case 5:
        setPinOutput(F7);
        writePinLow(F7);
        break;
      
    }
 
}
