/* Copyright 2020 David Philip Barr <@davidphilipbarr>
 * Copyright 2021 @filterpaper
 * SPDX-License-Identifier: GPL-2.0+
 */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MUTE, KC_MPLY, KC_MRWD, LT(1,KC_MFFD),
        C(KC_Z), C(KC_X), C(KC_C), C(KC_V)
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______,
        QK_BOOT, _______, _______, _______
    )
};

