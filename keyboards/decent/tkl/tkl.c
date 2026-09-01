// Copyright 2024 B. Le Roy
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        // 0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20
        0x20, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xBC, 0xBD, 0xBE, 0xBF,
        0x00
    };

   oled_write_P(qmk_logo, false);
   oled_write_pixel(126, 0, 1);
   oled_write_pixel(127, 0, 1);
   oled_write_pixel(126, 1, 1);
}

static const char PROGMEM caps_on[] = { 0x9C, 0x9D, 0x9E, 0x9F };
static const char PROGMEM caps_off[] = { 0xBC, 0xBD, 0xBE, 0xBF };

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    render_logo();

    bool caps = host_keyboard_led_state().caps_lock;

    if (caps) {
        oled_set_cursor(17, 3);
        oled_write_P(caps ? caps_on : caps_off, false);
    }
    return false;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    bool caps = host_keyboard_led_state().caps_lock;

    if (caps) {
        for (uint8_t i = led_min; i < led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_KEYLIGHT) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }

    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
            }
        }
    }

    return false;
}
