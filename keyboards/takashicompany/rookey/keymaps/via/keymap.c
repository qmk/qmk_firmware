// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_Q, KC_W, KC_E, KC_R,
        KC_A, KC_S, KC_D, KC_F,
        KC_V
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

    [0]     =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [1]     =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2]     =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3]     =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [4]     =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5]     =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [6]     =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [7]     =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [8]     =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [9]     =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [10]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [11]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [12]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [13]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [14]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [15]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [16]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [17]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [18]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [19]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [20]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [21]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [22]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [23]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [24]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [25]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [26]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [27]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [28]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [29]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [30]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [31]    =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }

};
#endif