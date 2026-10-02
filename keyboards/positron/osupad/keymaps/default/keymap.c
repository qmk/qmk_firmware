// Copyright 2024-2026 Juarendra Ramadhani (@juarendra)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_A, KC_B, KC_C,
        KC_E, KC_F, KC_G
    ),
};
