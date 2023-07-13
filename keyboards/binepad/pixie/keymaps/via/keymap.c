// Copyright 2023 Binepad (@binpad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE, KC_MPLY,
        KC_MPRV, KC_MNXT
    ),

    [1] = LAYOUT(
        _______, _______,
        _______, _______
    ),

    [2] = LAYOUT(
        _______, _______,
        _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_WH_U, KC_WH_D)
    },

    [1] = {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    },

    [2] = {
        ENCODER_CCW_CW(_______, _______),
        ENCODER_CCW_CW(_______, _______)
    }
};

#endif
