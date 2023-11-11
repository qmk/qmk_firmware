/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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

#include "madromys.h"

#ifndef PLOOPY_DPI_OPTIONS
#    define PLOOPY_DPI_OPTIONS \
        { 600, 900, 1200, 1600 }
#    ifndef PLOOPY_DPI_DEFAULT
#        define PLOOPY_DPI_DEFAULT 1
#    endif
#endif
#ifndef PLOOPY_DPI_DEFAULT
#    define PLOOPY_DPI_DEFAULT 0
#endif
#ifndef PLOOPY_DRAGSCROLL_DPI
#    define PLOOPY_DRAGSCROLL_DPI 100  // Fixed-DPI Drag Scroll
#endif
#ifndef PLOOPY_DRAGSCROLL_FIXED
#    define PLOOPY_DRAGSCROLL_FIXED 1
#endif
#ifndef PLOOPY_DRAGSCROLL_MULTIPLIER
#    define PLOOPY_DRAGSCROLL_MULTIPLIER 0.75  // Variable-DPI Drag Scroll
#endif
#ifndef PLOOPY_DRAGSCROLL_SEMAPHORE
#    define PLOOPY_DRAGSCROLL_SEMAPHORE 4
#endif
#ifndef PLOOPY_DRAGSCROLL_MOMENTARY
#    define PLOOPY_DRAGSCROLL_MOMENTARY 1
#endif
#ifndef PLOOPY_DRAGSCROLL_INVERT
#    define PLOOPY_DRAGSCROLL_INVERT 1
#endif

keyboard_config_t keyboard_config;
uint16_t          dpi_array[] = PLOOPY_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

// TODO: Implement libinput profiles
// https://wayland.freedesktop.org/libinput/doc/latest/pointer-acceleration.html
// Compile time accel selection
// Valid options are ACC_NONE, ACC_LINEAR, ACC_CUSTOM, ACC_QUADRATIC

// Trackball State
bool     is_drag_scroll    = false;

// drag scroll divisor state
int8_t drag_scroll_x_semaphore = 0;
int8_t drag_scroll_y_semaphore = 0;

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (is_drag_scroll) {
        int16_t mouse_report_x_temp = mouse_report.x;
        int16_t mouse_report_y_temp = mouse_report.y;
        int16_t mouse_report_x_calc = 0;
        int16_t mouse_report_y_calc = 0;
        int16_t valx = (mouse_report_x_temp > 0) ? -1 : 1;
        int16_t valy = (mouse_report_y_temp > 0) ? -1 : 1;

        while (mouse_report_x_temp != 0) {
            mouse_report_x_temp += valx;
            drag_scroll_x_semaphore -= valx;

            if (abs(drag_scroll_x_semaphore) >= PLOOPY_DRAGSCROLL_SEMAPHORE) {
                mouse_report_x_calc -= valx;
                drag_scroll_x_semaphore = 0;
            }
        }

        while (mouse_report_y_temp != 0) {
            mouse_report_y_temp += valy;
            drag_scroll_y_semaphore -= valy;

            if (abs(drag_scroll_y_semaphore) >= PLOOPY_DRAGSCROLL_SEMAPHORE) {
                mouse_report_y_calc -= valy;
                drag_scroll_y_semaphore = 0;
            }
        }

        mouse_report.h = mouse_report_x_calc;

#ifdef PLOOPY_DRAGSCROLL_INVERT
        // Invert vertical scroll direction
        mouse_report.v = -mouse_report_y_calc;
#else
        mouse_report.v = mouse_report_y_calc;
#endif
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return pointing_device_task_user(mouse_report);
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    if (keycode == DPI_CONFIG && record->event.pressed) {
        keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
        eeconfig_update_kb(keyboard_config.raw);
        pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
    }

    if (keycode == DRAG_SCROLL) {
#ifndef PLOOPY_DRAGSCROLL_MOMENTARY
        if (record->event.pressed)
#endif
        {
            is_drag_scroll ^= 1;
        }
#ifdef PLOOPY_DRAGSCROLL_FIXED
        pointing_device_set_cpi(is_drag_scroll ? PLOOPY_DRAGSCROLL_DPI : dpi_array[keyboard_config.dpi_config]);
#else
        pointing_device_set_cpi(is_drag_scroll ? (dpi_array[keyboard_config.dpi_config] * PLOOPY_DRAGSCROLL_MULTIPLIER) : dpi_array[keyboard_config.dpi_config]);
#endif
    }

    return true;
}

// Hardware Setup
void keyboard_pre_init_kb(void) {
    // debug_enable  = true;
    // debug_matrix  = true;
    // debug_mouse   = true;
    // debug_encoder = true;

    /* Ground all output pins connected to ground. This provides additional
     * pathways to ground. If you're messing with this, know this: driving ANY
     * of these pins high will cause a short. On the MCU. Ka-blooey.
     */
    const pin_t unused_pins[] = { GP1, GP3, GP4, GP6, GP8, GP10, GP14, GP16,
        GP18, GP20, GP22, GP24, GP25, GP26, GP27, GP28, GP29 };

    for (uint8_t i = 0; i < (sizeof(unused_pins) / sizeof(pin_t)); i++) {
        setPinOutput(unused_pins[i]);
        writePinLow(unused_pins[i]);
    }

    keyboard_pre_init_user();
}

void pointing_device_init_kb(void) { pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]); }

void eeconfig_init_kb(void) {
    keyboard_config.dpi_config = PLOOPY_DPI_DEFAULT;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    // is safe to just read DPI setting since matrix init
    // comes before pointing device init.
    keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.dpi_config > DPI_OPTION_SIZE) {
        eeconfig_init_kb();
    }
    matrix_init_user();
}
