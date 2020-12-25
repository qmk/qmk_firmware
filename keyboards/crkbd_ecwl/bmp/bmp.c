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

#include <string.h>

#include "crkbd_ecwl.h"
#include "quantum.h"
#include "bmp_matrix.h"
#include "bmp.h"

#include "debug.h"
#include "i2c_master.h"

#include "apidef.h"
#include "debug.h"

#define POWER_PIN 11
#define APLEX_EN_PIN 10
#define OPA_SHDN_PIN 20
#define ANALOG_PORT 6
#define DISCHARGE_PIN 16
const uint8_t row_pins[] = {7, 8, 9};
const uint8_t col_pins[] = {15, 14, 13};
const uint8_t col_sels[] = {6, 4, 3, 0, 1, 2, 5};

// Switch scan threthold
#define ERROR_TH 3000
#define HIGH_TH 1000
#define LOW_TH 800

// Sleep count threthold(x17ms)
#define STANBY_COUNT (10 * 1000 / 17)         // 10sec
#define SCAN_RATE_STANBY (2)                  // 2count
#define SCAN_RATE_DEEP_SLEEP (1 * 1000 / 17)  // 1sec

typedef enum {
    SCAN_MODE_ACTIVE,
    SCAN_MODE_STANBY,
    SCAN_MODE_DEEP_SLEEP,
} scan_mode_t;

static scan_mode_t scan_mode = SCAN_MODE_ACTIVE;

#define LEN(x) (sizeof(x) / sizeof(x[0]))

bool bmp_config_overwrite(bmp_api_config_t const *const config_on_storage,
                          bmp_api_config_t *const       keyboard_config) {
    // User can overwrite partial settings
    keyboard_config->mode            = config_on_storage->mode;
    keyboard_config->startup         = config_on_storage->startup;
    keyboard_config->matrix.debounce = config_on_storage->matrix.debounce;
    keyboard_config->matrix.is_left_hand =
        config_on_storage->matrix.is_left_hand;
    keyboard_config->param_central    = config_on_storage->param_central;
    keyboard_config->param_peripheral = config_on_storage->param_peripheral;
    keyboard_config->keymap           = config_on_storage->keymap;
    keyboard_config->reserved[2]      = config_on_storage->reserved[2];

    return true;
}

void keyboard_post_init_kb() {
    debug_enable   = false;
    debug_keyboard = false;
    debug_mouse    = false;
}

const bmp_ecs_config_t ecs_config = {.pins          = row_pins,
                                     .cnt           = LEN(row_pins),
                                     .adc_port      = ANALOG_PORT,
                                     .shdn_pin      = OPA_SHDN_PIN,
                                     .discharge_pin = DISCHARGE_PIN};

void ecs_matrix_init() {
    // init driver
    BMPAPI->ecs.init(&ecs_config);

    // init col_pins
    for (int idx = 0; idx < LEN(col_pins); idx++) {
        setPinOutput(col_pins[idx]);
        writePinLow(col_pins[idx]);
    }

    // power_on
    setPinOutput(POWER_PIN);
    writePinHigh(POWER_PIN);

    // enable multiplexer
    setPinOutput(APLEX_EN_PIN);
    writePinLow(APLEX_EN_PIN);
}

