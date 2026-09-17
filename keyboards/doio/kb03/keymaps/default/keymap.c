// Copyright 2025 DOIO
// Copyright 2025 ClownFish (@clownfish-og)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum my_layers {
    _BASE,
    _MOUSE,
    _MEDIA,
    _LIGHTS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        TO(_MOUSE),
        KC_1,    KC_2,    KC_3,
                 KC_ENT
    ),
    [_MOUSE] = LAYOUT(
        TO(_MEDIA),
        MS_BTN1, MS_BTN3, MS_BTN2,
                 KC_LCTL
    ),
    [_MEDIA] = LAYOUT(
        TO(_LIGHTS),
        KC_MRWD, KC_MPLY, KC_MFFD,
                 KC_MUTE
    ),
    [_LIGHTS] = LAYOUT(
        TO(_BASE),
        RM_VALD, RM_NEXT, RM_VALU,
                 RM_TOGG
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD), ENCODER_CCW_CW(MS_WHLL, MS_WHLR) },
    [_MOUSE]  = { ENCODER_CCW_CW(MS_LEFT, MS_RGHT), ENCODER_CCW_CW(MS_UP, MS_DOWN) },
    [_MEDIA]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_LIGHTS] = { ENCODER_CCW_CW(RM_SATD, RM_SATU), ENCODER_CCW_CW(RM_HUED, RM_HUEU) }
};
#endif
