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

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"

#ifndef DEBOUNCE
#   define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);


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

/* generic STM32F103C8T6 board */
#ifdef BOARD_GENERIC_STM32_F103
#define LED_ON()    do { palClearPad(GPIOB, 1) ;} while (0)
#define LED_OFF()   do { palSetPad(GPIOB, 1); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOB, 1); } while (0)
#endif

/* Maple Mini */
#ifdef BOARD_MAPLEMINI_STM32_F103
#define LED_ON()    do { palSetPad(GPIOB, 1) ;} while (0)
#define LED_OFF()   do { palClearPad(GPIOB, 1); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOB, 1); } while (0)
#endif

void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    //debug
    debug_matrix = true;
    LED_ON();
    wait_ms(500);
    LED_OFF();
}

uint8_t matrix_scan(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        wait_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) {
                debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    if (debouncing) {
        if (--debouncing) {
            wait_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

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
        phex(row); print(": ");
        pbin_reverse16(matrix_get_row(row));
        print("\n");
    }
}

/* Column pin configuration
 */
//  Modified by Xydane
static void  init_cols(void)
{
  palSetPadMode(GPIOA, 6, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 2, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 3, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 7, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_PULLUP);
}

/* Returns status of switches(1:on, 0:off) */
//  Modified by Xydane
static matrix_row_t read_cols(void)
{
  return ((palReadPad(GPIOA, 6)==PAL_HIGH) ? 0 : (1<<0))
    | ((palReadPad(GPIOA, 2)==PAL_HIGH) ? 0 : (1<<1))
    | ((palReadPad(GPIOA, 4)==PAL_HIGH) ? 0 : (1<<2))
    | ((palReadPad(GPIOA, 5)==PAL_HIGH) ? 0 : (1<<3))
    | ((palReadPad(GPIOA, 1)==PAL_HIGH) ? 0 : (1<<4))
    | ((palReadPad(GPIOA, 3)==PAL_HIGH) ? 0 : (1<<5))
    | ((palReadPad(GPIOA, 7)==PAL_HIGH) ? 0 : (1<<6))
    | ((palReadPad(GPIOA, 0)==PAL_HIGH) ? 0 : (1<<7));
}

/* Row pin configuration
 */
//  Modified by Xydane
static void unselect_rows(void)
{
  palSetPadMode(GPIOB, 9, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 8, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 7, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 6, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 5, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 10, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 10, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 11, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 9, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 8, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 15, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 14, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 13, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 12, PAL_MODE_INPUT);
}

//  Modified by Xydane
static void select_row(uint8_t row)
{
    (void)row;
    switch (row) {
    case 0:
      palSetPadMode(GPIOB, 9, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 9);
      break;
    case 1:
      palSetPadMode(GPIOB, 8, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 8);
      break;
    case 2:
      palSetPadMode(GPIOB, 7, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 7);
      break;
    case 3:
      palSetPadMode(GPIOB, 6, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 6);
      break;
    case 4:
      palSetPadMode(GPIOB, 5, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 5);
      break;
    case 5:
      palSetPadMode(GPIOA, 10, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOA, 10);
      break;
    case 6:
      palSetPadMode(GPIOB, 10, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 10);
      break;
    case 7:
      palSetPadMode(GPIOB, 11, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 11);
      break;
    case 8:
      palSetPadMode(GPIOA, 9, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOA, 9);
      break;
    case 9:
      palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOA, 8);
      break;
    case 10:
      palSetPadMode(GPIOB, 15, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 15);
      break;
    case 11:
      palSetPadMode(GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 14);
      break;
    case 12:
      palSetPadMode(GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 13);
      break;
    case 13:
      palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 12);
      break;
    }
}
