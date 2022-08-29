/*
Copyright 2022 DmNosachev

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QW,
    _RS,
    _LW
};

#define MC1 COMP_FR_QUOTES
#define MC2 COMP_NBSP_EM_DASH
#define MC3 COMP_NBSP

enum custom_keycodes {
    COMP_FR_QUOTES = SAFE_RANGE, // Compose: french quotes
    COMP_NBSP_EM_DASH,	         // Compose: nbsp followed by em dash
    COMP_NBSP,		    	     // Compose: nbsp
    PWD1,
    PWD2,
    PWD3,				      	 // KP password
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
	,----------------------------------.              ,----------------------------------.
	|Q/Alt |   W  |   E  |   R  |   T  |              |   Y  |   U  |   I  |   O  |   P  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|A/Ctrl|   S  |   D  |   F  |   G  |              |   H  |   J  |   K  |   L  |;/Ctrl|
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	|Z/Shft|   X  |   C  |   V  |   B  |Bkspc ||Delete|   N  |   M  |   ,  |   .  |?/Shft|
	|------+------+------+------+------|      ||      |------+------+------+------+------|
	|   ~  |  Tab |   -  |  GUI |Spc/LW|------'`------|Ent/RS|  |\  |   [  |   ]  |  "'  |
	`----------------------------------'              `----------------------------------'
*/
    [_QW] = LAYOUT( /* QWERTY */
    LALT_T(KC_Q),   KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,            KC_U,    KC_I,    KC_O,    KC_P,
    LCTL_T(KC_A),   KC_S,    KC_D,    KC_F,    KC_G,                             KC_H,            KC_J,    KC_K,    KC_L,    RCTL_T(KC_SCLN),
    LSFT_T(KC_Z),   KC_X,    KC_C,    KC_V,    KC_B,                             KC_N,            KC_M,    KC_COMM, KC_DOT,  RSFT_T(KC_SLSH),
    KC_GRV,         KC_TAB,  KC_MINS, KC_LGUI, LT(_LW, KC_SPC), KC_BSPC, KC_DEL, LT(_RS, KC_ENT), KC_BSLS, KC_LBRC, KC_RBRC, KC_QUOT
    ),
  
/*
	,----------------------------------.              ,----------------------------------.
	| PrnSc| pwd1 |  up  | pwd2 | PgUp |              | Home |  F7  |  F8  |  F9  |      |
	|------+------+------+------+------|              |------+------+------+------+------|
	| trns | left | down | right| PgDn |              |  End |  F4  |  F5  |  F6  | trns |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	| trns | MC2  |  MC3 |   (  |   )  |      ||      | AltGr|  F1  |  F2  |  F3  | trns |
	|------+------+------+------+------|      ||      |------+------+------+------+------|
	| trns | C+S  |  Ins |  MC1 | trns |------'`------| trns |  F10 |  F11 |  F12 | trns |
	`----------------------------------'              `----------------------------------'
*/

    [_RS] = LAYOUT( /* RAISE  */
    KC_PSCR, PWD1,           KC_UP,   PWD2,    KC_PGUP,                   KC_HOME, KC_F7,   KC_F8,  KC_F9,  _______,
    _______, KC_LEFT,        KC_DOWN, KC_RGHT, KC_PGDN,                   KC_END,  KC_F4,   KC_F5,  KC_F6,  _______,
    _______, MC2,            MC3,     KC_LPRN, KC_RPRN,                   KC_RALT, KC_F1,   KC_F2,  KC_F3,  _______,
    _______, LCTL(KC_LSFT),  _______, MC1,     _______, _______, _______, _______, KC_F10,  KC_F11, KC_F12, _______
    ),

/*
	,----------------------------------.              ,----------------------------------.
	|   !  |   @  |   #  |   $  |  %   |              |   /  |   7  |   8  |   9  |  .   |
	|------+------+------+------+------|              |------+------+------+------+------|
	| trns |   ^  |   &  |   *  | PWD3 |              |   *  |   4  |   5  |   6  | trns |
	|------+------+------+------+------|------.,------|------+------+------+------+------|
	| trns |r_tog | r_hue| r_sat| r_val|      ||      |   +  |   1  |   2  |   3  | trns |
	|------+------+------+------+------|      ||      |------+------+------+------+------|
	| trns | Esc  |RESET |capslk| trns |------'`------| trns |   0  |   -  |  +=  | trns |
	`----------------------------------'              `----------------------------------'
*/

    [_LW] = LAYOUT( /* LOWER */
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_PSLS, KC_7, KC_8,    KC_9,   KC_PDOT,
    _______, KC_CIRC, KC_AMPR, KC_ASTR, PWD3,                      KC_PAST, KC_4, KC_5,    KC_6,   _______,
    _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,                   KC_PPLS, KC_1, KC_2,    KC_3,   _______,
    _______, KC_ESC , RESET,   KC_CAPS, _______, _______, _______, _______, KC_0, KC_PMNS, KC_EQL, _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case MC1: /* French quotes */
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_RALT) SS_DELAY(100) "<<" SS_DELAY(100) SS_TAP(X_RALT) SS_DELAY(100) ">>" SS_TAP(X_LEFT));
        }
        break;
	  
	case MC2: /* NB-space + mdash + space */
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_RALT) SS_DELAY(100) "  " SS_DELAY(100) SS_TAP(X_RALT) SS_DELAY(100) "--- ");
        }
        break;
	  
	case MC3: /* NB-space */
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_RALT) SS_DELAY(100) "  ");
        }
        break;
	  
	case PWD1:
        if (record->event.pressed) {
            SEND_STRING("NakedLunch1991\n");
        }
        break;
	  
    case PWD2:
        if (record->event.pressed) {
            SEND_STRING("O94nx4sUWHc4akud\n");
        }
        break;
	  
	case PWD3:
        if (record->event.pressed) {
            SEND_STRING("Q123qQ123q\n");
        }
        break;
    }
    return true;
};