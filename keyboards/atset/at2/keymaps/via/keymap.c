/* Copyright 2024 Atset (@anubhavd7) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum {
    _L0,
    _L1
} keyboard_layers;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_ortho_1x1(
        KC_MUTE, KC_MPLY
    ),
    [_L1] = LAYOUT_ortho_1x1(
        KC_A, KC_B
    )
};

