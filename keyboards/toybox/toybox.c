/* Copyright 2020 sekigon-gonnoc
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
#include "toybox.h"

#include "i2c_master.h"
#include "pointing_device.h"
#include "matrix.h"

#include "mtch6102.h"

#ifndef I2C_TIMEOUT
#    define I2C_TIMEOUT 100
#endif

typedef enum {
    IOEXP_RUN,
    IOEXP_SLEEP1,
    IOEXP_SLEEP2,
} IOEXP_STAT;

typedef struct {
    const uint8_t addr;
    bool          select_all_row;
    uint32_t      last_active_time;
    uint32_t      last_read_time;
    IOEXP_STAT    stat;
} ioexp_t;

static ioexp_t io_left  = {.addr             = ioexp_left_addr,
                          .select_all_row   = false,
                          .last_active_time = 0,
                          .last_read_time   = 0,
                          .stat             = IOEXP_RUN};
static ioexp_t io_right = {.addr             = ioexp_right_addr,
                           .select_all_row   = false,
                           .last_active_time = 0,
                           .last_read_time   = 0,
                           .stat             = IOEXP_RUN};

static TOYBOX_MODE toybox_mode = TOYBOX_INVALID;
static bool        is_touchpad_enabled_;

TOYBOX_MODE get_toybox_mode() { return toybox_mode; }

bool is_touchpad_enabled() { return is_touchpad_enabled_; }
void set_touchpad_enabled(bool enable) { is_touchpad_enabled_ = enable; }

void matrix_scan_kb(void) {
    mtch6102_data_t mtch6102_data;
    report_mouse_t  mouse_rep = {0};
    bool            is_valid  = false;
    static uint32_t cnt;
    static uint32_t last_read_time   = 0;
    static uint32_t last_active_time = 0;

    if (is_touchpad_enabled_) {
        if (timer_elapsed32(last_active_time) < 320 ||
            timer_elapsed32(last_read_time) > 50) {
            is_valid       = read_mtch6102(&mtch6102_data);
            last_read_time = timer_read32();
        }

        if (is_valid) {
            if (mtch6102_data.status & TOUCH) {
                last_active_time = timer_read32();
            }

            bool send_flag = process_mtch6102(&mtch6102_data, &mouse_rep);

            if (send_flag) {
                pointing_device_set_report(mouse_rep);
            }

            if (++cnt % 10 == 0) {
                if (debug_mouse) {
#if defined(__AVR__)
                    dprintf("%d %d %d %d\n", mtch6102_data.status,
                            mtch6102_data.gesture, mtch6102_data.x,
                            mtch6102_data.y);
#else
                    dprintf("0x%02x 0x%02x %d %d\n", mtch6102_data.status,
                            mtch6102_data.gesture, mtch6102_data.x,
                            mtch6102_data.y);
#endif
                }
            }
        }
    }

    matrix_scan_user();
}

void toybox_matrix_init() {
    uint8_t res;
    bool    left  = false;
    bool    right = false;
    i2c_init();

    uint8_t dat = 0;
    res         = i2c_writeReg(ioexp_left_addr, pca9555_output1, &dat, 1, I2C_TIMEOUT);
    left        = res ? false : true;

    res   = i2c_writeReg(ioexp_right_addr, pca9555_output1, &dat, 1, I2C_TIMEOUT);
    right = res ? false : true;

    if (left) {
        toybox_mode |= TOYBOX_LEFT;
    }

    if (right) {
        toybox_mode |= TOYBOX_RIGHT;
    }

    if (check_mtch6102() >= 0x0200) {
        if (init_mtch6102() == 0) {
            is_touchpad_enabled_ = true;
        }
    }
}

#define SET_ROW_PIN(addr, row) \
    i2c_writeReg(addr, pca9555_config1, &row_write[row], 1, I2C_TIMEOUT);

#define READ_COL_PIN(addr, dst) i2c_readReg(addr, pca9555_input0, dst, 1, I2C_TIMEOUT)

uint32_t toybox_matrix_get_row() { return MATRIX_ROWS_DEFAULT; }

uint32_t toybox_matrix_get_col() { return MATRIX_COLS_DEFAULT; }

static uint32_t toybox_scan_ioexp(ioexp_t * const ioexp, matrix_row_t *matrix_raw) {
    uint8_t dat;
    uint32_t res = 0;
    uint8_t row_or = 0;
    if (ioexp->select_all_row) {
        if (timer_elapsed32(ioexp->last_active_time) < 1000 ||
            timer_elapsed32(ioexp->last_read_time) > 50) {
            if (READ_COL_PIN(ioexp->addr, &dat) != 0) {
                // retry once
                if (READ_COL_PIN(ioexp->addr, &dat) != 0) {
                    return 0;
                }
            }

            ioexp->last_read_time = timer_read32();
            if (dat == 0xFF) {
                // no switch is pushed
                for (int idx = 0; idx < toybox_matrix_get_row() / 2; idx++) {
                    matrix_raw[idx] = 0;
                }

                return 0;
            }
        } else {
            // skip read
            for (int idx = 0; idx < toybox_matrix_get_row() / 2; idx++) {
                matrix_raw[idx] = 0;
            }

            return 0;
        }
    }

    for (int idx = 0; idx < toybox_matrix_get_row() / 2; idx++) {
        SET_ROW_PIN(ioexp->addr, idx);
        if (READ_COL_PIN(ioexp->addr, &dat) != 0) {
            // retry once
            if (READ_COL_PIN(ioexp->addr, &dat) != 0) {
                dat = ~matrix_raw[idx];
            }
        }

        dat = ~dat;

        row_or |= dat;

        if (matrix_raw[idx] != dat) {
            res |= 1;
        }
        matrix_raw[idx] = dat;
    }

    if (row_or == 0) {
        // no switch is pushed

        // select all rows
        uint8_t zero = ~0x1F;
        i2c_writeReg(ioexp->addr, pca9555_config1, &zero, 1, I2C_TIMEOUT);
        ioexp->select_all_row = true;
    } else {
        ioexp->last_active_time = timer_read32();

        // unselect all rows
        SET_ROW_PIN(ioexp->addr, sizeof(row_write) - 1);
        ioexp->select_all_row = false;
    }

    return res;
}


uint32_t toybox_matrix_scan(matrix_row_t *matrix_raw) {
    int32_t res = 0;
    uint8_t row = 0;

    if (toybox_mode & TOYBOX_LEFT) {
        res |= toybox_scan_ioexp(&io_left, &matrix_raw[row]);
    }

#if defined(PROTOCOL_NRF)
    const bmp_api_config_t * config = BMPAPI->app.get_config();
    if (config->mode != SPLIT_MASTER) {
        row += toybox_matrix_get_row() / 2;
    }
#else
    row += toybox_matrix_get_row() / 2;
#endif

    if (toybox_mode & TOYBOX_RIGHT) {
        res |= toybox_scan_ioexp(&io_right, &matrix_raw[row]);
    }

    return res;
}

