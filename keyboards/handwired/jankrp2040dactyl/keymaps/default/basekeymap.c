// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
  _BASELAYER,
  _SYMBOLLAYER,
  _BOOTLAYER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASELAYER] = LAYOUT(
        KC_GRV, KC_1,  	KC_2,   KC_3,	KC_4, 	KC_5, 	    KC_6,	KC_7,	KC_8,	KC_9,	KC_0,	KC_EQUAL,
        KC_BSLS,KC_B,  	KC_Y,   KC_O, 	KC_U,	KC_QUOT,    KC_SCLN,KC_L,	KC_D,	KC_W,	KC_V,	KC_Z,
        KC_LSFT,KC_C, 	KC_I,   KC_E,	KC_A, 	KC_COMM,    KC_DOT,	KC_H,	KC_T,	KC_S,	KC_N,	KC_Q,
        KC_RSFT,KC_G, 	KC_X,   KC_J,	KC_K, 	KC_MINS,    KC_SLSH,KC_R,	KC_M,	KC_F,	KC_P,	KC_LALT,

				                KC_BSPC, KC_DEL, KC_ESC,     KC_ENT, KC_SPC, KC_TAB,
					                    TG(1), KC_UP,	    KC_DOWN, KC_LEFT,XXXXXXX,XXXXXXX
    ),
    [_SYMBOLLAYER] = LAYOUT(
        KC_GRV, KC_1,  	KC_2,   KC_3,	KC_4, 	KC_5, 	    KC_6,	KC_7,	KC_8,	KC_9,	KC_0,	KC_EQUAL,
        KC_BSLS,KC_B,  	KC_Y,   KC_O, 	KC_U,	KC_QUOT,    KC_SCLN,KC_L,	KC_D,	KC_W,	KC_V,	KC_Z,
        KC_LSFT,KC_C, 	KC_I,   KC_E,	KC_A, 	KC_COMM,    KC_DOT,	KC_H,	KC_T,	KC_S,	KC_N,	KC_Q,
        KC_RSFT,KC_G, 	KC_X,   KC_J,	KC_K, 	KC_MINS,    KC_SLSH,KC_R,	KC_M,	KC_F,	KC_P,	KC_LALT,

				                KC_BSPC, KC_DEL, KC_ESC,     KC_ENT, KC_SPC, KC_TAB,
					                    TG(0), KC_UP,	    KC_DOWN, MO(2),XXXXXXX,XXXXXXX
    ),
    [_BOOTLAYER] = LAYOUT(
        QK_BOOT,KC_1,  	KC_2,   KC_3,	KC_4, 	KC_5, 	    KC_6,	KC_7,	KC_8,	KC_9,	KC_0,	KC_EQUAL,
        KC_BSLS,KC_B,  	KC_Y,   KC_O, 	KC_U,	KC_QUOT,    KC_SCLN,KC_L,	KC_D,	KC_W,	KC_V,	KC_Z,
        KC_LSFT,KC_C, 	KC_I,   KC_E,	KC_A, 	KC_COMM,    KC_DOT,	KC_H,	KC_T,	KC_S,	KC_N,	KC_Q,
        KC_RSFT,KC_G, 	KC_X,   KC_J,	KC_K, 	KC_MINS,    KC_SLSH,KC_R,	KC_M,	KC_F,	KC_P,	KC_LALT,

				                KC_BSPC, KC_DEL, KC_ESC,     KC_ENT, KC_SPC, KC_TAB,
					                    KC_RGHT, KC_UP,	    KC_DOWN, KC_LEFT,XXXXXXX,XXXXXXX
    )
};
