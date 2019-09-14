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

#include <stdbool.h>

static uint8_t debouncing = 1;

/* matrix state(1:on, 0:off) */
_Static_assert(sizeof(matrix_row_t)==4, "Invalid row size");
#define DEFAULT_MATRIX_ROWS 32
static matrix_row_t matrix[DEFAULT_MATRIX_ROWS];
static matrix_row_t matrix_dummy[DEFAULT_MATRIX_ROWS];
static matrix_row_t matrix_debouncing[DEFAULT_MATRIX_ROWS];

#define QUEUE_LEN 32
typedef struct {
  ble_switch_state_t* const buf;
  uint8_t ridx, widx, cnt;
  const uint8_t len;
} switch_queue;
ble_switch_state_t rcv_keys_buf[QUEUE_LEN], delay_keys_buf[QUEUE_LEN];

static void init_rows(void);
static void init_cols(void);
void scan_row2col_matrix(void);
matrix_row_t get_row2col_matrix(uint8_t row);
void unselect_cols(void);
void select_col(uint8_t col);
matrix_col_t read_row_pins(void);
matrix_col_t read_col(uint8_t col);
void unselect_rows(void);
void select_row(uint8_t row);
matrix_row_t read_col_pins(void);
matrix_row_t read_row(uint8_t row);

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

#define LED_ON()    do { } while (0)
#define LED_OFF()   do { } while (0)
#define LED_TGL()   do { } while (0)

void matrix_init(void) {
  // initialize row and col

  init_rows();

  if (BMPAPI->app.get_config()->matrix.diode_direction != 0)
  {
    unselect_cols();
  }
  else
  {
    unselect_rows();
  }

  init_cols();
//    NRF_LOG_INFO("matrix init\r\n")

// initialize matrix state: all keys off
  for (uint8_t i = 0; i < DEFAULT_MATRIX_ROWS; i++) {
    matrix[i] = 0;
    matrix_debouncing[i] = 0;
  }

  matrix_init_quantum();
}

