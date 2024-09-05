// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Helpful defines
#define GRAVE_MODS  (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

enum layer_names {
    _BL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT(
        KC_S,   KC_D,   KC_K,   KC_L,
        KC_V,   KC_B,   KC_N
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(QK_MOUSE_CURSOR_UP);
        } else {
            tap_code(QK_MOUSE_CURSOR_DOWN);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(QK_MOUSE_CURSOR_LEFT);
        } else {
            tap_code(QK_MOUSE_CURSOR_RIGHT);
        }
    }
    return false;
}