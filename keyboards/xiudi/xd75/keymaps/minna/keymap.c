// Copyright 2022 Minna Pallari (@pallarim)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_finnish.h"

enum unicode_names {
    BEER,
    BEERS
};

enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
};

const uint32_t PROGMEM unicode_map[] = {
    [BEER]  = 0x1F37A,  // 🍺
    [BEERS] = 0x1F37B   // 🍻
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
		switch(keycode) {
			case QMKBEST:
				SEND_STRING(SS_LGUI("r") SS_DELAY(500) "calc\n" SS_DELAY(1000) "1337");
                break;
		}
	}
	return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │ESC│ § | 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ + │ ´ │BS │
 * ├───|───|───|───|───|───|───|───|───|───|───|───|───|───|───|
 * │TAB    | Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ Å │ ¨ │   │
 * ├───|───|───|───|───|───|───|───|───|───|───|───|───|───|ENT|
 * │CPS    │ A │ S │ D │ F │ G │ H │ J │ K │ L │ Ö │ Ä │ ' │   │
 * ├───|───|───|───|───|───|───|───|───|───|───|───|───|───|───|
 * │SFT│ < │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ - │SFT|UP |   │
 * ├───|───|───|───|───|───|───|───|───|───|───|───|───|───|───|
 * │CTR│FN │WIN│ALT│BER│  SPC  │  SPC  │AGR│MNU│CTR│LF │DN │RG │
 * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
 */

	[0] = LAYOUT_ortho_5x15(
   KC_ESC, FI_SECT, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, FI_PLUS, FI_ACUT, KC_BSPC,
   KC_TAB, KC_NO, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, FI_ARNG, FI_DIAE, KC_ENT, 
   KC_CAPS, KC_NO, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, FI_ODIA, FI_ADIA, FI_QUOT, KC_NO,
   KC_LSFT, FI_LABK, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, FI_MINS, KC_RSFT, KC_UP, KC_NO,
   KC_LCTL, MO(1), KC_LGUI, KC_LALT, XP(BEER, BEERS), KC_SPC, KC_NO, KC_SPC, KC_NO, KC_RALT, KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

/*
 * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │Mute│CAL| F1│F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│DEL│
 * ├────|───|───|───|───|───|───|───|───|───|───|───|───|───|───|
 * │MSel    |My │Ma │RGB│RGB│Cal│ 7 │ 8 │ 9 │ - │   │Prn│SL │ P │
 * │        |Cmp│il │HUD│HUI│   │   │   │   │   │   │Scr│CK │ a │
 * ├────|───|───|───|───|───|───|───|───|───|───|───|───|───| u |
 * │MPrev   │   │   │RGB│RGB│   │ 4 │ 5 │ 6 │ + │RST│   │   │ s │
 * │        │NXT│STP│SAD│SAI│PLY│   │   │   │   │   │   │   │ e │
 * ├────|───|───|───|───|───|───|───|───|───|───|───|───|───|───|
 * │Vo- │Mte│Vo+│App│RGB│RGB│   │ 1 │ 2 │ 3 │ENT│   │   |   |   │
 * │    │   │   │   │VAD│VAI│   │ 1 │ 2 │ 3 │ENT│   │   |   |   │
 * ├────|───|───|───|───|───|───|───|───|───|───|───|───|───|───|
 * │    │FN │RGB│   │RMR│RGB_MOD│ 0     │ . │ENT│ENT│FN │UCR│UCM│
 * └────┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
 */

	[1] = LAYOUT_ortho_5x15(
    KC_MUTE, QMKBEST, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_MSEL, KC_NO,   KC_MYCM, KC_MAIL, RGB_HUD, RGB_HUI, KC_CALC, KC_P7, KC_P8, KC_P9, KC_MINS, KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS,
    KC_MPRV, KC_NO,   KC_MNXT, KC_MSTP, RGB_SAD, RGB_SAI, KC_MPLY, KC_P4, KC_P5, KC_P6, KC_PLUS, RESET, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_VOLD, KC_MUTE, KC_VOLU, KC_APP,  RGB_VAD, RGB_VAI, KC_NO, KC_P1, KC_P2, KC_P3, KC_PENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, MO(1),   RGB_TOG, KC_NO,   RGB_RMOD,RGB_MOD, KC_NO, KC_P0, KC_NO, KC_PDOT, KC_PENT, KC_PENT, MO(1), UC_RMOD, UC_MOD)
};

