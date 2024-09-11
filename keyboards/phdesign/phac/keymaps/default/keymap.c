// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BL,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BL] = LAYOUT(
                    KC_B,
        KC_S,   KC_D,   KC_K,   KC_L,
            KC_V,           KC_N
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BL] = { ENCODER_CCW_CW(MS_UP, MS_DOWN),  ENCODER_CCW_CW(MS_LEFT, MS_RGHT)  },
};
#endif