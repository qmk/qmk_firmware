/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public LicensezZZ
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ymd96.h"
#include "action_layer.h"
#include "rgblight.h"

#define _______ KC_TRNS
#define _DEFLT 0
#define _RAISE 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	/* Layer 0, default layer
	*  | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |Print | Home | End  |Insert|Delete| PgUp | 19 keys
	*  |  ~`  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |    0 |    - |    = |    BkSpc    |NumLck|   /  |   *  | PgDn | 18 keys
	*  |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |    P |    { |    } |     \    |  7   |   8  |   9  |   -  | 18 keys
	*  |   Caps   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |    ; |   '  |     Return     |  4   |   5  |   6  |   +  | 17 keys
	*  |    LShft     |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |       RShft       |  1   |   2  |   3  |  En  | 16 keys
	*  | Ctrl  |  Win  |  Alt  |                                             |  Fn  |  Win | Left | Down |  Up  | Right|   0  |   .  |  ter | 12 keys
	*/
	
    [_DEFLT] = {
		{ KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,       KC_F12,      KC_PSCR, KC_HOME,    KC_END,     KC_INSERT,   KC_DELETE,      KC_PGUP },
		{ KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,      KC_EQL,      KC_BSPC, KC_BSPC,    KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_PGDN },
		{ KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,      KC_RBRC,     KC_BSLS, KC_BSLS,    KC_P7,      KC_P8,       KC_P9,          KC_PMNS },
		{ KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,      KC_ENT,      KC_ENT,  KC_ENT,     KC_P4,      KC_P5,       KC_P6,          KC_PPLS },
		{ KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,      KC_RSFT,     KC_RSFT, KC_RSFT,    KC_P1,      KC_P2,       KC_P3,          KC_PENT },
		{ KC_LCTL, KC_LGUI,KC_LALT,KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_RCTL,      KC_RGUI,     KC_LEFT, KC_DOWN,    KC_UP,      KC_RGHT,     KC_P0,          KC_PDOT }
	}
	/*
		KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,       KC_F12,      KC_PSCR, KC_HOME,    KC_END,     KC_INSERT,   KC_DELETE,      KC_PGUP,
        KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,      KC_EQL,           KC_BSPC,        KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_PGDN,
        KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,      KC_RBRC,          KC_BSLS,        KC_P7,      KC_P8,       KC_P9,          KC_PMNS,
        KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,                  KC_ENT,               KC_P4,      KC_P5,       KC_P6,          KC_PPLS,
        KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,              KC_RSFT,                          KC_P1,      KC_P2,       KC_P3,          KC_PENT,
        KC_LCTL, KC_LGUI,KC_LALT,                       KC_SPC,                       KC_RCTL      ,   KC_RGUI,   KC_LEFT,   KC_DOWN,   KC_UP,   KC_RGHT,    KC_P0,       KC_PDOT
		
		
        KC_LCTL, KC_LGUI,KC_LALT,                       KC_SPC,                       KC_RCTL      ,   KC_RGUI,   KC_LEFT,   KC_DOWN,   KC_UP,   KC_RGHT,    KC_P0,       KC_PDOT,
        KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,              KC_RSFT,                          KC_P1,      KC_P2,       KC_P3,          KC_PENT,
        KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,                  KC_ENT,               KC_P4,      KC_P5,       KC_P6,          KC_PPLS,
        KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,      KC_RBRC,          KC_BSLS,        KC_P7,      KC_P8,       KC_P9,          KC_PMNS,
        KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,      KC_EQL,           KC_BSPC,        KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_PGDN,
		KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,       KC_F12,      KC_PSCR, KC_HOME,    KC_END,     KC_INSERT,   KC_DELETE,      KC_PGUP
		
		KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,       KC_F12,      KC_PSCR, KC_HOME,    KC_END,     KC_INSERT,   KC_DELETE,      KC_PGUP,
        KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,      KC_EQL,  KC_NO,         KC_BSPC,        KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_PGDN,
        KC_TAB,  KC_NO,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,      KC_RBRC,          KC_BSLS,        KC_P7,      KC_P8,       KC_P9,          KC_PMNS,
        KC_CAPS, KC_NO,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,                  KC_ENT,  KC_NO,               KC_P4,      KC_P5,       KC_P6,          KC_PPLS,
        KC_NO,  KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,  KC_NO,    KC_RSFT,     KC_NO,       KC_P1,      KC_P2,       KC_P3,          KC_NO,
        KC_LCTL, KC_LGUI, KC_NO, KC_LALT, KC_NO,  KC_NO,   KC_SPC, KC_NO,  KC_NO,  KC_NO,   KC_RCTL,   KC_RGUI,   KC_LEFT,   KC_DOWN,   KC_UP,   KC_RGHT,    KC_P0,       KC_PDOT,          KC_PENT

		*/
	
	/*,
	
    [_RAISE] = KEYMAP(
        KC_TRNS,RGB_TOG,RGB_MOD,RGB_HUI,RGB_SAI,RGB_VAI,RGB_HUD,RGB_SAD,RGB_VAD,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_END,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,        KC_DEL,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,        KC_INS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,                                KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_RGHT
    ), */
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_LAYER_MOMENTARY(1),
};
