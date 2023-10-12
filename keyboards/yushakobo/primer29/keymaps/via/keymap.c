// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_INS,  KC_HOME, KC_PGUP, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_DEL,  KC_END,  KC_PGDN, KC_P7,   KC_P8,   KC_P9,
                                   KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        MO(1),   KC_UP,   MO(2),   KC_P1,   KC_P2,   KC_P3,
        KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,   KC_PDOT,       KC_PENT
    ),
    [1] = LAYOUT(
        _______, _______, _______, KC_TAB,  _______, _______, KC_BSPC,
        C(KC_X), C(KC_C), C(KC_V), _______, _______, _______,
                                   _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        C(KC_Z), C(KC_S), C(KC_Y),  _______,   KC_SPC,        _______
    ),
    [2] = LAYOUT(
        _______, _______, _______, KC_F10,  KC_F11,  KC_F12, _______,
        _______, _______, _______, KC_F7,   KC_F8,   KC_F9,
                                   KC_F4,   KC_F5,   KC_F6,   _______,
        _______, _______, _______, KC_F1,   KC_F2,   KC_F3,
        _______, _______, _______,  _______,   _______,       _______
    )
};
