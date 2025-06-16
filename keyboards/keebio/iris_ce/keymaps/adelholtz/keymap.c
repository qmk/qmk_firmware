// Copyright 2023 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_german.h"

// Layer detinitoins
#define COLEMAK    0
#define NAVIGATION 1
#define BRACKETS   2
#define EXTRA      OSL(3)

enum custom_keycodes {
  LMAGIC = SAFE_RANGE,
  RMAGIC,
  MLCURLY
};

#define MLCURLY ALGR(DE_8)

enum custom_layers {
     _COLEMAK,
     _NAVIGATION,
     _BRACKETS,
     _EXTRA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT(
     QK_GESC, KC_1, KC_2, KC_3,                         KC_4, KC_5,                             KC_6,              KC_7, KC_8,              KC_9,   KC_0,    KC_BSPC,
     KC_TAB,  DE_Q, DE_W, DE_F,                         DE_P, DE_G,                             DE_J,              DE_L, DE_U,              DE_Y,   DE_ODIA, DE_UDIA,
     KC_LCTL, DE_A, DE_R, MT(MOD_LALT | MOD_RALT,DE_S), DE_T, DE_D,                             MT(MOD_LGUI,DE_H), DE_N, MT(MOD_LCTL,DE_E), DE_I,   DE_O,    DE_ADIA,
     KC_LSFT, DE_Z, DE_X, DE_C,                         DE_V, DE_B,       KC_HOME, KC_END,      DE_K,              DE_M, DE_COMM,           KC_DOT, KC_SLSH, KC_CAPS,
                                             LT(_NAVIGATION,KC_ENTER), LMAGIC, LT(_BRACKETS,KC_SPC), OSM(MOD_LSFT), RMAGIC, OSL(_EXTRA)
  ),

  [_NAVIGATION] = LAYOUT(
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     _______,  XXXXXXX, KC_PGDN, KC_UP,   KC_PGUP, XXXXXXX,                               XXXXXXX, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PGDN,
     _______,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                                KC_RBRC, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, KC_PIPE,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         TO(0), _______,       KC_RCBR, KC_P1,   KC_P2,   KC_P3,   DE_SS,   _______,
                                              _______, _______,  KC_DEL, KC_DEL, _______, KC_P0
  ),

  [_BRACKETS] = LAYOUT(
     KC_F12, KC_F1,    KC_F2,      KC_F3,      KC_F4,   KC_F5,                           KC_F6,   KC_F7,   KC_F8,      KC_F9,      KC_F10,  KC_F11,
     _______, XXXXXXX, XXXXXXX,    XXXXXXX,    DE_LABK, XXXXXXX,                         XXXXXXX, DE_RABK, XXXXXXX,    XXXXXXX,    XXXXXXX, QK_BOOT,
     _______, XXXXXXX, MLCURLY,    ALGR(DE_5), DE_LPRN, XXXXXXX,                         XXXXXXX,  DE_RPRN, ALGR(DE_6), ALGR(DE_9), XXXXXXX, KC_BSLS,
     _______, XXXXXXX, ALGR(DE_7), XXXXXXX,    XXXXXXX, XXXXXXX,    TO(0), _______,      XXXXXXX, DE_EQL,  ALGR(DE_0), XXXXXXX,    XXXXXXX, XXXXXXX,
                                                _______, _______, KC_BSPC, KC_BSPC, QK_AREP, _______
  ),


  [_EXTRA] = LAYOUT(
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                      RM_NEXT, RM_PREV, RM_VALU, RM_VALD, RM_SPDU,    RM_SPDD,
     _______, XXXXXXX, KC_GRV, KC_TILD, KC_PLUS, XXXXXXX,                      XXXXXXX, DE_BSLS, XXXXXXX, XXXXXXX, RM_HUEU,    RM_HUED,
     _______, DE_EQL,  DE_PERC, DE_EXLM, DE_DQUO, DE_DLR,                       DE_AMPR, DE_SLSH, DE_QUES, DE_HASH, ALGR(DE_7), DE_SECT,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, XXXXXXX,    TO(0), _______,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DE_PIPE,    RM_TOGG,
                                          _______, _______, _______, _______, _______, _______
  )
};

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
	switch (keycode) {
		case CW_TOGG:
        case KC_ESC:
        case KC_BSPC:
        case KC_DEL:

        case LMAGIC:
        case RMAGIC:
            return false;  // Magic keys will ignore the above keycodes.
    }
    return true;  // Other keys can be repeated.
}

// An enhanced version of SEND_STRING: the last key is set such that if
// the Repeat Key is pressed next, it produces `repeat_keycode`.
#define MAGIC_STRING(str, repeat_keycode) \
		magic_send_string_P(PSTR(str), (repeat_keycode))

static void magic_send_string_P(const char* str, uint16_t repeat_keycode) {
  send_string_with_delay_P(str, TAP_CODE_DELAY);  // Send the string.
  set_last_keycode(repeat_keycode); // 2024-03-09 Disabled sending of string for mag-rep / rep-mag consistency.

}


