// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE,
        KC_P1,    KC_P2,    KC_P3,
        KC_P4,    KC_P5,    KC_P6,
        KC_P7,    KC_P8,    LT(1, KC_P9)
    ),
    [1] = LAYOUT(
        RM_TOGG,
        RM_HUEU,  RM_SATU,  RM_SPDU,
        RM_HUED,  RM_SATD,  RM_SPDD,
        RM_PREV,  RM_NEXT,  _______
    )
};

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RM_VALD, RM_VALU) }
};

#endif
