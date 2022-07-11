// Copyright 2022 Todd McIntire (@toddmcintire)
// SPDX-License_Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layers {
    L0,
    L1,
    L2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Base layer - ANSI QWERTY
[L0] = LAYOUT(
	KC_ESCAPE, KC_1,    KC_2,    KC_3,   KC_4,   KC_5,   KC_6,    KC_7,   KC_8,    KC_9,    KC_0,  KC_MINS, KC_EQL,KC_BSPC,
	KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
	KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_RSFT, KC_UP,  KC_SLSH,
	KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(L1), KC_LEFT, KC_DOWN, KC_RIGHT),

// // Utility layer - RGB and multimedia control
[L1] = LAYOUT(
	KC_GRV,  KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,KC_F10,KC_F11,KC_F12,KC_DEL,
	RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, ____, ____, ____, ____, RESET,
	____, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, RGB_M_TW, ____, ____,
	____, ____, ____, ____, BL_DEC, BL_TOGG, BL_INC, BL_STEP, ____, ____, ____, ____, ____, 
	____, ____, ____, ____, ____, ____, KC_HOME, ____, KC_END)
 };
