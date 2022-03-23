/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

#ifdef RGB_MATRIX_ENABLE

const ckled2001_led PROGMEM g_ckled2001_leds[DRIVER_LED_TOTAL] = {
/* Refer to CKLED manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, C_1,    A_1,    B_1},
    {0, C_2,    A_2,    B_2},
    {0, C_3,    A_3,    B_3},
    {0, C_4,    A_4,    B_4},
    {0, C_5,    A_5,    B_5},
    {0, C_6,    A_6,    B_6},

    {0, C_7,    A_7,    B_7},

    {0, F_1,    D_1,    E_1},
    {0, F_2,    D_2,    E_2},
    {0, F_3,    D_3,    E_3},
    {0, F_4,    D_4,    E_4},
    {0, F_5,    D_5,    E_5},
    {0, F_6,    D_6,    E_6},

    {0, F_7,    D_7,    E_7},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0, 1, 2,  3,  4,  5,  6, \
          7, 8, 9, 10, 11, 12, 13 },
    },
    {
        // LED Index to Physical Position
        // {0,1}, {0,2}, {0,3}, {0,4}, {0,5}, {0,6},
        // {0,6}, {0,7}, {0,8}, {0,9}, {0,10}, {0,11},
    },
    {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4,
    }
};

#endif

#ifndef KEYCHRON_DPI_OPTIONS
#    define KEYCHRON_DPI_OPTIONS \
        { 1200, 2600, 3400, 5000 }
#    ifndef KEYCHRON_DPI_DEFAULT
#        define KEYCHRON_DPI_DEFAULT 0
#    endif
#endif

keyboard_config_t keyboard_config;
uint16_t dpi_array[] = KEYCHRON_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    if (keycode == DPI_CONFIG && record->event.pressed) {
        keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
        eeconfig_update_kb(keyboard_config.raw);
        pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);

        // uint16_t cpi = pointing_device_get_cpi();
        // uprintf("cpi = %d\r\n", cpi);
    }

/* If Mousekeys is disabled, then use handle the mouse button
 * keycodes.  This makes things simpler, and allows usage of
 * the keycodes in a consistent manner.  But only do this if
 * Mousekeys is not enable, so it's not handled twice.
 */
#ifndef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t currentReport = pointing_device_get_report();
        currentReport.buttons = pointing_device_handle_buttons(currentReport.buttons, record->event.pressed, keycode - KC_MS_BTN1);
        pointing_device_set_report(currentReport);
        pointing_device_send();
    }
#endif
    return true;
}

// Hardware Setup
void keyboard_pre_init_kb(void) {

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

#ifdef ENCODER_ENABLE
    // pin_t encoders_pad_a[] = ENCODERS_PAD_A;
    // pin_t encoders_pad_b[] = ENCODERS_PAD_B;
    // palEnableLineEvent(encoders_pad_a[0], PAL_EVENT_MODE_BOTH_EDGES);
    // palEnableLineEvent(encoders_pad_b[0], PAL_EVENT_MODE_BOTH_EDGES);
    // palSetLineCallback(encoders_pad_a[0], encoder0_pad_cb, NULL);
    // palSetLineCallback(encoders_pad_b[0], encoder0_pad_cb, NULL);
#endif
    keyboard_pre_init_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
#ifdef MOUSEKEY_ENABLE
    tap_code(clockwise ? KC_WH_U : KC_WH_D);
#else
    mouse_report_t mouse_report = pointing_device_get_report();
    mouse_report.v = clockwise ? 1 : -1;
    pointing_device_set_report(mouse_report);
    pointing_device_send();
#endif
    return true;
}

void pointing_device_init_kb(void) {
    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
}

void eeconfig_init_kb(void) {
    keyboard_config.dpi_config = KEYCHRON_DPI_DEFAULT;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

void matrix_init_kb(void) {
    // is safe to just read DPI setting since matrix init
    // comes before pointing device init.
    // keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.dpi_config > DPI_OPTION_SIZE) {
        eeconfig_init_kb();
    }
    matrix_init_user();
}