static void process_left_magic(uint16_t keycode, uint8_t mods) { // LMAGIC definitions
    switch (keycode) {
	//case HRL_A: { MAGIC_STRING("a", 		KC_SPC); } break;
	case  KC_B: { MAGIC_STRING("ecause",	KC_NO); } break;
	case  KC_C: { MAGIC_STRING("an",		KC_NO); } break;
	//case HRL_D: { MAGIC_STRING("d", 		KC_NO); } break;
	case KC_E: { MAGIC_STRING("e",			KC_NO); } break;
	//case  KC_F: { MAGIC_STRING("f", 		KC_NO); } break;
	case  KC_G: { MAGIC_STRING("eneral", 	KC_NO); } break;
	//case HRM_H: { MAGIC_STRING("h", 		KC_NO); } break;
	case KC_I: { MAGIC_STRING("on", 		KC_NO); } break;
	case  KC_J: { MAGIC_STRING("ust",		KC_NO); } break;
	//case  KC_K: { MAGIC_STRING("k", 		KC_NO); } break;
	case  KC_L: { MAGIC_STRING("l", 		KC_NO); } break;
	case  KC_M: { MAGIC_STRING("ent",		KC_NO); } break;
	//case  KC_N: { MAGIC_STRING("ion",		KC_NO); } break;
	case  KC_O: { MAGIC_STRING("o", 		KC_NO); } break;
	case  KC_P: { MAGIC_STRING("retty",    	KC_NO); } break;
	case  KC_Q: { MAGIC_STRING("q", 		KC_NO); } break;
	//case HRM_R: { MAGIC_STRING("r", 		KC_NO); } break;
	//case HRM_S: { MAGIC_STRING("s", 		KC_NO); } break;
        case  KC_T: { MAGIC_STRING("t", 		KC_NO); } break;
	case  KC_U: { MAGIC_STRING("u", 		KC_NO); } break;
	//case HRM_V: { MAGIC_STRING("azjorfia",	KC_NO); } break;
	case  KC_W: { MAGIC_STRING("hich",		KC_NO); } break;
	//case HRM_X: { MAGIC_STRING("x", 		KC_NO); } break;
	case  KC_Y: { MAGIC_STRING("y", 		KC_NO); } break;
	case  KC_Z: { MAGIC_STRING("z", 		KC_NO); } break;

	case KC_COMM: { MAGIC_STRING(" and",    KC_NO); } break;
    }
}

static void process_right_magic(uint16_t keycode, uint8_t mods) { // RMAGIC definitions
    switch (keycode) {
       	case KC_A: { MAGIC_STRING("nd",    	KC_SPC); } break;
    	case  KC_B: { MAGIC_STRING("b", 		KC_NO); } break;
    	case  KC_C: { MAGIC_STRING("c", 		KC_NO); } break;
    	//case HRL_D: { MAGIC_STRING("d", 		KC_NO); } break;
    	case  KC_E: { MAGIC_STRING("e", 		KC_NO); } break;
    	case  KC_F: { MAGIC_STRING("f", 		KC_NO); } break;
    	case  KC_G: { MAGIC_STRING("g", 		KC_NO); } break;
    	//case HRM_H: { MAGIC_STRING("h", 		KC_NO); } break;
    	case KC_I: { MAGIC_STRING("on",    	KC_NO); } break;
    	case  KC_J: { MAGIC_STRING("j", 		KC_NO); } break;
    	case  KC_K: { MAGIC_STRING("k", 		KC_NO); } break;
    	//case HRM_L: { MAGIC_STRING("l", 		KC_NO); } break;
    	case  KC_M: { MAGIC_STRING("m", 		KC_NO); } break;
    	case  KC_N: { MAGIC_STRING("n", 		KC_NO); } break;
    	//case  KC_O: { MAGIC_STRING("o", 		KC_NO); } break;
    	case  KC_P: { MAGIC_STRING("p", 		KC_NO); } break;
    	case  KC_Q: { MAGIC_STRING("ueen",		KC_NO); } break;
    	case KC_R: { MAGIC_STRING("r", 		KC_NO); } break;
    	case KC_S: { MAGIC_STRING("s", 		KC_NO); } break;
    	case  DE_T: { MAGIC_STRING("t", 		KC_NO); } break;
    	//case  KC_U: { MAGIC_STRING("u", 		KC_NO); } break;
       	//case HRM_V: { MAGIC_STRING("v", 		KC_NO); } break;
       	case  DE_W: { MAGIC_STRING("w", 		KC_NO); } break;
    	//case HRM_X: { MAGIC_STRING("ex",    	KC_NO); } break;
    	case  KC_Y: { MAGIC_STRING("eah",    	KC_NO); } break;
    	//case  KC_Z: { MAGIC_STRING("z", 		KC_NO); } break;
    	case KC_COMM: { MAGIC_STRING(" but",    KC_NO); } break;
    	case  KC_SPC: { MAGIC_STRING("the", 	KC_NO); } break;
        case MLCURLY: { SEND_STRING("TEST"); } break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (record->event.pressed){
  	switch (keycode) {
       	 	case LMAGIC: { process_left_magic(get_last_keycode(), get_last_mods()); set_last_keycode(KC_SPC); } return false;
        	case RMAGIC: { process_right_magic(get_last_keycode(), get_last_mods()); set_last_keycode(KC_SPC); } return false;
	}
  }

  return true;
}