uint16_t sw_read[32] = {0};
uint32_t ecs_get_device_row() { return MATRIX_ROWS_DEFAULT; }
uint32_t ecs_get_device_col() { return MATRIX_COLS_DEFAULT; }
uint32_t ecs_matrix_scan(matrix_row_t *matrix_raw) {
    static uint32_t sleep_count = 0;
    uint16_t        sw_idx      = 0;

    if (scan_mode == SCAN_MODE_DEEP_SLEEP) {
        if (sleep_count % SCAN_RATE_DEEP_SLEEP == SCAN_RATE_DEEP_SLEEP - 1) {
            sleep_count++;
            BMPAPI->ecs.schedule_next_scan();
            return 0;
        } else if (sleep_count % SCAN_RATE_DEEP_SLEEP != 0) {
            sleep_count++;
            BMPAPI->ecs.shutdown_amp();
            return 0;
        }
    } else if (scan_mode == SCAN_MODE_STANBY) {
        if (sleep_count % SCAN_RATE_STANBY == SCAN_RATE_STANBY - 1) {
            sleep_count++;
            BMPAPI->ecs.schedule_next_scan();
            return 0;
        } else if (sleep_count % SCAN_RATE_STANBY != 0) {
            sleep_count++;
            BMPAPI->ecs.shutdown_amp();
            return 0;
        }
    }

    for (int col_sel_idx = 0; col_sel_idx < LEN(col_sels); col_sel_idx++) {
        BMPAPI->ecs.discharge_capacitor();

        writePinHigh(APLEX_EN_PIN);
        // select col
        for (int col_pin_idx = 0; col_pin_idx < LEN(col_pins); col_pin_idx++) {
            writePin(col_pins[col_pin_idx],
                     col_sels[col_sel_idx] & (1 << col_pin_idx) ? 1 : 0);
        }
        writePinLow(APLEX_EN_PIN);

        for (int row = 0; row < sizeof(row_pins); row++) {
            BMPAPI->ecs.discharge_capacitor();

            // assign_ecs_drive_pin
            BMPAPI->ecs.assign_drive_pin(row_pins[row]);

            // drive prev row low
            BMPAPI->ecs.clear_drive_pins(&ecs_config);

            // read switch value
            BMPAPI->ecs.sw_read(&sw_read[col_sel_idx + row * LEN(col_sels)]);
            sw_idx++;
        }
    }

    BMPAPI->ecs.discharge_capacitor();

    // select first col
    for (int col_pin_idx = 0; col_pin_idx < LEN(col_pins); col_pin_idx++) {
        writePin(col_pins[col_pin_idx],
                 col_sels[0] & (1 << col_pin_idx) ? 1 : 0);
    }

    // clear all row
    BMPAPI->ecs.clear_drive_pins(&ecs_config);

    // stop_adc
    BMPAPI->ecs.schedule_next_scan();

    uint8_t matrix_changed = 0;

    for (int row = 0; row < THIS_DEVICE_ROWS; row++) {
        for (int col = 0; col < THIS_DEVICE_COLS; col++) {
            if (sw_read[col + row * LEN(col_sels)] > ERROR_TH) {
                // error value

                dprintf("ERROR(%d,%d):%d", row, col,
                        sw_read[col + row * LEN(col_sels)]);

                sw_read[col + row * LEN(col_sels)] = 0;
            }

            if (matrix_raw[row] & (1 << col)) {
                if (sw_read[col + row * LEN(col_sels)] < LOW_TH) {
                    matrix_raw[row] &= ~(1 << col);
                    matrix_changed++;

                    dprintf("UP(%d,%d):%d", row, col,
                            sw_read[col + row * LEN(col_sels)]);
                }
            } else {
                if (sw_read[col + row * LEN(col_sels)] > HIGH_TH) {
                    matrix_raw[row] |= (1 << col);
                    matrix_changed++;

                    dprintf("DOWN(%d,%d):%d", row, col,
                            sw_read[col + row * LEN(col_sels)]);
                }
            }
        }
    }

    static int cnt = 0;
    if (cnt++ == 30) {
        cnt = 0;
        for (int row = 0; row < sizeof(row_pins); row++) {
            for (int col_sel_idx = 0; col_sel_idx < LEN(col_sels);
                 col_sel_idx++) {
                dprintf("%5d", sw_read[col_sel_idx + row * LEN(col_sels)]);
            }
            dprintf("\n");
        }
        dprintf("\n");
    }

    if (matrix_changed) {
        if (scan_mode == SCAN_MODE_DEEP_SLEEP) {
            BMPAPI->app.reset(0);
        }
        sleep_count = 0;
        scan_mode   = SCAN_MODE_ACTIVE;
    } else {
        if ((!is_usb_connected()) && scan_mode == SCAN_MODE_ACTIVE && sleep_count > STANBY_COUNT) {
            scan_mode = SCAN_MODE_STANBY;
        }
        sleep_count++;
    }

    return matrix_changed;
}

static const bmp_matrix_func_t matrix_func = {
    ecs_matrix_init, ecs_get_device_row, ecs_get_device_col, ecs_matrix_scan};

const bmp_matrix_func_t *get_matrix_func_user() { return &matrix_func; }

void bmp_enter_sleep() {
    scan_mode = SCAN_MODE_DEEP_SLEEP;
    BMPAPI->ble.disconnect(1);
}

void bmp_before_sleep() {}

bool checkSafemodeFlag(bmp_api_config_t const *const config) { return false; }
