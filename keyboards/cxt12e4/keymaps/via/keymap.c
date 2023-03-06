// Copyright 2023 Ismaïl Senhaji (@iSma)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                 KC_BSPC, KC_7, KC_8, KC_9,
                 KC_TAB,  KC_4, KC_5, KC_6,
                 KC_0,    KC_1, KC_2, KC_3,
                 RGB_MOD, RGB_TOG, KC_MPLY, KC_MUTE
                 ),
    [1] = LAYOUT(/* LAYER 1 */
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                 ),
    [2] = LAYOUT(/* LAYER 2 */
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                 ),
    [3] = LAYOUT(/* LAYER 3 */
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
                 ),


};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU), /* top left encoder */
        ENCODER_CCW_CW(KC_MRWD, KC_MFFD), /* top right encoder */
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D), /* center encoder */
        ENCODER_CCW_CW(KC_WH_L, KC_WH_R), /* bottom encoder */
        },
    [1] = {
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* top left encoder */
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* top right encoder */
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* center encoder */
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* bottom encoder */
        },
    [2] = {
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* top left encoder */
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* top right encoder */
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* center encoder */
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* bottom encoder */
        },
    [3] = {
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* top left encoder */
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* top right encoder */
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* center encoder */
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS), /* bottom encoder */
        },
};
#endif

