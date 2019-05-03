/*
Copyright 2016 Daniel Svensson <dsvensson@gmail.com>

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

/* Swedish keys */
#define SE_HALF KC_GRV
#define SE_PLUS KC_MINS
#define SE_ACUT KC_EQL
#define SE_AO   KC_LBRC
#define SE_CIRC KC_RBRC
#define SE_QUOT KC_BSLS
#define SE_OE   KC_SCLN
#define SE_AE   KC_QUOT
#define SE_MINS KC_SLSH
#define SE_LTGT KC_NUBS
#define SE_LCBR RALT(KC_7)
#define SE_LBRC RALT(KC_8)
#define SE_RBRC RALT(KC_9)
#define SE_RCBR RALT(KC_0)
#define SE_PIPE RALT(SE_LTGT)
#define SE_BSLS RALT(SE_PLUS)

#define KM_BLOWRAK 0
#define KM_QWERTY  1
#define KM_MEDIA   2
#define KM_HAXHAX  3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Layer 0: Blowrak ISO layer, a Swedish take on Dvorak */
	[KM_BLOWRAK] = LAYOUT( \
		KC_ESC,          KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,    KC_PSCR,KC_SLCK,KC_PAUS, \
		SE_HALF, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   SE_PLUS,SE_ACUT,KC_BSPC,   KC_INS, KC_HOME,KC_PGUP, \
		KC_TAB,  SE_AO,  SE_AE,  SE_OE,  KC_P,   KC_Y,   KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_COMM,SE_CIRC,SE_QUOT,   KC_DEL, KC_END, KC_PGDN, \
		KC_LCTRL,KC_A,   KC_O,   KC_E,   KC_U,   KC_I,   KC_H,   KC_D,   KC_T,   KC_N,   KC_S,   SE_MINS,        KC_ENT,                             \
		KC_LSFT, SE_LTGT,KC_DOT, KC_Q,   KC_J,   KC_K,   KC_B,   KC_X,   KC_M,   KC_W,   KC_V,   KC_Z,           KC_RSFT,           KC_UP,           \
		KC_FN0,  KC_LGUI,KC_LALT,                       KC_SPC,                          KC_RALT,KC_RGUI,KC_MENU,KC_FN1,    KC_LEFT,KC_DOWN,KC_RGHT),
	/* Layer 1: Standard ISO layer */
	[KM_QWERTY] = LAYOUT( \
		KC_ESC,          KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,    KC_PSCR,KC_SLCK,KC_PAUS, \
		SE_HALF, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   SE_PLUS,SE_ACUT,KC_BSPC,   KC_INS, KC_HOME,KC_PGUP, \
		KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   SE_AO,  SE_CIRC,SE_QUOT,   KC_DEL, KC_END, KC_PGDN, \
		KC_LCTRL,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   SE_OE,  SE_AE,          KC_ENT,                             \
		KC_LSFT, SE_LTGT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, SE_MINS,        KC_RSFT,           KC_UP,           \
		KC_FN0,  KC_LGUI,KC_LALT,                       KC_SPC,                          KC_RALT,KC_RGUI,KC_MENU,KC_FN1,    KC_LEFT,KC_DOWN,KC_RGHT),
	/* Layer 2: Media layer */
	[KM_MEDIA] = LAYOUT( \
		_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   KC_WAKE,KC_PWR, KC_SLEP, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,KC_VOLU, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   KC_MUTE,_______,KC_VOLD, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,                            \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           KC_MPLY,         \
		_______,_______,_______,                        _______,                        _______,_______,RESET  ,_______,   KC_MPRV,KC_MSTP,KC_MNXT),
	/* Layer 3: Programming layer */
	[KM_HAXHAX] = LAYOUT( \
		_______,        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______, \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______, \
		_______,SE_LCBR,SE_PIPE,SE_RCBR,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,   _______,_______,_______, \
		_______,SE_LBRC,SE_BSLS,SE_RBRC,_______,_______,_______,_______,_______,_______,_______,_______,        _______,                            \
		_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,        _______,           _______,         \
		_______,_______,_______,                        _______,                        _______,_______,_______,_______,   _______,_______,_______),
};

const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_MOMENTARY(KM_MEDIA),
	[1] = ACTION_LAYER_TOGGLE(KM_QWERTY)
};

void matrix_scan_user(void)
{
	uint8_t layer = biton32(layer_state);
	switch (layer) {
		case KM_BLOWRAK:
			ph_caps_led_on();
			ph_sclk_led_off();
			break;
		case KM_QWERTY:
			ph_sclk_led_on();
			ph_caps_led_off();
			break;
	}
}

/* Mixes in KM_HAXHAX via RALT modifier without shadowing the RALT key combinations. */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	uint8_t modifiers = get_mods();
	if (modifiers & MOD_BIT(KC_RALT) && record->event.pressed) {
		uint16_t kc = keymap_key_to_keycode(KM_HAXHAX, record->event.key);
		if (kc != KC_TRNS) {
			register_code(kc);
			unregister_code(kc);
			return false;
		}
	}
	return true;
}
