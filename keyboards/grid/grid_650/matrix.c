/* Copyright 2020 grid
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
#include "config.h"
#include "grid_650.h"



/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static matrix_row_t read_cols(uint8_t row);
// static void         init_cols(void);
static void         unselect_rows(void);
static void         select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;
// static uint16_t mcp23018_reset_loop;





void matrix_init_custom(void) {
  // initialize row and col

  mcp23018_status = init_mcp23018();

  unselect_rows();
  // init_cols();

  // initialize matrix state: all keys off
  // for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
  //   matrix[i]     = 0;
  //   raw_matrix[i] = 0;
  // }

  // debounce_init(MATRIX_ROWS);
  // matrix_init_kb();
}

void matrix_power_up(void) {
  mcp23018_status = init_mcp23018();

  unselect_rows();
  // init_cols();

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

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (mcp23018_status) {  // if there was an error
        if (++mcp23018_reset_loop == 0) {
            mcp23018_status = init_mcp23018();

        }
    }

    bool changed = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        // select rows from left and right hands
         uint8_t index = i;    
         select_row(index);

        changed |= store_raw_matrix_row(index);

        unselect_rows();
    }

    return changed;
}


bool matrix_is_modified(void)  // deprecated and evidently not called.
{
  return true;
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
