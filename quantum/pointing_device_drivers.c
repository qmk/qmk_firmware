/* Copyright 2017 Joshua Broekhuijsen <snipeye+qmk@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "pointing_device_drivers.h"
#include "debug.h"
#include "timer.h"

// get_report functions should probably be moved to their respective drivers.
#if defined(POINTING_DEVICE_DRIVER_adns5050)
// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init         = adns9800_device_init,
    .get_report   = get_adns9800_trackball_report,
};
// clang-format on
#elif defined(POINTING_DEVICE_DRIVER_adns9800)

report_mouse_t adns9800_get_report_driver(report_mouse_t mouse_report) {
    report_adns9800_t sensor_report = adns9800_get_report();

    int8_t clamped_x = CLAMP_HID(sensor_report.x);
    int8_t clamped_y = CLAMP_HID(sensor_report.y);

    mouse_report.x = clamped_x;
    mouse_report.y = clamped_y;

    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init         = adns9800_init,
    .get_report   = adns9800_get_report_driver,
};
// clang-format on
#elif defined(POINTING_DEVICE_DRIVER_pimoroni_trackball)
report_mouse_t pimorono_trackball_get_report(report_mouse_t mouse_report) {
    static fast_timer_t throttle      = 0;
    static uint16_t     debounce      = 0;
    static uint8_t      error_count   = 0;
    pimoroni_data_t     pimoroni_data = {0};
    static int16_t      x_offset = 0, y_offset = 0;

    if (error_count < PIMORONI_TRACKBALL_ERROR_COUNT && timer_elapsed_fast(throttle) >= PIMORONI_TRACKBALL_INTERVAL_MS) {
        i2c_status_t status = read_pimoroni_trackball(&pimoroni_data);

        if (status == I2C_STATUS_SUCCESS) {
            error_count = 0;

            if (!(pimoroni_data.click & 128)) {
                mouse_report.buttons |= MOUSE_BTN1;
                if (!debounce) {
                    x_offset += pimoroni_trackball_get_offsets(pimoroni_data.right, pimoroni_data.left, PIMORONI_TRACKBALL_MOUSE_SCALE);
                    y_offset += pimoroni_trackball_get_offsets(pimoroni_data.down, pimoroni_data.up, PIMORONI_TRACKBALL_MOUSE_SCALE);
                    pimoroni_trackball_adapt_values(&mouse_report.x, &x_offset);
                    pimoroni_trackball_adapt_values(&mouse_report.y, &y_offset);
                } else {
                    debounce--;
                }
            } else {
                mouse_report.buttons &= ~MOUSE_BTN1;
                debounce = PIMORONI_TRACKBALL_DEBOUNCE_CYCLES;
            }
        }
    } else {
        error_count++;
    }

    throttle = timer_read_fast();
    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = pimironi_trackball_device_init,
    .get_report = pimorono_trackball_get_report,
};
// clang-format on
#elif defined(POINTING_DEVICE_DRIVER_pmw3360)

static void init(void) { pmw3360_init(); }

report_mouse_t pmw3360_get_report(report_mouse_t mouse_report) {
    report_pmw3360_t data        = pmw3360_read_burst();
    static uint16_t  MotionStart = 0;  // Timer for accel, 0 is resting state

    if (data.isOnSurface && data.isMotion) {
        // Reset timer if stopped moving
        if (!data.isMotion) {
            if (MotionStart != 0) MotionStart = 0;
            return mouse_report;
        }

        // Set timer if new motion
        if ((MotionStart == 0) && data.isMotion) {
            if (debug_mouse) dprintf("Starting motion.\n");
            MotionStart = timer_read();
        }
        mouse_report.x = constrain(data.dx, -127, 127);
        mouse_report.y = constrain(data.dy, -127, 127);
    }

    return mouse_report;
}

// clang-format off
const pointing_device_driver_t pointing_device_driver = {
    .init       = init,
    .get_report = pmw3360_get_report,
};
// clang-format on
#endif
