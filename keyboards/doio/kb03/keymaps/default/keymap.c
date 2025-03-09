// Copyright 2025 DOIO
// Copyright 2025 ClownFish (@clownfish-og)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum my_layers {
    _BASE,
    _LAYER1,
    _LAYER2,
    _LAYER3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        TO(_LAYER1), KC_1,    KC_2,    KC_3,    KC_ENT
    ),
    [_LAYER1] = LAYOUT(
        TO(_LAYER2), MS_BTN1, MS_BTN3, MS_BTN2, KC_LCTL
    ),
    [_LAYER2] = LAYOUT(
        TO(_LAYER3), KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE
    ),
    [_LAYER3] = LAYOUT(
        TO(_BASE), RM_VALD, RM_NEXT, RM_VALU, RM_TOGG
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLL, MS_WHLR) },
    [_LAYER1] = { ENCODER_CCW_CW(MS_LEFT, MS_RGHT), ENCODER_CCW_CW(MS_UP, MS_DOWN) },
    [_LAYER2] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_LAYER3] = { ENCODER_CCW_CW(RM_SATD, RM_SATU), ENCODER_CCW_CW(RM_HUED, RM_HUEU) }
};
#endif
