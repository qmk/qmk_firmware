// Copyright 2023 Treasure
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_3x3(
        MO(1),   KC_MPLY, RM_TOGG,
        KC_VOLD, KC_MUTE, KC_VOLU,
        KC_KP_1, KC_KP_2, KC_KP_3
    ),

    [1] = LAYOUT_ortho_3x3(
        KC_TRNS, RGB_M_P, MO(2),
        RM_NEXT, RM_HUEU, RM_VALU,
        RM_PREV, RM_HUED, RM_VALD
    ),

    [2] = LAYOUT_ortho_3x3(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, MO(3)
    ),

    [3] = LAYOUT_ortho_3x3(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        QK_BOOT, KC_TRNS, KC_TRNS
    )
};
