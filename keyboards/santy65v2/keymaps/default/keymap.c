// Copyright 2023-2026 Santiago Garcia (@santy81855)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
	    KC_F15, KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                         KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_TRNS, 
	    KC_F16, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                               KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_TRNS, 
	    KC_F17, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G,                              KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_TRNS, 
	    KC_F18, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                              KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, 
	    KC_TRNS, KC_LCTL, KC_LGUI, KC_LALT, KC_SPACE, KC_SPACE, KC_TRNS,		        KC_SPACE, KC_SPACE, KC_MPLY, KC_VOLD, KC_VOLU, KC_LEFT, KC_DOWN, KC_RIGHT
	)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(C(KC_PGUP), C(KC_PGDN)) }
};
#endif
