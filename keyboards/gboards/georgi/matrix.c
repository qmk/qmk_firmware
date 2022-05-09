/*

Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

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

#include "matrix.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap_steno.h"
#include QMK_KEYBOARD_H

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif

// MCP Pin Defs
#define RROW1 (1<<3)
#define RROW2 (1<<2)
#define RROW3 (1<<1)
#define RROW4 (1<<0)
#define COL0 (1<<0)
#define COL1 (1<<1)
#define COL2 (1<<2)
#define COL3 (1<<3)
#define COL4 (1<<4)
#define COL5 (1<<5)
#define COL6 (1<<6)

// ATmega pin defs
#define ROW1  (1<<6)
#define ROW2  (1<<5)
#define ROW3  (1<<4)
#define ROW4  (1<<1)
#define COL7 (1<<0)
#define COL8 (1<<1)
#define COL9 (1<<2)
#define COL10 (1<<3)
#define COL11 (1<<2)
#define COL12 (1<<3)
#define COL13 (1<<6)


// bit masks
#define BMASK     (COL7 | COL8 | COL9 | COL10)
#define CMASK     (COL13)
#define DMASK     (COL11 | COL12)
#define FMASK     (ROW1 | ROW2 | ROW3 | ROW4)
#define RROWMASK  (RROW1 | RROW2 | RROW3 | RROW4)
#define MCPMASK   (COL0 | COL1 | COL2 | COL3 | COL4 | COL5 | COL6)

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
/*
 * matrix state(1:on, 0:off)
 * contains the raw values without debounce filtering of the last read cycle.
 */
static matrix_row_t raw_matrix[MATRIX_ROWS];

// Debouncing: store for each key the number of scans until it's eligible to
// change.  When scanning the matrix, ignore any changes in keys that have
// already changed in the last DEBOUNCE scans.
static uint8_t debounce_matrix[MATRIX_ROWS * MATRIX_COLS];

static matrix_row_t read_cols(uint8_t row);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;
// static uint16_t mcp23018_reset_loop;

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
    // initialize row and col
    mcp23018_status = init_mcp23018();
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        raw_matrix[i] = 0;
        for (uint8_t j=0; j < MATRIX_COLS; ++j) {
            debounce_matrix[i * MATRIX_COLS + j] = 0;
        }
    }

    matrix_init_quantum();
}

void matrix_power_up(void) {
    mcp23018_status = init_mcp23018();

    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
    }
}

// Returns a matrix_row_t whose bits are set if the corresponding key should be
// eligible to change in this scan.
matrix_row_t debounce_mask(matrix_row_t rawcols, uint8_t row) {
  matrix_row_t result = 0;
  matrix_row_t change = rawcols ^ raw_matrix[row];
  raw_matrix[row] = rawcols;
  for (uint8_t i = 0; i < MATRIX_COLS; ++i) {
    if (debounce_matrix[row * MATRIX_COLS + i]) {
      --debounce_matrix[row * MATRIX_COLS + i];
    } else {
      result |= (1 << i);
    }
    if (change & (1 << i)) {
      debounce_matrix[row * MATRIX_COLS + i] = DEBOUNCE;
    }
  }
  return result;
}

matrix_row_t debounce_read_cols(uint8_t row) {
  // Read the row without debouncing filtering and store it for later usage.
  matrix_row_t cols = read_cols(row);
  // Get the Debounce mask.
  matrix_row_t mask = debounce_mask(cols, row);
  // debounce the row and return the result.
  return (cols & mask) | (matrix[row] & ~mask);;
}

