/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum {
    _L0,
    _L1
} keyboard_layers;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_L0] = LAYOUT_ortho_1x1(
        LT(_L1, KC_MUTE)
    ),

    [_L1] = LAYOUT_ortho_1x1(
        _______
    )
};

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_L0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_L1] = { ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP) }
};

#endif
