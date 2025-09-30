// Copyright 2025 Enoch Chau <enoch965@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LIGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        LT(1, KC_NUM), KC_PSLS, KC_PAST, KC_MPLY,
        KC_P7, KC_P8, KC_P9, KC_PMNS,
        KC_P4, KC_P5, KC_P6, KC_PPLS,
        KC_P1, KC_P2, KC_P3, KC_PENT,
        KC_P0, KC_PDOT
    ),

    [_LIGHT] = LAYOUT(
        _______, _______, _______, _______,
        _______, BL_UP, BL_DOWN, BL_TOGG,
        _______, _______, _______, _______,
        _______, _______, _______, QK_BOOT,
        _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]  = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [_LIGHT] = {ENCODER_CCW_CW(_______, _______)}
};
#endif
