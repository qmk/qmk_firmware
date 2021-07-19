/* Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
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

#include "tractyl_manuform.h"
#include "transactions.h"
#include <string.h>
#include "drivers/sensors/pmw3360.h"

#ifndef TRACKBALL_DPI_OPTIONS
#    define TRACKBALL_DPI_OPTIONS \
        { 1200, 1600, 2400 }
#    ifndef TRACKBALL_DPI_DEFAULT
#        define TRACKBALL_DPI_DEFAULT 1
#    endif
#endif
#ifndef TRACKBALL_DPI_DEFAULT
#    define TRACKBALL_DPI_DEFAULT 0
#endif

extern kb_runtime_config_t kb_state;
extern kb_slave_data_t     kb_slave;

keyboard_config_t keyboard_config;
uint16_t          dpi_array[] = TRACKBALL_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

bool     BurstState  = false; // init burst state for Trackball module
uint16_t MotionStart = 0;     // Timer for accel, 0 is resting state

__attribute__((weak)) void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {
    mouse_report->x = x;
    mouse_report->y = y;
}

__attribute__((weak)) void process_mouse(report_mouse_t* mouse_report) {
    report_pmw_t data = pmw_read_burst();
    if (data.isOnSurface && data.isMotion) {
        // Reset timer if stopped moving
        if (!data.isMotion) {
            if (MotionStart != 0) MotionStart = 0;
            return;
        }

        // Set timer if new motion
        if ((MotionStart == 0) && data.isMotion) {
            if (debug_mouse) dprintf("Starting motion.\n");
            MotionStart = timer_read();
        }

        if (debug_mouse) { dprintf("Delt] d: %d t: %u\n", abs(data.dx) + abs(data.dy), MotionStart); }
        if (debug_mouse) { dprintf("Pre ] X: %d, Y: %d\n", data.dx, data.dy); }
#if defined(PROFILE_LINEAR)
        float scale = float(timer_elaspsed(MotionStart)) / 1000.0;
        data.dx *= scale;
        data.dy *= scale;
#elif defined(PROFILE_INVERSE)
        // TODO
#else
        // no post processing
#endif

        // Wrap to HID size
        data.dx = constrain(data.dx, -127, 127);
        data.dy = constrain(data.dy, -127, 127);
        if (debug_mouse) dprintf("Cons] X: %d, Y: %d\n", data.dx, data.dy);
        // dprintf("Elapsed:%u, X: %f Y: %\n", i, pgm_read_byte(firmware_data+i));

        mouse_report->x = -data.dx;
        mouse_report->y = data.dy;
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) { return false; }

#ifdef POINTING_DEVICE_ENABLE
    if (keycode == DPI_CONFIG && record->event.pressed) {
        if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
            keyboard_config.dpi_config = (keyboard_config.dpi_config - 1) % DPI_OPTION_SIZE;
        } else {
            keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
        }
        eeconfig_update_kb(keyboard_config.raw);
        trackball_set_cpi(dpi_array[keyboard_config.dpi_config]);
    }
#endif

/* If Mousekeys is disabled, then use handle the mouse button
 * keycodes.  This makes things simpler, and allows usage of
 * the keycodes in a consistent manner.  But only do this if
 * Mousekeys is not enable, so it's not handled twice.
 */
#ifndef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t currentReport = pointing_device_get_report();
        if (record->event.pressed) {
            currentReport.buttons |= 1 << (keycode - KC_MS_BTN1);
        } else {
            currentReport.buttons &= ~(1 << (keycode - KC_MS_BTN1));
        }
        pointing_device_set_report(currentReport);
        pointing_device_send();
    }
#endif

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

    // This is the debug LED.
#if defined(DEBUG_LED_PIN)
    setPinOutput(DEBUG_LED_PIN);
    writePin(DEBUG_LED_PIN, debug_enable);
#endif

    keyboard_pre_init_user();
}

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init(void) {
    if (!is_keyboard_left()) {
        // initialize ball sensor
        pmw_spi_init();
    }
    trackball_set_cpi(dpi_array[keyboard_config.dpi_config]);
}

static bool has_report_changed(report_mouse_t new, report_mouse_t old) { return (new.buttons != old.buttons) || (new.x&& new.x != old.x) || (new.y&& new.y != old.y) || (new.h&& new.h != old.h) || (new.v&& new.v != old.v); }

void pointing_device_task(void) {
    report_mouse_t mouse_report = pointing_device_get_report();
    if (!is_keyboard_left()) { process_mouse(&mouse_report); }

    pointing_device_set_report(mouse_report);
    pointing_device_send();
}
#endif

void eeconfig_init_kb(void) {
    keyboard_config.dpi_config = TRACKBALL_DPI_DEFAULT;
#ifdef POINTING_DEVICE_ENABLE
    trackball_set_cpi(dpi_array[keyboard_config.dpi_config]);
#endif
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    // is safe to just read DPI setting since matrix init
    // comes before pointing device init.
    keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.dpi_config > DPI_OPTION_SIZE) { eeconfig_init_kb(); }
    matrix_init_user();
}

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_send(void) {
    static report_mouse_t old_report  = {};
    report_mouse_t        mouseReport = pointing_device_get_report();
    if (is_keyboard_master()) {
        int8_t x = mouseReport.x, y = mouseReport.y;
        mouseReport.x = 0;
        mouseReport.y = 0;
        process_mouse_user(&mouseReport, x, y);
        if (has_report_changed(mouseReport, old_report)) { host_mouse_send(&mouseReport); }
    } else {
        master_mouse_send(mouseReport.x, mouseReport.y);
    }
    mouseReport.x = 0;
    mouseReport.y = 0;
    mouseReport.v = 0;
    mouseReport.h = 0;
    old_report    = mouseReport;
    pointing_device_set_report(mouseReport);
}
#endif

#ifdef POINTING_DEVICE_ENABLE
void master_mouse_send(int8_t x, int8_t y) {
#ifdef SPLIT_TRANSACTION_IDS_KB
    kb_slave.mouse_x += x;
    kb_slave.mouse_y += y;
#endif
}
void trackball_set_cpi(uint16_t cpi) {
    if (!is_keyboard_left()) {
        pmw_set_cpi(cpi);
    } else {
#ifdef SPLIT_TRANSACTION_IDS_KB
        kb_state.device_cpi = cpi;
#endif
    }
}
#endif
