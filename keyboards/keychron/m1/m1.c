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
    {0, C_1,    B_1,    A_1},
    {0, C_2,    B_2,    A_2},
    {0, C_3,    B_3,    A_3},
    {0, C_4,    B_4,    A_4},
    {0, C_5,    B_5,    A_5},
    {0, C_6,    B_6,    A_6},

    {0, F_1,    D_1,    E_1},
    {0, F_2,    D_2,    E_2},
    {0, F_3,    D_3,    E_3},
    {0, F_4,    D_4,    E_4},
    {0, F_5,    D_5,    E_5},
    {0, F_6,    D_6,    E_6},

    {0, C_7,    A_7,    B_7}, // Wheel RGB
    {0, F_7,    D_7,    E_7}, // RGB indicator
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 },
    },
    {
        // LED Index to Physical Position
    },
    {
        // LED Index to Flag
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 9,
    }
};

#endif

/* Definiton of RGB Configuration and factory reset*/
enum {
    MODE_NONE,
    MODE_RGB,
    MODE_DPI
}rgb_dpi_mode;

uint32_t timer_3s_buffer   = 0;
uint32_t timer_250ms_buffer   = 0;
uint8_t factory_reset_count  = 0;
bool rgb_cfg_indicate = false;
bool wheel_set_hue = false;
bool rgb_cfg_mode = false;
bool dpi_cfg_mode = false;

/* Definiton of DPI Configuration */
#define KEYCHRON_DPI_OPTIONS {1200, 2400, 3600, 5000};
#define KEYCHRON_DPI_DEFAULT 0
keyboard_config_t keyboard_config;
uint16_t dpi_array[] = KEYCHRON_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

/* Definiton of DPI Indicator */
#define LED_RED_PIN A10
#define LED_GREEN_PIN A8
#define LED_BLUE_PIN A9

void dpi_config_indicators(uint8_t dpi_config);

void led_red_on(void);
void led_blue_on(void);
void led_white_on(void);
void led_all_off(void);

/* User functions */
uint16_t dpi_val = 0;

    bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    // uprintf("timer_3s_buffer4 = %d\n", timer_3s_buffer);
#ifdef CONSOLE_ENABLE
    // uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    switch (keycode) {
        case RGB_CONFIG:
            if (record->event.pressed) {
                // chVTDoSetI(&vt, TIME_MS2I(100), key_debounce_callback, NULL);
                if (wheel_set_hue) {
                    wheel_set_hue    = false;
                    rgb_cfg_indicate = false;
                    rgb_cfg_mode     = true;
                } else {
                    rgb_dpi_mode    = MODE_RGB;
                    timer_3s_buffer = sync_timer_read32();
                }
            } else {
                if (wheel_set_hue || rgb_cfg_mode) {
                    if (!wheel_set_hue) {
                        rgb_cfg_mode = false;
                    }
                } else {
                    rgb_matrix_step();
                }
                rgb_dpi_mode    = MODE_NONE;
                timer_3s_buffer = 0;
            }
            return false;  // Skip all further processing of this key
        case DPI_CONFIG:
            if (record->event.pressed) {
                rgb_dpi_mode = MODE_DPI;
                timer_3s_buffer = sync_timer_read32();
            } else {
                if (dpi_cfg_mode) {
                    dpi_cfg_mode = false;
                } else {
                    keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
                    eeconfig_update_kb(keyboard_config.raw);
                    pointing_device_set_cpi(dpi_array[keyboard_config.dpi_config]);
                    dpi_config_indicators(keyboard_config.dpi_config);
                }
                rgb_dpi_mode = MODE_NONE;
                timer_3s_buffer = 0;
            }
            return false;  // Skip all further processing of this key
        case KC_BTN4:
            if (record->event.pressed) {
                dpi_val = pointing_device_get_cpi();
                uprintf("Current dpi value is %d\n", dpi_val);
            }
            return false;  // Skip all further processing of this key
        default:
/* If Mousekeys is disabled, then use handle the mouse button
 * keycodes.  This makes things simpler, and allows usage of
 * the keycodes in a consistent manner.  But only do this if
 * Mousekeys is not enable, so it's not handled twice.
 */
