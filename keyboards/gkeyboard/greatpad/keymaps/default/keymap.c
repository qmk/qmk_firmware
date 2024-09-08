// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_MUTE,                                    RGB_TOG,
        KC_P7,    KC_P8,    KC_P9,      KC_PSLS,    KC_NUM,
        KC_P4,    KC_P5,    KC_P6,      KC_PAST,    KC_PGUP,
        KC_P1,    KC_P2,    KC_P3,      KC_PMNS,    KC_PGDN,
        KC_P0,    KC_PDOT,  KC_PENT,    KC_PPLS,    _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
};
#endif