__attribute__ ((weak))
uint8_t matrix_scan_impl(matrix_row_t* _matrix){
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  uint8_t matrix_offset = config->matrix.is_left_hand ? 0 :
                                config->matrix.rows - config->matrix.device_rows;
  volatile int matrix_changed = 0;

  if (config->matrix.diode_direction != 0)
  {
    scan_row2col_matrix();
    for (uint8_t i = 0; i < config->matrix.device_rows; i++) {
      matrix_row_t row = get_row2col_matrix(i);
      if (matrix_debouncing[i + matrix_offset] != row) {
        matrix_debouncing[i + matrix_offset] = row;
        debouncing = config->matrix.debounce;
      }
    }
  }
  else
  {
    for (uint8_t i = 0; i < config->matrix.device_rows; i++) {
      matrix_row_t row = read_row(i);
      if (matrix_debouncing[i + matrix_offset] != row) {
        matrix_debouncing[i + matrix_offset] = row;
        debouncing = config->matrix.debounce;
      }
    }
  }

  bmp_api_key_event_t key_state[16];
  matrix_changed = 0;
  if (debouncing) {
    if (--debouncing) {
//            wait_ms(1);
    } else {
      for (uint8_t i = 0; i < config->matrix.device_rows; i++) {
        if (matrix_dummy[i + matrix_offset] != matrix_debouncing[i + matrix_offset]) {
          for (uint8_t j = 0; j < config->matrix.device_cols; j++) {
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
          config->param_central.max_interval/17+1);

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

  return 0;
}

char str[16];

uint8_t matrix_scan(void)
{
  uint8_t res = matrix_scan_impl(matrix);
  matrix_scan_quantum();
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

static void init_rows() {
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  if (config->matrix.diode_direction != 0)
  {
    const bmp_api_gpio_mode_t gpio_conf = {
        .dir = BMP_MODE_INPUT,
        .pull = BMP_PULLUP,
    };
    for(int i=0; i < config->matrix.device_rows; i++) {
      BMPAPI->gpio.set_mode(config->matrix.row_pins[i],
          &gpio_conf);
    }
  }
  else
  {
    const bmp_api_gpio_mode_t gpio_conf = {.dir = BMP_MODE_OUTPUT,
        .pull = BMP_PULL_NONE,
        .drive = BMP_PIN_S0D1
    };
    for(int i=0; i < config->matrix.device_rows; i++) {
      BMPAPI->gpio.set_mode(config->matrix.row_pins[i],
          &gpio_conf);
    }
  }
}
/* Column pin configuration
 */
static void  init_cols(void)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  if (config->matrix.diode_direction != 0)
  {
    const bmp_api_gpio_mode_t gpio_conf = {.dir = BMP_MODE_OUTPUT,
        .pull = BMP_PULL_NONE,
        .drive = BMP_PIN_S0D1
    };
    for(int i=0; i<config->matrix.device_cols; i++) {
      BMPAPI->gpio.set_mode(config->matrix.col_pins[i],
          &gpio_conf);
    }
  }
  else
  {
    const bmp_api_gpio_mode_t gpio_conf = {.dir = BMP_MODE_INPUT,
        .pull = BMP_PULLUP,
    };
    for(int i=0; i < config->matrix.device_cols; i++) {
      BMPAPI->gpio.set_mode( config->matrix.col_pins[i],
          &gpio_conf);
    }
  }
}

matrix_row_t matrix_row2col[DEFAULT_MATRIX_ROWS];
void scan_row2col_matrix(void)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  for (uint8_t i = 0; i < config->matrix.device_cols; i++) {
    matrix_col_t col = read_col(i);
    for (uint8_t j = 0; j < config->matrix.device_rows; j++) {
      uint8_t bit =  (col >> j) & 1;
      if ( bit == 1) {
        matrix_row2col[j] |= (1 << i);
      } else {
        matrix_row2col[j] &= ~(1 << i);
      }
    }
  }
}

matrix_row_t get_row2col_matrix(uint8_t row)
{
  return matrix_row2col[row];
}

/* Returns status of switches(1:on, 0:off) */
matrix_col_t read_row_pins(void)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  matrix_col_t col = 0;

  for (int i=0; i < config->matrix.device_rows; i++) {
    col |= ((BMPAPI->gpio.read_pin(config->matrix.row_pins[i]) ? 0 : 1) << i);
  }
  return col;
}

__attribute__ ((weak))
matrix_col_t read_col(uint8_t col)
{
  select_col(col);
  wait_us(0);
  matrix_col_t col_state = read_row_pins();
  unselect_cols();
  return col_state;
}

void unselect_cols(void)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  for(int i=0; i < config->matrix.device_cols; i++) {
    BMPAPI->gpio.set_pin(config->matrix.col_pins[i]);
  }
}

void select_col(uint8_t col)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  BMPAPI->gpio.clear_pin(config->matrix.col_pins[col]);
}

/* Returns status of switches(1:on, 0:off) */
matrix_row_t read_col_pins(void)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  uint32_t pin_num;
  matrix_row_t row = 0;
  for (int i=0; i < config->matrix.device_cols; i++) {
    pin_num = config->matrix.col_pins[i];
    row |= (BMPAPI->gpio.read_pin(pin_num) ? 0 : 1) << i;
  }
  return row;
}

__attribute__ ((weak))
matrix_row_t read_row(uint8_t row)
{
#if defined(USE_I2C_IOEXPANDER) || defined(USE_SPI_IOEXPANDER)
  return read_row_ioexpander(row);
#else
  select_row(row);
  wait_us(0);
  matrix_row_t row_state = read_col_pins();
  unselect_rows();
  return row_state;
#endif
}

/* Row pin configuration
 */
void unselect_rows(void)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();

  for(int i=0; i<config->matrix.device_rows; i++) {
    BMPAPI->gpio.set_pin(config->matrix.row_pins[i]);
  }
}

void select_row(uint8_t row)
{
  BMPAPI->gpio.clear_pin(BMPAPI->app.get_config()->matrix.row_pins[row]);
}

