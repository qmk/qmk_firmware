/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)
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
#include "pimoroni_trackball.h"
#include "i2c_master.h"
#include "print.h"

#ifndef PIMORONI_TRACKBALL_ADDRESS
#    define PIMORONI_TRACKBALL_ADDRESS 0x0A
#endif
#ifndef PIMORONI_TRACKBALL_INTERVAL_MS
#    define PIMORONI_TRACKBALL_INTERVAL_MS 8
#endif
#ifndef PIMORONI_TRACKBALL_MOUSE_SCALE
#    define PIMORONI_TRACKBALL_MOUSE_SCALE 5
#endif
#ifndef PIMORONI_TRACKBALL_SCROLL_SCALE
#    define PIMORONI_TRACKBALL_SCROLL_SCALE 1
#endif
#ifndef PIMORONI_TRACKBALL_DEBOUNCE_CYCLES
#    define PIMORONI_TRACKBALL_DEBOUNCE_CYCLES 20
#endif
#ifndef PIMORONI_TRACKBALL_ERROR_COUNT
#    define PIMORONI_TRACKBALL_ERROR_COUNT 10
#endif

#define TRACKBALL_TIMEOUT     100
#define TRACKBALL_REG_LED_RED 0x00
#define TRACKBALL_REG_LED_GRN 0x01
#define TRACKBALL_REG_LED_BLU 0x02
#define TRACKBALL_REG_LED_WHT 0x03
#define TRACKBALL_REG_LEFT    0x04
#define TRACKBALL_REG_RIGHT   0x05
#define TRACKBALL_REG_UP      0x06
#define TRACKBALL_REG_DOWN    0x07

static int16_t  x_offset    = 0;
static int16_t  y_offset    = 0;
static int16_t  h_offset    = 0;
static int16_t  v_offset    = 0;
static uint16_t precision   = 128;
static uint8_t  error_count = 0;

float pimoroni_trackball_get_precision(void) { return ((float)precision / 128); }
void  pimoroni_trackball_set_precision(float floatprecision) { precision = (floatprecision * 128); }
bool  pimoroni_trackball_is_scrolling(void) { return scrolling; }
void  pimoroni_trackball_set_scrolling(bool scroll) { scrolling = scroll; }

void pimoroni_trackball_set_rgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    uint8_t                              data[4] = {r, g, b, w};
    __attribute__((unused)) i2c_status_t status  = i2c_writeReg(PIMORONI_TRACKBALL_ADDRESS << 1, TRACKBALL_REG_LED_RED, data, sizeof(data), TRACKBALL_TIMEOUT);
#ifdef TRACKBALL_DEBUG
    dprintf("Trackball RGBW i2c_status_t: %d\n", status);
#endif
}

__attribute__((weak)) void pimironi_device_init(void) {
    i2c_init();
    trackball_set_rgbw(0x00, 0x00, 0x00, 0x00);
}

int16_t pimoroni_trackball_get_offsets(uint8_t negative_dir, uint8_t positive_dir, uint8_t scale) {
    uint8_t offset     = 0;
    bool    isnegative = false;
    if (negative_dir > positive_dir) {
        offset     = negative_dir - positive_dir;
        isnegative = true;
    } else {
        offset = positive_dir - negative_dir;
    }
    uint16_t magnitude = (scale * offset * offset * precision) >> 7;
    return isnegative ? -(int16_t)(magnitude) : (int16_t)(magnitude);
}

void pimoroni_trackball_adapt_values(int8_t* mouse, int16_t* offset) {
    if (*offset > 127) {
        *mouse = 127;
        *offset -= 127;
    } else if (*offset < -127) {
        *mouse = -127;
        *offset += 127;
    } else {
        *mouse  = *offset;
        *offset = 0;
    }
}

__attribute__((weak)) report_mouse_t get_pimorono_trackball_report(void) {
    static fast_timer_t throttle      = 0;
    static uint16_t     debounce      = 0;
    pimoroni_data_t     pimoroni_data = {0};
    report_mouse_t      report        = {0};

    if (error_count < PIMORONI_TRACKBALL_ERROR_COUNT && timer_elapsed_fast(throttle) >= PIMORONI_TRACKBALL_INTERVAL_MS) {
        i2c_status_t status = i2c_readReg(PIMORONI_TRACKBALL_ADDRESS << 1, TRACKBALL_REG_LEFT, &pimoroni_data, sizeof(pimoroni_data), TRACKBALL_TIMEOUT);
#ifdef TRACKBALL_DEBUG
        dprintf("Trackball READ i2c_status_t: %d\nLeft: %d\nRight: %d\nUp: %d\nDown: %d\nSwtich: %d\n", status, pimoroni_data.left, pimoroni_data.right, pimoroni_data.up, pimoroni_data.down, pimoroni_data.click);
#endif

        if (status == I2C_STATUS_SUCCESS) {
            error_count = 0;

            if (!(pimoroni_data.click & 128)) {
                if (!debounce) {
                    x_offset += trackball_get_offsets(pimoroni_data.right, pimoroni_data.left, PIMORONI_TRACKBALL_MOUSE_SCALE);
                    y_offset += trackball_get_offsets(pimoroni_data.down, pimoroni_data.up, PIMORONI_TRACKBALL_MOUSE_SCALE);
                    pimoroni_trackball_adapt_values(&report.x, &x_offset);
                    pimoroni_trackball_adapt_values(&report.y, &y_offset);
                } else {
                    debounce--;
                }
            } else {
                report.buttons = 0b1;
                debounce       = PIMORONI_TRACKBALL_DEBOUNCE_CYCLES;
            }
        }
    } else {
        error_count++;
    }

    throttle = timer_read_fast();
    return report;
}
