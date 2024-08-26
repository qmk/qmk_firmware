// Copyright 2024 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_C,    KC_V,   KC_VOLU, KC_VOLD, KC_DEL,
        KC_LCTL, KC_PGUP, KC_SPC, KC_PGDN, KC_ENT
    )
};
