// Copyright 2021 Paul Maria Scheikl (@ScheiklP)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "keymap_german.h"

// Layer shorthand
#define _QWZ 0
#define _FNC 1
#define _AGR 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


	[_QWZ] = {
	{ KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,     KC_5,     DE_CIRC, DE_UNDO,  KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    DE_SS,   DE_ACUT},
	{ KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,     DE_COPY, DE_PASTE, DE_Z,   KC_U,   KC_I,    KC_O,    KC_P,    DE_UDIA, DE_PLUS},
	{ KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,     KC_DEL,  KC_BSPC,  KC_H,   KC_J,   KC_K,    KC_L,    DE_ODIA, DE_ADIA, DE_HASH},
    { KC_LSFT, DE_Y,    KC_X,    KC_C,    KC_V,     KC_B,     KC_DOWN, KC_UP,    KC_N,   KC_M,   KC_COMM, KC_DOT,  DE_MINS, KC_TRNS, KC_RSFT},
    { KC_LCTL, DE_LABK, KC_HOME, KC_LALT, KC_ENTER, KC_ENTER, KC_LEFT, KC_RIGHT, KC_SPC, KC_SPC, MO(2),   KC_TRNS, KC_TRNS, KC_TRNS, MO(1) },
    },

	[_FNC] = {
	{ QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,    KC_TRNS, KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12},
	{ KC_TAB,  DE_AT,   KC_TRNS, DE_EURO, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DE_TILD },
	{ KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS },
	{ KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT },
	{ KC_LCTL, DE_PIPE, KC_HOME, KC_LALT, KC_ENTER, KC_ENTER, KC_LEFT, KC_RIGHT, KC_SPC, KC_SPC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS },
	},

    [_AGR] = {

    { KC_ESC,  KC_TRNS, DE_SUP2, DE_SUP3, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, DE_LCBR, DE_LBRC, DE_RBRC, DE_RCBR, DE_BSLS, KC_TRNS},
	{ KC_TAB,  DE_AT,   KC_TRNS, DE_EURO, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, DE_TILD },
	{ KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS },
	{ KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT },
	{ KC_LCTL, DE_PIPE, KC_HOME, KC_LALT, KC_ENTER, KC_ENTER, KC_LEFT, KC_RIGHT, KC_SPC, KC_SPC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS },
	},

};
