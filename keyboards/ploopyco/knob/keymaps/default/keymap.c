/* Copyright 2023 Colin Lam (Ploopy Corporation)
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

#include QMK_KEYBOARD_H
#include "as5600.h"

// Dummy
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{ KC_NO }}};

static uint16_t current_position = 0;

void keyboard_post_init_user(void) {
    // debug_enable   = true;
    // debug_matrix   = true;
    // debug_keyboard = true;
    // debug_mouse    = true;

    as5600_init();
    current_position = as5600_get_rawangle();
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    uint16_t ra = as5600_get_rawangle();
    int16_t delta = (int16_t)(ra - current_position);

    // Wrap into [-2048, 2047] to get shortest direction
    if (delta > 2048) {
        delta -= 4096;
    } else if (delta < -2048) {
        delta += 4096;
    }

    if (detected_host_os() == OS_WINDOWS || detected_host_os() == OS_LINUX) {
        // Establish a deadzone to prevent spurious inputs
        if (delta > POINTING_DEVICE_AS5600_DEADZONE || delta < -POINTING_DEVICE_AS5600_DEADZONE) {
            current_position = ra;
            mouse_report.v = delta / POINTING_DEVICE_AS5600_SPEED_DIV;
        }
    } else {
        // Certain operating systems, like MacOS, don't play well with the
        // high-res scrolling implementation. For more details, see:
        // https://github.com/qmk/qmk_firmware/issues/17585#issuecomment-2325248167
        if (delta >= POINTING_DEVICE_AS5600_TICK_COUNT) {
            current_position = ra;
            mouse_report.v = 1;
        } else if (delta <= -POINTING_DEVICE_AS5600_TICK_COUNT) {
            current_position = ra;
            mouse_report.v = -1;
        }
    }

    return mouse_report;
}

bool pointing_device_driver_init(void) {
    return true;
}
