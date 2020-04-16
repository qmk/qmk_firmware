/*
Copyright 2018 Sekigon

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

#include <stdint.h>
#include <stdlib.h>
/*
 * scan matrix
 */
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "quantum.h"

#include "progmem.h"

#include "app_ble_func.h"
#include "configurator.h"

#include "apidef.h"
#include "i2c.h"
#include "spi.h"
#include "bmp_matrix.h"

#include <stdbool.h>

static uint8_t debouncing = 0;
extern const uint8_t MAINTASK_INTERVAL;

/* matrix state(1:on, 0:off) */
_Static_assert(sizeof(matrix_row_t)==4, "Invalid row size");
#define DEFAULT_MATRIX_ROWS 32
static matrix_row_t matrix[DEFAULT_MATRIX_ROWS];
static matrix_row_t matrix_dummy[DEFAULT_MATRIX_ROWS];
static matrix_row_t matrix_debouncing[DEFAULT_MATRIX_ROWS];
matrix_row_t matrix_row2col[DEFAULT_MATRIX_ROWS];

static const bmp_matrix_func_t *matrix_func;
extern const bmp_matrix_func_t matrix_func_row2col;
extern const bmp_matrix_func_t matrix_func_col2row;
extern const bmp_matrix_func_t matrix_func_row2col_lpme;
extern const bmp_matrix_func_t matrix_func_col2row_lpme;
extern const bmp_matrix_func_t matrix_func_row2col2row;
extern const bmp_matrix_func_t matrix_func_col2row2col;

extern int reset_counter;
#define BOOTPIN 22

__attribute__ ((weak))
void matrix_init_quantum(void) {
    matrix_init_kb();
}

__attribute__ ((weak))
void matrix_scan_quantum(void) {
    matrix_scan_kb();
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

inline
uint8_t matrix_rows(void)
{
    return BMPAPI->app.get_config()->matrix.rows;
}

inline
uint8_t matrix_cols(void)
{
    return BMPAPI->app.get_config()->matrix.cols;
}

__attribute__ ((weak))
const bmp_matrix_func_t * get_matrix_func_user(void) {
    return NULL;
}

void matrix_init(void) {
  // initialize row and col

  matrix_func = get_matrix_func_user();

  if (matrix_func == NULL)
  {
    switch (BMPAPI->app.get_config()->matrix.diode_direction)
    {
        case MATRIX_COL2ROW:
            matrix_func = &matrix_func_col2row;
            break;
        case MATRIX_ROW2COL:
            matrix_func = &matrix_func_row2col;
            break;
        case MATRIX_COL2ROW_LPME:
            matrix_func = &matrix_func_col2row_lpme;
            break;
        case MATRIX_ROW2COL_LPME:
            matrix_func = &matrix_func_row2col_lpme;
            break;
        case MATRIX_COL2ROW2COL:
            matrix_func = &matrix_func_col2row2col;
            break;
        case MATRIX_ROW2COL2ROW:
            matrix_func = &matrix_func_row2col2row;
            break;
        default:
            matrix_func = &matrix_func_row2col;
            break;
    }
  }

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < DEFAULT_MATRIX_ROWS; i++) {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_func->init();

  matrix_init_quantum();

#if defined(BMP_BOOTPIN_AS_RESET)
  setPinInputHigh(BOOTPIN);
#endif
}

__attribute__ ((weak))
uint8_t matrix_scan_impl(matrix_row_t* _matrix){
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  uint8_t matrix_offset = config->matrix.is_left_hand ? 0 :
                                config->matrix.rows - matrix_func->get_device_row();
  volatile int matrix_changed = 0;

  if (matrix_func->scan(matrix_debouncing)) {
    debouncing = config->matrix.debounce;
  }

  bmp_api_key_event_t key_state[16];
  matrix_changed = 0;
  if (debouncing) {
    if (--debouncing) {
//            wait_ms(1);
    } else {
      for (uint8_t i = 0; i < matrix_func->get_device_row(); i++) {
        if (matrix_dummy[i + matrix_offset] != matrix_debouncing[i + matrix_offset]) {
          for (uint8_t j = 0; j < matrix_func->get_device_col(); j++) {
            if ((matrix_dummy[i + matrix_offset]
                ^ matrix_debouncing[i + matrix_offset]) & (1 << j)) {
              key_state[matrix_changed].row = i;
              key_state[matrix_changed].col = j;
              key_state[matrix_changed].state = (matrix_debouncing[i
                  + matrix_offset] >> j) & 1;
              matrix_changed++;
            }
          }
        }
        matrix_dummy[i + matrix_offset] = matrix_debouncing[i + matrix_offset];
      }
    }
  }

  for (int i=0; i<matrix_changed; i++) {
    BMPAPI->app.push_keystate_change(&key_state[i]);
  }

  uint32_t pop_cnt =
      BMPAPI->app.pop_keystate_change(key_state,
          sizeof(key_state)/sizeof(key_state[0]),
          config->param_central.max_interval/MAINTASK_INTERVAL + 3);

  for (uint32_t i=0; i<pop_cnt; i++) {
    if (key_state[i].state == 0)
    {
      _matrix[key_state[i].row] &= ~(1 << key_state[i].col);
    }
    else
    {
      _matrix[key_state[i].row] |= (1 << key_state[i].col);
    }
  }

  return pop_cnt;
}

char str[16];

uint8_t matrix_scan(void)
{
  uint8_t res = matrix_scan_impl(matrix);
  matrix_scan_quantum();

#if defined(BMP_BOOTPIN_AS_RESET)
  if (readPin(BOOTPIN) == 0 && reset_counter < 0)
  {
    reset_counter = 10;
  }
#endif

  return res;
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
}