#ifndef MOUSEKEY_ENABLE
            if (IS_MOUSEKEY_BUTTON(keycode)) {
                report_mouse_t currentReport = pointing_device_get_report();
                currentReport.buttons        = pointing_device_handle_buttons(currentReport.buttons, record->event.pressed, keycode - KC_MS_BTN1);
                pointing_device_set_report(currentReport);
                pointing_device_send();
            }
#endif
            return true;
                }
}

void matrix_scan_kb(void) {
    if (timer_3s_buffer && (timer_elapsed32(timer_3s_buffer) > 3000)) {
        timer_3s_buffer    = 0;
        switch (rgb_dpi_mode) {
            case MODE_RGB:
                wheel_set_hue    = true;
                rgb_cfg_indicate = true;
                break;
            case MODE_DPI:
                dpi_cfg_mode       = true;
                timer_250ms_buffer = sync_timer_read32();
            default:
                break;
        }
    }

    if (timer_250ms_buffer && sync_timer_elapsed32(timer_250ms_buffer) > 300) {
        if (++factory_reset_count > 7) {
            factory_reset_count = 0;
            timer_250ms_buffer  = 0;
            eeconfig_init();
            eeconfig_init_kb();
            dpi_config_indicators(keyboard_config.dpi_config);
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_enable();
            }
            rgb_matrix_init();
        } else {
            timer_250ms_buffer = sync_timer_read32();
        }
    }

    matrix_scan_user();
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

    led_all_off();

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
    if (wheel_set_hue) {
        if (clockwise) {
            rgb_matrix_increase_hue();
        } else {
            rgb_matrix_decrease_hue();
        }
    } else {
        tap_code_delay(clockwise ? KC_WH_U : KC_WH_D, 10);
    }
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
    keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.dpi_config > DPI_OPTION_SIZE) {
        eeconfig_init_kb();
    }
    dpi_config_indicators(keyboard_config.dpi_config);
    matrix_init_user();
}

void rgb_matrix_indicators_kb(void) {
    if (rgb_cfg_indicate) {
        rgb_matrix_set_color(13, RGB_WHITE);
    } else {
        rgb_matrix_set_color(13, RGB_OFF);
    }
    if (factory_reset_count) {
        for (uint8_t i = 0; i < 13; i++) {
            rgb_matrix_set_color(i, factory_reset_count % 2 ? 0 : RGB_RED);
        }
    }
}

void led_red_on(void) {
    setPinOutput(LED_RED_PIN);
    writePinLow(LED_RED_PIN);
    setPinOutput(LED_GREEN_PIN);
    writePinHigh(LED_GREEN_PIN);
    setPinOutput(LED_BLUE_PIN);
    writePinHigh(LED_BLUE_PIN);
}

void led_green_on(void) {
    setPinOutput(LED_RED_PIN);
    writePinHigh(LED_RED_PIN);
    setPinOutput(LED_GREEN_PIN);
    writePinLow(LED_GREEN_PIN);
    setPinOutput(LED_BLUE_PIN);
    writePinHigh(LED_BLUE_PIN);
}

void led_blue_on(void) {
    setPinOutput(LED_RED_PIN);
    writePinHigh(LED_RED_PIN);
    setPinOutput(LED_GREEN_PIN);
    writePinHigh(LED_GREEN_PIN);
    setPinOutput(LED_BLUE_PIN);
    writePinLow(LED_BLUE_PIN);
}

void led_white_on(void) {
    setPinOutput(LED_RED_PIN);
    writePinLow(LED_RED_PIN);
    setPinOutput(LED_GREEN_PIN);
    writePinLow(LED_GREEN_PIN);
    setPinOutput(LED_BLUE_PIN);
    writePinLow(LED_BLUE_PIN);
}

void led_all_off(void) {
    setPinOutput(LED_RED_PIN);
    writePinHigh(LED_RED_PIN);
    setPinOutput(LED_GREEN_PIN);
    writePinHigh(LED_GREEN_PIN);
    setPinOutput(LED_BLUE_PIN);
    writePinHigh(LED_BLUE_PIN);
}

void dpi_config_indicators(uint8_t dpi_config) {
    switch (dpi_config) {
        case 0:
            led_white_on();
            break;
        case 1:
            led_blue_on();
            break;
        case 2:
            led_green_on();
            break;
        case 3:
            led_red_on();
            break;
        default:
            break;
    }
}
