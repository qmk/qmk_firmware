/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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

#include "trackball_nano.h"
#include "wait.h"

#ifndef OPT_DEBOUNCE
#    define OPT_DEBOUNCE 5  // (ms) 			Time between scroll events
#endif

#ifndef SCROLL_BUTT_DEBOUNCE
#    define SCROLL_BUTT_DEBOUNCE 100  // (ms) 			Time between scroll events
#endif

#ifndef OPT_THRES
#    define OPT_THRES 150  // (0-1024) 	Threshold for actication
#endif

#ifndef OPT_SCALE
#    define OPT_SCALE 1  // Multiplier for wheel
#endif

#ifndef PLOOPY_DPI_OPTIONS
#    define PLOOPY_DPI_OPTIONS { CPI375, CPI750, CPI1375 }
#    ifndef PLOOPY_DPI_DEFAULT
#        define PLOOPY_DPI_DEFAULT 2
#    endif
#endif

#ifndef PLOOPY_DPI_DEFAULT
#    define PLOOPY_DPI_DEFAULT 2
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { };

// Transformation constants for delta-X and delta-Y
const static float ADNS_X_TRANSFORM = -1.0;
const static float ADNS_Y_TRANSFORM = 1.0;

keyboard_config_t keyboard_config;
uint16_t dpi_array[] = PLOOPY_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

// TODO: Implement libinput profiles
// https://wayland.freedesktop.org/libinput/doc/latest/pointer-acceleration.html
// Compile time accel selection
// Valid options are ACC_NONE, ACC_LINEAR, ACC_CUSTOM, ACC_QUADRATIC

// Trackball State
bool is_scroll_clicked = false;
bool BurstState = false;  // init burst state for Trackball module
uint16_t MotionStart = 0;  // Timer for accel, 0 is resting state
uint16_t lastScroll = 0;  // Previous confirmed wheel event
uint16_t lastMidClick = 0;  // Stops scrollwheel from being read if it was pressed
uint8_t OptLowPin = OPT_ENC1;
bool debug_encoder = false;

__attribute__((weak)) void process_mouse_user(report_mouse_t* mouse_report, int16_t x, int16_t y) {
    mouse_report->x = x;
    mouse_report->y = y;
}

__attribute__((weak)) void process_mouse(report_mouse_t* mouse_report) {
    report_adns_t data = adns_read_burst();

    if (data.dx != 0 || data.dy != 0) {
        if (debug_mouse)
            dprintf("Raw ] X: %d, Y: %d\n", data.dx, data.dy);

        // Apply delta-X and delta-Y transformations.
        // x and y are swapped
        // the sensor is rotated
        // by 90 degrees
        float xt = (float) data.dy * ADNS_X_TRANSFORM;
        float yt = (float) data.dx * ADNS_Y_TRANSFORM;

        int16_t xti = (int16_t)xt;
        int16_t yti = (int16_t)yt;

        process_mouse_user(mouse_report, xti, yti);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);

    // Update Timer to prevent accidental scrolls
    if ((record->event.key.col == 1) && (record->event.key.row == 0)) {
        lastMidClick = timer_read();
        is_scroll_clicked = record->event.pressed;
    }

    if (!process_record_user(keycode, record))
        return false;

    if (keycode == DPI_CONFIG && record->event.pressed) {
        keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
        eeconfig_update_kb(keyboard_config.raw);
        adns_set_cpi(dpi_array[keyboard_config.dpi_config]);
    }

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
    // debug_enable = true;
    // debug_matrix = true;
    // debug_mouse = true;
    // debug_encoder = true;

    setPinInput(OPT_ENC1);
    setPinInput(OPT_ENC2);

    /* Ground all output pins connected to ground. This provides additional
     * pathways to ground. If you're messing with this, know this: driving ANY
     * of these pins high will cause a short. On the MCU. Ka-blooey.
     */
#ifdef UNUSED_PINS
    const pin_t unused_pins[] = UNUSED_PINS;

    for (uint8_t i = 0; i < (sizeof(unused_pins) / sizeof(pin_t)); i++) {
        setPinOutput(unused_pins[i]);
        writePinLow(unused_pins[i]);
    }
#endif

    keyboard_pre_init_user();
}

void pointing_device_init(void) {
    adns_init();
    opt_encoder_init();

    // reboot the adns.
    // if the adns hasn't initialized yet, this is harmless.
    adns_write_reg(REG_CHIP_RESET, 0x5a);

    // wait maximum time before adns is ready.
    // this ensures that the adns is actuall ready after reset.
    wait_ms(55);

    // read a burst from the adns and then discard it.
    // gets the adns ready for write commands
    // (for example, setting the dpi).
    adns_read_burst();

    // set the DPI.
    adns_set_cpi(dpi_array[keyboard_config.dpi_config]);
}

void pointing_device_task(void) {
    report_mouse_t mouse_report = pointing_device_get_report();
    process_mouse(&mouse_report);
    pointing_device_set_report(mouse_report);
    pointing_device_send();
}

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
