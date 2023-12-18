// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_MUTE,                                    RGB_TOG,
        KC_P7,    KC_P8,    KC_P9,      KC_PSLS,    KC_NUM,
        KC_P4,    KC_P5,    KC_P6,      KC_PAST,    KC_PGUP,
        KC_P1,    KC_P2,    KC_P3,      KC_PMNS,    KC_PGDN,
        KC_P0,    KC_PDOT,  KC_PENT,    KC_PPLS,    TO(1)
    ),
    [1] = LAYOUT(
        KC_TRNS,                                    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    TO(2)
    ),
    [2] = LAYOUT(
        KC_TRNS,                                    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    TO(3)
    ),
    [3] = LAYOUT(
        KC_TRNS,                                    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    TO(4)
    ),
    [4] = LAYOUT(
        KC_TRNS,                                    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    TO(5)
    ),
    [5] = LAYOUT(
        KC_TRNS,                                    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    TO(6)
    ),
    [6] = LAYOUT(
        KC_TRNS,                                    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    TO(7)
    ),
    [7] = LAYOUT(
        KC_TRNS,                                    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    TO(8)
    ),
    [8] = LAYOUT(
        KC_TRNS,                                    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    TO(9)
    ),
    [9] = LAYOUT(
        KC_TRNS,                                    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,    TO(0)
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
    [1] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [4] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [6] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [7] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [8] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [9] =  { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif
