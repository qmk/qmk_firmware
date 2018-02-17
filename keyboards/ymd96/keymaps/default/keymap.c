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


/*
	K500, K502, K503, K504, K505, K600, K610, K710, K700, K511, K512, K513, K514, K113, K214, K013, K706, K709, K708, \
	K400, K401, K402, K403, K404, K405, K601, K611, K711, K701, K410, K411, K412, K414, 	  K406, K407, K408, K409, \
    K300, K301, K302, K303, K304, K305, K602, K612, K712, K702, K310, K311, K312, K313,       K306, K307, K308, K309, \
	K200, K201, K202, K203, K204, K205, K603, K613, K713, K703, K210, K211, 			K213, K206, K207, K208, K209, \
	K100, K101, K102, K103, K104, K105, K604, K614, K714, K704, K110,             K111, K810, K106, K107, K108, K009, \
	K000, K001, K002,                   K605,                         K705, K011, K606, K607, K609, K006, K008  \
*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	/* Layer 0, default layer
	*  | Esc  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |Print | Home | End  |Insert|Delete| PgUp | 19 keys
	*  |  ~`  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |    0 |    - |    = |    BkSpc    |NumLck|   /  |   *  | PgDn | 18 keys
	*  |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |    P |    { |    } |     \    |  7   |   8  |   9  |   -  | 18 keys
	*  |   Caps   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |    ; |   '  |     Return     |  4   |   5  |   6  |   +  | 17 keys
	*  |    LShft     |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |       RShft       |  1   |   2  |   3  |  En  | 16 keys
	*  | Ctrl  |  Win  |  Alt  |                  Space                      |  Fn  |  Win | Left | Down |  Up  | Right|   0  |   .  |  ter | 12 keys
	*/
	
    KEYMAP(
			KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,       KC_F12,      	KC_PSCR, KC_PAUS, KC_HOME,    KC_END,      KC_PGUP,   	   KC_PGDN, \
			KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,      KC_EQL,          KC_BSPC,          KC_DEL,     KC_KP_SLASH, KC_KP_ASTERISK, KC_PMNS, \
			KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,      KC_RBRC,         KC_BSLS,          KC_P7,      KC_P8,       KC_P9,          F(0),    \
			KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,                       KC_ENT,           KC_P4,      KC_P5,       KC_P6,          KC_PPLS, \
			KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,                               KC_RSFT, KC_UP,   KC_P1,      KC_P2,       KC_P3,          KC_PENT, \
			KC_LCTL, KC_LGUI,KC_LALT,                              KC_SPC,                        KC_RALT,      KC_RCTL,       KC_LEFT,     KC_DOWN,      KC_RGHT,     KC_P0,          KC_PDOT  \
	),

    KEYMAP(
			KC_ESC,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,       KC_F12,      	KC_PSCR, KC_PAUS, KC_HOME,    KC_END,      KC_PGUP,   	   KC_PGDN, \
			KC_GRV,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,      KC_EQL,          KC_BSPC,          KC_INS,     KC_KP_SLASH, KC_KP_ASTERISK, KC_PMNS, \
			KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,      KC_RBRC,         KC_BSLS,          RGB_TOG,      RGB_MOD,       RGB_HUI,          F(0),    \
			KC_CAPS, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,                       KC_ENT,           RGB_VAI,      RGB_VAD,       RGB_HUD,          KC_PPLS, \
			KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,                               KC_RSFT, KC_VOLU,   KC_P1,      KC_P2,       KC_P3,          KC_PENT, \
			KC_LCTL, KC_LGUI,KC_LALT,                              KC_SPC,                        KC_LALT,      KC_RCTL,       KC_LEFT,     KC_VOLD,      KC_RGHT,     BL_STEP,          KC_PDOT  \
	),
};

// Custom Actions
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
};
