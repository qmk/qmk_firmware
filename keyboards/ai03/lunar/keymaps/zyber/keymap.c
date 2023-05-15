// Copyright 2022 ZyBeR (@ZyberSE)
// SPDX-License-Identifier: GPL-2.0

#include "zyber.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT( /* Base */
		KC_ESC,  KC_1,    KC_2,    KC_3,    TD(SSHT), KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,   KC_BSPC, KC_BSPC, KC_PGUP,
		KC_TAB,           KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     TD(LBRC), KC_RBRC, KC_BSLS, KC_PGDN,
		L1_EXPL,          KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD(SCLN), TD(QUOT),          KC_ENT,  KC_DEL,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_LSFT,           KC_UP,   MO(1),
		KC_LCTL, ROPT_SRH,KC_LCMD,          _______,           LCMD_T(KC_SPC),           _______,          ROPT_SRH,  KC_GRV,   KC_LEFT, KC_DOWN, KC_RGHT
	),
	[1] = LAYOUT( /* FN */
		QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,   KC_DEL,  KC_DEL,  KC_PAUS,
		C_BLK,            _______, KC_UP,   _______,  _______, _______, KC_NUM,  KC_P7,   KC_P8,   KC_P9,   KC_MPRV,  KC_MPLY,  KC_MNXT, _______, KC_SCRL,
		_______,          KC_LEFT, KC_DOWN, KC_RGHT,  _______, KC_VOLD, KC_VOLU, KC_P4,   KC_P5,   KC_P6,   _______,  _______,           _______, _______,
		_______,          KC_RCTL, KC_RGUI, KC_RALT,  _______, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   _______,  _______,           KC_PGUP, _______,
		_______, _______, _______,          _______,           _______,          _______,                   _______,  _______,  KC_HOME, KC_PGDN, KC_END
	)
};

