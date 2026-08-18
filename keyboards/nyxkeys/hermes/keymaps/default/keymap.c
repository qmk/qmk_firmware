// Copyright 2025 NyxKeys (@Shiva1796)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_6x4(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,
        MO(1),   KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_BSPC,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_PEQL, KC_PDOT, KC_TAB
    ),

    [1] = LAYOUT_ortho_6x4(
        KC_F5,   KC_F6,   KC_F7,   KC_F8,
        KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_HOME, KC_UP,   KC_PGUP, _______,
        KC_LEFT, XXXXXXX, KC_RGHT, QK_BOOT,
        KC_END,  KC_DOWN, KC_PGDN, _______,
        _______, _______, _______, _______
    )
};
