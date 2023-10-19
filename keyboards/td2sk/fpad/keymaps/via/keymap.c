// Copyright 2023 td2sk (@td2sk)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum layer_names { _BASE, _1, _2, _3 };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_ortho_5x5(
        KC_MUTE, KC_MPLY, KC_BTN3, KC_BTN3, KC_NO,
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS, KC_NO,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST, RGB_TOG,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS, KC_NO,
        KC_P0,   KC_PDOT, KC_PENT, KC_PPLS, KC_NO
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = {
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU),
        ENCODER_CCW_CW(KC_MPRV, KC_MNXT),
        ENCODER_CCW_CW(KC_WH_D, KC_WH_U),
        ENCODER_CCW_CW(KC_WH_L, KC_WH_R),
        ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)
    },
};
// clang-format on

#endif
