// Copyright 2026 Dominic Yeap-Holliday <DoomishGuy>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_Q, KC_W,    KC_E,    KC_R,     KC_T,        KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,
        KC_A, KC_S,    KC_D,    KC_F,     KC_G,        KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z, KC_X,    KC_C,    KC_V,     KC_B,        KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLASH,
              KC_LCTL, KC_LGUI, KC_SPACE, KC_ENTER,    KC_TAB, KC_BSPC, KC_RSFT, KC_RALT
        )
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = {ENCODER_CCW_CW(KC_L, KC_R), ENCODER_CCW_CW(KC_U, KC_D)},
};
#endif
