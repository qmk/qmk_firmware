// Copyright 2022 peepeetee (@peepeetee)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_DLR,  KC_LPRN, KC_RPRN, MO(1),   KC_DEL,
        KC_NLCK, KC_ESC,  KC_SLSH, KC_PAST, KC_PMNS,
        KC_EQL,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_TAB,  KC_P4,   KC_P5,   KC_P6,
        KC_CAPS, KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_BSPC, KC_P0,   KC_DOT
    ),

    [1] = LAYOUT(
        RESET,   _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______
    ),

};