uint8_t matrix_scan(void)
{
  // Then the keyboard
  if (mcp23018_status) { // if there was an error
      if (++mcp23018_reset_loop == 0) {
      // if (++mcp23018_reset_loop >= 1300) {
          // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
          // this will be approx bit more frequent than once per second
          print("trying to reset mcp23018\n");
          mcp23018_status = init_mcp23018();
          if (mcp23018_status) {
              print("left side not responding\n");
          } else {
              print("left side attached\n");
          }
      }
  }

    for (uint8_t i = 0; i < MATRIX_ROWS_PER_SIDE; i++) {
        select_row(i);
        // and select on left hand
        select_row(i + MATRIX_ROWS_PER_SIDE);
        // we don't need a 30us delay anymore, because selecting a
        // left-hand row requires more than 30us for i2c.

        // grab cols from left hand
        matrix[i] = debounce_read_cols(i);
        // grab cols from right hand
        matrix[i + MATRIX_ROWS_PER_SIDE] = debounce_read_cols(i + MATRIX_ROWS_PER_SIDE);

        unselect_rows();
    }

    matrix_scan_quantum();

#ifdef DEBUG_MATRIX
    for (uint8_t c = 0; c < MATRIX_COLS; c++)
		for (uint8_t r = 0; r < MATRIX_ROWS; r++)
		  if (matrix_is_on(r, c)) xprintf("r:%d c:%d \n", r, c);
#endif

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

// Remember this means ROWS
static void  init_cols(void)
{
    // init on mcp23018
    // not needed, already done as part of init_mcp23018()

    // Input with pull-up(DDR:0, PORT:1)
    DDRF  &= ~FMASK;
    PORTF |=  FMASK;
}

static matrix_row_t read_cols(uint8_t row)
{
    if (row < 7) {
        if (mcp23018_status) { // if there was an error
            return 0;
        } else {
            uint8_t data = 0;
            mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);    if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOB, ERGODOX_EZ_I2C_TIMEOUT);             if (mcp23018_status) goto out;
            mcp23018_status = i2c_start(I2C_ADDR_READ, ERGODOX_EZ_I2C_TIMEOUT);     if (mcp23018_status) goto out;
            mcp23018_status = i2c_read_nack(ERGODOX_EZ_I2C_TIMEOUT);                if (mcp23018_status < 0) goto out;
            data = ~((uint8_t)mcp23018_status);
            mcp23018_status = I2C_STATUS_SUCCESS;
        out:
            i2c_stop();

#ifdef DEBUG_MATRIX
            if (data != 0x00) xprintf("I2C: %d\n", data);
#endif
            return data;
        }
    } else {
         /* read from teensy
	        * bitmask is 0b0111001, but we want the lower four
	        * we'll return 1s for the top two, but that's harmless.
	        */
        // So I need to confuckulate all this
        //return ~(((PIND & DMASK) >> 1  | ((PINC & CMASK) >> 6) | (PIN)));
        //return ~((PINF & 0x03) | ((PINF & 0xF0) >> 2));
        return ~(
           (((PINF & ROW4) >> 1)
          | ((PINF & (ROW1 | ROW2 | ROW3)) >> 3))
        & 0xF);
    }
}

// Row pin configuration
static void unselect_rows(void)
{
    // no need to unselect on mcp23018, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRB  &= ~(BMASK);
    PORTB &= ~(BMASK);
    DDRC  &= ~CMASK;
    PORTC &= ~CMASK;
    DDRD  &= ~DMASK;
    PORTD &= ~DMASK;
}

static void select_row(uint8_t row)
{
    if (row < 7) {
        // select on mcp23018
        if (mcp23018_status) { // do nothing on error
        } else { // set active row low  : 0 // set other rows hi-Z : 1
            mcp23018_status = i2c_start(I2C_ADDR_WRITE, ERGODOX_EZ_I2C_TIMEOUT);        if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(GPIOA, ERGODOX_EZ_I2C_TIMEOUT);                 if (mcp23018_status) goto out;
            mcp23018_status = i2c_write(0xFF & ~(1<<row), ERGODOX_EZ_I2C_TIMEOUT);      if (mcp23018_status) goto out;
        out:
            i2c_stop();
        }
    } else {
        // Output low(DDR:1, PORT:0) to select
        switch (row) {
            case 7:
                DDRB  |= COL7;
                PORTB &= ~COL7;
                break;
            case 8:
                DDRB  |= COL8;
                PORTB &= ~COL8;
                break;
            case 9:
                DDRB  |= COL9;
                PORTB &= ~COL9;
                break;
            case 10:
                DDRB  |= COL10;
                PORTB &= ~COL10;
                break;
            case 11:
                DDRD  |= COL11;
                PORTD &= ~COL11;
                break;
            case 12:
                DDRD  |= COL12;
                PORTD &= ~COL12;
                break;
            case 13:
                DDRC  |= COL13;
                PORTC &= ~COL13;
                break;
        }
    }
}
