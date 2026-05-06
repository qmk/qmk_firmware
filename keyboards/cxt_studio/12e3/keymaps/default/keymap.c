// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum my_layers {
    _BASE,
    _RGBL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC, C(KC_X), C(KC_C), C(KC_V),  MS_BTN3, RM_TOGG,
        KC_PSCR,C(KC_Z), KC_CALC, KC_MNXT,     KC_MPLY,
        MO(1), KC_LGUI, KC_DEL, KC_APP
    ),

    [_RGBL] = LAYOUT(
        RM_NEXT, RM_SATU, KC_INS,  KC_DEL,   _______, _______,
        RM_PREV, RM_SATD, KC_PGUP, KC_HOME,     KC_MUTE,
        _______, QK_BOOT, KC_PGDN, KC_END
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    // Encoders: Left, Right, Big
    [_BASE] = {
        ENCODER_CCW_CW(MS_WHLD, MS_WHLU),
        ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
    },
    [_RGBL] = {
        ENCODER_CCW_CW(RM_HUED, RM_HUEU),
        ENCODER_CCW_CW(RM_SPDD, RM_SPDU),
        ENCODER_CCW_CW(RM_VALD, RM_VALU)
    },
};
#endif
