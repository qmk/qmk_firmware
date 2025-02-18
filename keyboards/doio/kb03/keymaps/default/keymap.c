// Copyright 2025 DOIO
// Copyright 2025 ClownFish (@clownfish-og)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TO(1), KC_1,    KC_2,    KC_3,    KC_MUTE
    ),
    [1] = LAYOUT(
        TO(0), RM_VALD, RM_NEXT, RM_VALU, RM_TOGG
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RM_SATD, RM_SATU),  ENCODER_CCW_CW(RM_HUED, RM_HUEU) }
};
#endif
