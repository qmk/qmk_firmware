// Copyright 2023 mjbogusz (@mjbogusz)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default layer: numpad + volume control
    [0] = LAYOUT(
                 KC_MUTE,
        TO(1),   KC_PSLS, KC_PAST, KC_PMNS,
        KC_KP_7, KC_KP_8, KC_KP_9, KC_PPLS,
        KC_KP_4, KC_KP_5, KC_KP_6,
        KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT,
        KC_KP_0,          KC_PDOT
    ),
    [1] = LAYOUT(
                 KC_MUTE,
        TO(2),   XXXXXXX, XXXXXXX, KC_VOLD,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
        KC_MRWD, KC_MPLY, KC_MFFD,
        KC_MPRV, KC_MSTP, KC_MNXT, KC_MSEL,
        XXXXXXX,          XXXXXXX
    ),
    [2] = LAYOUT(
                 RGB_MOD,
        TO(3),   KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
    [3] = LAYOUT(
                 KC_TRNS,
        TO(0),   KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [2] = { ENCODER_CCW_CW(RGB_HUI, RGB_HUD) },
    [3] = { ENCODER_CCW_CW(RGB_HUI, RGB_HUD) },
};
#endif
