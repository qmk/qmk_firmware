// Copyright 2024  Evgeny Kapusta (@ryodeushii)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gem80-common.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "common/keycodes.h"
#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// layer Mac
[0] = LAYOUT_tkl_f13_ansi(
	KC_ESC, 	KC_BRMD,  	KC_BRMU,  	MAC_TASK, 	MAC_SEARCH, MAC_VOICE,  MAC_DND,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	KC_DEL, 	MAC_PRTA,   KC_F14,		KC_F13,
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_INS,		KC_HOME,	KC_PGUP,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_DEL,		KC_END,		KC_PGDN,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 				KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LOPT,	KC_LCMD,										KC_SPC, 							KC_RCMD,	KC_ROPT,	MO(1),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
// layer Mac Fn
#if(WORK_MODE == THREE_MODE)
[1] = LAYOUT_tkl_f13_ansi(
	TOG_BAT_IND_NUM, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	TG(7),	    MAC_PRT,    _______,		_______,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______,    _______, 	    DEBOUNCE_PRESS_DEC,	    DEBOUNCE_PRESS_SHOW,	DEBOUNCE_PRESS_INC,
    _______, 	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	TOG_DEEP_SLEEP,  	TOG_USB_SLP,   	DEV_RESET,	SLEEP_MODE, BAT_SHOW,	DEBOUNCE_RELEASE_DEC,	DEBOUNCE_RELEASE_SHOW,	DEBOUNCE_RELEASE_INC,
	TOG_CAPS_IND,	SLEEP_TIMEOUT_DEC,   	SLEEP_TIMEOUT_SHOW,   	SLEEP_TIMEOUT_INC,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,    _______,   	MO(5),		MO(4), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(1),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#else
[1] = LAYOUT_tkl_f13_ansi(
	_______, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	TG(7),	    MAC_PRT,    _______,		_______,
	_______,    _______,    _______,    _______,    _______,  	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______,    _______, 	    DEBOUNCE_PRESS_DEC,	    DEBOUNCE_PRESS_SHOW,	DEBOUNCE_PRESS_INC,
    _______, 	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	TOG_USB_SLP,   	DEV_RESET,	SLEEP_MODE, 	_______,	DEBOUNCE_RELEASE_DEC,	DEBOUNCE_RELEASE_SHOW,	DEBOUNCE_RELEASE_INC,
	TOG_CAPS_IND,	SLEEP_TIMEOUT_DEC,   	SLEEP_TIMEOUT_SHOW,   	SLEEP_TIMEOUT_INC,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,    _______,   	MO(5),		MO(4), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(1),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#endif
// layer win
[2] = LAYOUT_tkl_f13_ansi(
	KC_ESC, 	KC_F1,  	KC_F2,  	KC_F3, 		KC_F4,  	KC_F5,  	KC_F6,  	KC_F7,  	KC_F8,  	KC_F9, 		KC_F10, 	KC_F11, 	KC_F12, 	KC_DEL, 	WIN_PRTA,   KC_F14,     KC_F13,
	KC_GRV, 	KC_1,   	KC_2,   	KC_3,  		KC_4,   	KC_5,   	KC_6,   	KC_7,   	KC_8,   	KC_9,  		KC_0,   	KC_MINS,	KC_EQL, 	KC_BSPC,	KC_INS,		KC_HOME,	KC_PGUP,
	KC_TAB, 	KC_Q,   	KC_W,   	KC_E,  		KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,   	KC_O,  		KC_P,   	KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_DEL,		KC_END,		KC_PGDN,
	KC_CAPS,	KC_A,   	KC_S,   	KC_D,  		KC_F,   	KC_G,   	KC_H,   	KC_J,   	KC_K,   	KC_L,  		KC_SCLN,	KC_QUOT, 	 			KC_ENT,
	KC_LSFT,				KC_Z,   	KC_X,   	KC_C,  		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM,	KC_DOT,		KC_SLSH,				KC_RSFT,				KC_UP,
	KC_LCTL,	KC_LWIN,	KC_LALT,										KC_SPC, 							KC_RALT,	KC_RWIN,	MO(3),   	KC_RCTL,				KC_LEFT,	KC_DOWN,    KC_RGHT),
// layer win Fn
#if(WORK_MODE == THREE_MODE)
[3] = LAYOUT_tkl_f13_ansi(
	TOG_BAT_IND_NUM, 	KC_BRID,  	KC_BRIU,  	SOCDON, 	SOCDOFF,  	SOCDTOG,  	_______,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	TG(7),	   	KC_PSCR,    KC_TRNS,    WIN_LOCK,
	_______, 	LNK_BLE1,  	LNK_BLE2,  	LNK_BLE3,  	LNK_RF,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______,    _______, 	    DEBOUNCE_PRESS_DEC,	    DEBOUNCE_PRESS_SHOW,	DEBOUNCE_PRESS_INC,
    _______, 	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	TOG_DEEP_SLEEP,  	TOG_USB_SLP,   	DEV_RESET,	SLEEP_MODE, BAT_SHOW,	DEBOUNCE_RELEASE_DEC,	DEBOUNCE_RELEASE_SHOW,	DEBOUNCE_RELEASE_INC,
	TOG_CAPS_IND,	SLEEP_TIMEOUT_DEC,   	SLEEP_TIMEOUT_SHOW,   	SLEEP_TIMEOUT_INC,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	MO(5),		MO(4), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(3),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#else
[3] = LAYOUT_tkl_f13_ansi(
	_______, 	KC_BRID,  	KC_BRIU,  	SOCDON, 	SOCDOFF,  	SOCDTOG,  	_______,  	KC_MPRV,  	KC_MPLY,  	KC_MNXT, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	TG(7),	   	KC_PSCR,    KC_TRNS,    WIN_LOCK,
	_______,    _______,    _______,    _______,    _______,  	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______,    _______, 	    DEBOUNCE_PRESS_DEC,	    DEBOUNCE_PRESS_SHOW,	DEBOUNCE_PRESS_INC,
    _______, 	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	TOG_USB_SLP,   	DEV_RESET,	SLEEP_MODE, 	_______,	DEBOUNCE_RELEASE_DEC,	DEBOUNCE_RELEASE_SHOW,	DEBOUNCE_RELEASE_INC,
	TOG_CAPS_IND,	SLEEP_TIMEOUT_DEC,   	SLEEP_TIMEOUT_SHOW,   	SLEEP_TIMEOUT_INC,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	MO(5),		MO(4), 		RGB_SPD,	RGB_SPI,	_______,				_______,				RGB_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(3),		_______,				RGB_MOD,    RGB_VAD,	RGB_HUI),
#endif
// layer 4
[4] = LAYOUT_tkl_f13_ansi(
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	RGB_TEST,  	_______,   	_______,   	_______,	_______, 	SIDE_SPD,	SIDE_SPI,	_______,				_______,				SIDE_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(4),		_______,				SIDE_MOD,   SIDE_VAD,	SIDE_HUI),
// layer 4
[5] = LAYOUT_tkl_f13_ansi(
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______, 	AMBIENT_SPD,	AMBIENT_SPI,	_______,				_______,				AMBIENT_VAI,
	_______,	_______,	_______,										_______, 							_______,	_______,   	MO(5),		_______,				AMBIENT_MOD,   AMBIENT_VAD,	AMBIENT_HUI),
[7] = LAYOUT_tkl_f13_ansi(
	_______, 	_______,  	_______,  	_______, 	_______,  	_______,  	_______,  	_______,  	_______,  	_______, 	_______, 	_______, 	_______, 	TG(7),	    _______,	_______,	_______,
	_______, 	_______,   	_______,   	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	KC_F24, 	_______,  	_______,  	_______,  	_______,   	_______,   	_______,   	_______,   	_______,   	_______,  	_______,   	_______,	_______, 	_______,	_______,	_______,	_______,
	_______,	_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______,   	_______,   	_______,  	_______,	_______, 	 			_______,
	_______,				_______,   	_______,   	_______,  	_______,   	_______,   	_______,	_______, 	_______,	_______,	_______,				_______,				_______,
	_______,	_______,	_______,										_______, 							_______,	_______,   	_______,		_______,			_______,    _______,	_______),
};
// clang-format on
