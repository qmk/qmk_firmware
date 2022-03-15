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
#include "bmp_debounce.h"

#include <stdbool.h>

extern const uint8_t MAINTASK_INTERVAL;

/* matrix state(1:on, 0:off) */
_Static_assert(sizeof(matrix_row_t) == 4, "Invalid row size");
#define DEFAULT_MATRIX_ROWS 32
static matrix_row_t matrix[DEFAULT_MATRIX_ROWS];
static matrix_row_t matrix_dummy[DEFAULT_MATRIX_ROWS];
static matrix_row_t matrix_debouncing[DEFAULT_MATRIX_ROWS];
matrix_row_t        matrix_row2col[DEFAULT_MATRIX_ROWS];

static const bmp_matrix_func_t *matrix_func;
extern const bmp_matrix_func_t  matrix_func_row2col;
extern const bmp_matrix_func_t  matrix_func_col2row;
extern const bmp_matrix_func_t  matrix_func_row2col_lpme;
extern const bmp_matrix_func_t  matrix_func_col2row_lpme;
extern const bmp_matrix_func_t  matrix_func_row2col2row;
extern const bmp_matrix_func_t  matrix_func_col2row2col;

extern int reset_counter;
#define BOOTPIN 22

__attribute__((weak)) void matrix_init_quantum(void) { matrix_init_kb(); }

__attribute__((weak)) void matrix_scan_quantum(void) { matrix_scan_kb(); }

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

inline uint8_t matrix_rows(void) {
    return BMPAPI->app.get_config()->matrix.rows;
}

inline uint8_t matrix_cols(void) {
    return BMPAPI->app.get_config()->matrix.cols;
}

__attribute__((weak)) const bmp_matrix_func_t *get_matrix_func_user(void) {
    return NULL;
}

void matrix_init(void) {
    // initialize row and col

    bmp_debounce_init();

    matrix_func = get_matrix_func_user();

    if (matrix_func == NULL) {
        switch (BMPAPI->app.get_config()->matrix.diode_direction) {
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
        matrix[i]            = 0;
        matrix_debouncing[i] = 0;
    }

    matrix_func->init();

    matrix_init_quantum();

#if defined(BMP_BOOTPIN_AS_RESET)
    setPinInputHigh(BOOTPIN);
#endif
}

__attribute__((weak)) uint8_t matrix_scan_impl(matrix_row_t *_matrix) {
    const bmp_api_config_t *config     = BMPAPI->app.get_config();
    const uint8_t           device_row = matrix_func->get_device_row();
    const uint8_t           device_col = matrix_func->get_device_col();
    uint8_t                 matrix_offset =
        config->matrix.is_left_hand ? 0 : config->matrix.rows - device_row;
    int matrix_changed = 0;

    uint32_t raw_changed = matrix_func->scan(matrix_debouncing);
    bmp_api_key_event_t key_state[16];
    matrix_changed = bmp_debounce(
        matrix_debouncing + matrix_offset, matrix_dummy + matrix_offset,
        device_row, device_col,
        config->matrix.debounce * MAINTASK_INTERVAL, raw_changed, key_state);

    for (int i = 0; i < matrix_changed; i++) {
        BMPAPI->app.push_keystate_change(&key_state[i]);
    }

    if (debug_config.keyboard && matrix_changed > 0) {
        dprintf("device rows:\n");
        for (uint8_t idx = 0; idx < device_row; idx++) {
            if (config->matrix.cols <= 8) {
                dprintf("\tdr%02d:0x%02x\n", idx,
                        matrix_debouncing[idx + matrix_offset]);
            } else if (config->matrix.cols <= 16) {
                dprintf("\tdr%02d:0x%04x\n", idx,
                        matrix_debouncing[idx + matrix_offset]);
            } else {
                dprintf("\tdr%02d:0x%08x\n", idx,
                        matrix_debouncing[idx + matrix_offset]);
            }
        }
        dprintf("\n");
    }

    uint32_t pop_cnt = BMPAPI->app.pop_keystate_change(
        key_state, sizeof(key_state) / sizeof(key_state[0]),
        config->param_central.max_interval / MAINTASK_INTERVAL + 3);

    for (uint32_t i = 0; i < pop_cnt; i++) {
        if (key_state[i].state == 0) {
            _matrix[key_state[i].row] &= ~(1 << key_state[i].col);
        } else {
            _matrix[key_state[i].row] |= (1 << key_state[i].col);
        }
    }

    if (debug_config.keyboard && pop_cnt > 0) {
        dprintf("matrix rows:\n");
        for (uint8_t idx = 0; idx < device_row; idx++) {
            if (device_col <= 8) {
                dprintf("\tr%02d:0x%02x\n", idx, _matrix[idx]);
            } else if (device_col <= 16) {
                dprintf("\tr%02d:0x%04x\n", idx, _matrix[idx]);
            } else {
                dprintf("\tr%02d:0x%08x\n", idx, _matrix[idx]);
            }
        }
        dprintf("\n");
    }

    return pop_cnt;
}

char str[16];

uint8_t matrix_scan(void) {
    uint8_t res = matrix_scan_impl(matrix);
    matrix_scan_quantum();

#if defined(BMP_BOOTPIN_AS_RESET)
    if (readPin(BOOTPIN) == 0 && reset_counter < 0) {
        reset_counter = 10;
    }
#endif

    return res;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix[row] & ((matrix_row_t)1 << col));
}

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {}
