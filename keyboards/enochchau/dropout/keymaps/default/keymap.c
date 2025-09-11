// Copyright 2025 Enoch Chau <enoch965@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _LIGHT,
    _EMPTY
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_ortho_5x4(
        LT(1, KC_NUM), KC_PSLS, KC_PAST, KC_MPLY,
        KC_P7, KC_P8, KC_P9, KC_PMNS,
        KC_P4, KC_P5, KC_P6, KC_PPLS,
        KC_P1, KC_P2, KC_P3, _______,
        KC_P0, _______, KC_PDOT, KC_PENT
    ),

    [_LIGHT] = LAYOUT_ortho_5x4(
        _______, _______, _______, _______,
        _______, BL_UP, BL_DOWN, BL_TOGG,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, QK_BOOT
    ),

    [_EMPTY] = LAYOUT_ortho_5x4( // empty layer
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    )
};

bool led_update_user(led_t led_state) {
    return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]  = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [_LIGHT] = {ENCODER_CCW_CW(_______, _______)},
    [_EMPTY] = {ENCODER_CCW_CW(_______, _______)},
};
#endif
