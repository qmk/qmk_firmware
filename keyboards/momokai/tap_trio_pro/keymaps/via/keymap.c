// Copyright 2023 peepeetee
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                KC_MUTE,
        KC_Z,   KC_X,   KC_C,
        KC_GRV,   KC_ESC,   KC_F2
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0]   =  { ENCODER_CCW_CW(KC_VOLD,  KC_VOLU) },
};
#endif
