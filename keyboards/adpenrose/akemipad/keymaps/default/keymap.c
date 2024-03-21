// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/* Keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                  MO(1),    MO(2),     MO(3),     KC_DEL,
                  KC_NUM,   KC_PSLS,   KC_PAST,   KC_PMNS,
                  KC_P7,    KC_P8,     KC_P9,     KC_PPLS,
                  KC_P4,    KC_P5,     KC_P6,     KC_PPLS,
                  KC_P1,    KC_P2,     KC_P3,     KC_PENT,
        KC_MUTE,  KC_P0,    KC_P0,     KC_PDOT,   KC_PENT 
    ),
    [1] = LAYOUT_all(
                  KC_TRNS,  CK_DOWN,   CK_UP,     CK_RST,
                  MU_TOGG,  MU_NEXT,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        CK_TOGG,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
    [2] = LAYOUT_all(
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    ),
    [3] = LAYOUT_all(
                  QK_BOOT,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
                  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS 
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [2] = { ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
    [3] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif
