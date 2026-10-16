// Copyright 2026 juarendra
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names { _LAY0, _LAY1, _LAY2, _LAY3, _LAY4, _LAY5 };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAY0] = LAYOUT(
        TO(1), KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,   KC_F6,   KC_F7,   KC_F8,      KC_F9,   KC_F10,  KC_F11,  KC_F12),
    [_LAY1] = LAYOUT(
        TO(2), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_LAY2] = LAYOUT(
        TO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_LAY3] = LAYOUT(
        TO(4), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_LAY4] = LAYOUT(
        TO(5), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [_LAY5] = LAYOUT(
        TO(0), RM_TOGG, RM_NEXT, RM_SPDU, RM_SPDD,    RM_SATU, RM_SATD, RM_HUEU, RM_HUED,    RM_VALU, RM_VALD, KC_TRNS, KC_TRNS)
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAY0] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [_LAY1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY4] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_LAY5] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
// clang-format on
#endif
