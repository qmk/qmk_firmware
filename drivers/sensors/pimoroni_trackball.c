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

#ifndef TRACKBALL_ADDRESS
#    define TRACKBALL_ADDRESS 0x0A
#endif
#ifndef TRACKBALL_INTERVAL_MS
#    define TRACKBALL_INTERVAL_MS 8
#endif
#ifndef TRACKBALL_DEBOUNCE_ONCLICK
#    define TRACKBALL_DEBOUNCE_ONCLICK 5
#endif

#define TRACKBALL_TIMEOUT 100
#define TRACKBALL_REG_LED_RED 0x00
#define TRACKBALL_REG_LED_GRN 0x01
#define TRACKBALL_REG_LED_BLU 0x02
#define TRACKBALL_REG_LED_WHT 0x03
#define TRACKBALL_REG_LEFT 0x04
#define TRACKBALL_REG_RIGHT 0x05
#define TRACKBALL_REG_UP 0x06
#define TRACKBALL_REG_DOWN 0x07

typedef struct pimoroni_data {
    uint8_t left;
    uint8_t right;
    uint8_t up;
    uint8_t down;
    uint8_t click;
} pimoroni_data;

static pimoroni_data  current_pimoroni_data;
static report_mouse_t mouse_report;
static bool           scrolling = false;
static int16_t        x_offset  = 0;
static int16_t        y_offset  = 0;
static int16_t        h_offset  = 0;
static int16_t        v_offset  = 0;
static uint16_t       precision = 128;

float trackball_get_precision(void) { return (float)(precision >> 7); }
void  trackball_set_precision(float floatprecision) { precision = (floatprecision * 128); }
bool  trackball_is_scrolling(void) { return scrolling; }
void  trackball_set_scrolling(bool scroll) { scrolling = scroll; }

void trackball_set_rgbw(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    uint8_t                              data[4] = {r, g, b, w};
    __attribute__((unused)) i2c_status_t status  = i2c_writeReg(TRACKBALL_ADDRESS << 1, TRACKBALL_REG_LED_RED, data, sizeof(data), TRACKBALL_TIMEOUT);
    dprintf("Trackball RGBW i2c_status_t: %d\n", status);
}

void read_pimoroni_trackball(pimoroni_data* data) {
    __attribute__((unused)) i2c_status_t status = i2c_readReg(TRACKBALL_ADDRESS << 1, TRACKBALL_REG_LEFT, (uint8_t*)data, sizeof(*data), TRACKBALL_TIMEOUT);
#ifdef TRACKBALL_DEBUG_READ
    dprintf("Trackball READ i2c_status_t: %d\nLeft: %d\nRight: %d\nUp: %d\nDown: %d\nSwtich: %d\n", status, data->left, data->right, data->up, data->down, data->click);
#endif
}

__attribute__((weak)) void pointing_device_init(void) {
    i2c_init();
    trackball_set_rgbw(0x00, 0x00, 0x00, 0x00);
}

int16_t get_offsets(uint8_t negative_dir, uint8_t positive_dir, uint8_t scale) {
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

void update_values(int8_t* member, int16_t* offset) {
    if (*offset > 127) {
        *member = 127;
        *offset -= 127;
    } else if (*offset < -127) {
        *member = -127;
        *offset += 127;
    } else {
        *member = *offset;
        *offset = 0;
    }
}

__attribute__((weak)) void trackball_check_click(bool pressed, report_mouse_t* mouse) {
    if (pressed) {
        mouse->buttons |= MOUSE_BTN1;
    } else {
        mouse->buttons &= ~MOUSE_BTN1;
    }
}

void pointing_device_task() {
    static fast_timer_t throttle = 0;
    static uint8_t      debounce = 0;

    if (timer_elapsed_fast(throttle) > TRACKBALL_INTERVAL_MS) {
        static pimoroni_data last_read_data = {0};
        mouse_report                        = pointing_device_get_report();
        read_pimoroni_trackball(&current_pimoroni_data);

        if (!debounce) {
            if (memcmp(&last_read_data, &current_pimoroni_data, sizeof(current_pimoroni_data))) {
                memcpy(&last_read_data, &current_pimoroni_data, sizeof(current_pimoroni_data));

#ifdef PIMORONI_TRACKBALL_CLICK
                if (current_pimoroni_data.click & 128) {
                    trackball_check_click(true, &mouse_report);
                    debounce = TRACKBALL_DEBOUNCE_ONCLICK;
                } else {
                    trackball_check_click(false, &mouse_report);
                }
#endif
                if (scrolling) {
#ifdef PIMORONI_TRACKBALL_INVERT_X
                    h_offset += get_offsets(current_pimoroni_data.right, current_pimoroni_data.left, 5);
#else
                    h_offset -= get_offsets(current_pimoroni_data.right, current_pimoroni_data.left, 5);
#endif
#ifdef PIMORONI_TRACKBALL_INVERT_Y
                    v_offset += get_offsets(current_pimoroni_data.down, current_pimoroni_data.up, 5);
#else
                    v_offset -= get_offsets(current_pimoroni_data.down, current_pimoroni_data.up, 5);
#endif
                } else {
#ifdef PIMORONI_TRACKBALL_INVERT_X
                    x_offset -= get_offsets(current_pimoroni_data.right, current_pimoroni_data.left, 5);
#else
                    x_offset += get_offsets(current_pimoroni_data.right, current_pimoroni_data.left, 5);
#endif
#ifdef PIMORONI_TRACKBALL_INVERT_Y
                    y_offset -= get_offsets(current_pimoroni_data.down, current_pimoroni_data.up, 5);
#else
                    y_offset += get_offsets(current_pimoroni_data.down, current_pimoroni_data.up, 5);
#endif
                }
            }
        } else {
            debounce--;
        }
        if (scrolling) {
#ifndef PIMORONI_TRACKBALL_ROTATE
            update_values(&mouse_report.h, &h_offset);
            update_values(&mouse_report.v, &v_offset);
#else
            update_values(&mouse_report.h, &v_offset);
            update_values(&mouse_report.v, &h_offset);
#endif
            mouse_report.x = 0;
            mouse_report.y = 0;
        } else {
#ifndef PIMORONI_TRACKBALL_ROTATE
            update_values(&mouse_report.x, &x_offset);
            update_values(&mouse_report.y, &y_offset);
#else
            update_values(&mouse_report.x, &y_offset);
            update_values(&mouse_report.y, &x_offset);
#endif
            mouse_report.h = 0;
            mouse_report.v = 0;
        }
        pointing_device_set_report(mouse_report);
        pointing_device_send();

        throttle = timer_read_fast();
    }
}
