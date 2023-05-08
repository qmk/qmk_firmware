// Copyright 2023 <dennis@kruyt.org>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_P1,  KC_P2, KC_P3, KC_P4,
    KC_P5,  KC_P6, KC_P7,
    KC_P8,   MO(1),   KC_P9   
  ),
  [1] = LAYOUT(
    RGB_TOG , RGB_MOD , RGB_HUI, _______,
    _______, _______, _______,
    _______, _______, _______
  ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
    [1] = { ENCODER_CCW_CW(KC_MRWD, KC_MFFD)  },
};
#endif