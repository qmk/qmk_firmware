// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4,
        KC_TAB, KC_Q, KC_W, KC_ENT,
        KC_LCTL, KC_A, KC_S, KC_RSFT
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) }
};
#endif
