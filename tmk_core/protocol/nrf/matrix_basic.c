
#include "bmp_matrix.h"
#include "quantum.h"
#include "apidef.h"

static void init_row2col();
static void init_col2row();
static uint32_t get_device_row() { return BMPAPI->app.get_config()->matrix.device_rows; };
static uint32_t get_device_col() { return BMPAPI->app.get_config()->matrix.device_cols; };
static uint32_t scan_row2col();
static uint32_t scan_col2row();

const bmp_matrix_func_t matrix_func_row2col = {init_row2col, get_device_row, get_device_col, scan_row2col};
const bmp_matrix_func_t matrix_func_col2row = {init_col2row, get_device_row, get_device_col, scan_col2row};



//
//// col2row matrix
//
static void unselect_rows(void)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();

  for(int i=0; i<config->matrix.device_rows; i++) {
    BMPAPI->gpio.set_pin(config->matrix.row_pins[i]);
  }
}

static void select_row(uint8_t row)
{
  BMPAPI->gpio.clear_pin(BMPAPI->app.get_config()->matrix.row_pins[row]);
}

static void init_col2row() {
    const bmp_api_config_t *config = BMPAPI->app.get_config();

    for(int i=0; i < config->matrix.device_rows; i++) {
        setPinOd(config->matrix.row_pins[i]);
        writePinHigh(config->matrix.row_pins[i]);
    }

    for(int i=0; i < config->matrix.device_cols; i++) {
        setPinInputHigh(config->matrix.col_pins[i]);
    }
}

static matrix_row_t read_col_pins(void)
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

static matrix_row_t read_row(uint8_t row)
{
  select_row(row);
  matrix_row_t row_state = read_col_pins();
  unselect_rows();
  return row_state;
}

static uint32_t scan_col2row(matrix_row_t *matrix_raw)
{
    const bmp_api_config_t *config = BMPAPI->app.get_config();
    uint8_t matrix_offset = config->matrix.is_left_hand ? 0 :
        config->matrix.rows - get_device_row();
    uint32_t change = 0;

    for (uint8_t i = 0; i < config->matrix.device_rows; i++) {
      matrix_row_t row = read_row(i);
      if (matrix_raw[i + matrix_offset] != row) {
        matrix_raw[i + matrix_offset] = row;
        change = 1;
      }
    }

    return change;
}

//
//// row2col matrix
//
static void select_col(uint8_t col)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  BMPAPI->gpio.clear_pin(config->matrix.col_pins[col]);
}

static void unselect_cols(void)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  for(int i=0; i < config->matrix.device_cols; i++) {
    BMPAPI->gpio.set_pin(config->matrix.col_pins[i]);
  }
}

static matrix_col_t read_row_pins(void)
{
  const bmp_api_config_t *config = BMPAPI->app.get_config();
  matrix_col_t col = 0;

  for (int i=0; i < config->matrix.device_rows; i++) {
    col |= ((BMPAPI->gpio.read_pin(config->matrix.row_pins[i]) ? 0 : 1) << i);
  }
  return col;
}

static matrix_col_t read_col(uint8_t col)
{
  select_col(col);
  matrix_col_t col_state = read_row_pins();
  unselect_cols();
  return col_state;
}

static void init_row2col() {
    const bmp_api_config_t *config = BMPAPI->app.get_config();

    for(int i=0; i < config->matrix.device_rows; i++) {
        setPinInputHigh(config->matrix.row_pins[i]);
    }

    for(int i=0; i < config->matrix.device_cols; i++) {
        setPinOd(config->matrix.col_pins[i]);
        writePinHigh(config->matrix.col_pins[i]);
    }
}

extern matrix_row_t matrix_row2col[];
static matrix_row_t get_row2col_matrix(uint8_t row)
{
  return matrix_row2col[row];
}

static void scan_row2col_matrix(void)
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

static uint32_t scan_row2col(matrix_row_t *matrix_raw)
{
    const bmp_api_config_t *config = BMPAPI->app.get_config();
    uint32_t change = 0;

    uint8_t matrix_offset = config->matrix.is_left_hand ? 0 :
        config->matrix.rows - get_device_row();

    scan_row2col_matrix();
    for (uint8_t i = 0; i < config->matrix.device_rows; i++) {
      matrix_row_t row = get_row2col_matrix(i);
      if (matrix_raw[i + matrix_offset] != row) {
        matrix_raw[i + matrix_offset] = row;
        change = 1;
      }
    }

    return change;
}
