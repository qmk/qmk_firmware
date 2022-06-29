/* Copyright 2020 MechMerlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "dz60.h"

enum{
	M_JQUERY = SAFE_RANGE,
	M_DIV,
	M_DIVEND,
	M_PHPTAG,
	M_VDUMP,
	M_JSLOG,
	M_EMAIL_W,
	M_PW_W,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_b_iso(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
        KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, KC_ENT,
        KC_LSFT, KC_GRV, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,        KC_UP,   MO(2),
        KC_LCTL,   KC_LGUI,   KC_LALT,              KC_SPC, MO(1), KC_SPC,                       KC_SLSH, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_60_b_iso(
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
        _______,     RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,
        _______,     M_JQUERY, M_DIV, M_DIVEND, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLASH, _______,
        _______, BL_TOGG,  _______, _______, M_JSLOG, M_VDUMP, _______, _______, _______, LCTL(KC_Z), LCTL(KC_Y), _______,        KC_VOLU, TO(0),
        _______,   _______,   _______,              KC_UNDS, _______, C(KC_BSPC),                       _______, _______, _______, KC_VOLD, TO(3)
    ),
	[2] = LAYOUT_60_b_iso(
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LALT(KC_F4),
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RSFT(KC_BSLASH), _______,
        _______, _______,  M_EMAIL_W, M_PW_W, _______, _______, _______, _______, _______, A(KC_LEFT), A(KC_RIGHT), C(KC_T),        KC_PGUP, _______,
        _______,   _______,   _______,              _______, _______, _______,                       _______, C(A(KC_DEL)), C(S(KC_T)), KC_PGDOWN, C(KC_W)
    ),
	[3] = LAYOUT_60_b_iso(
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______, MO(5),
        _______,   KC_LALT,   KC_LGUI,              _______, MO(4), _______,                       _______, MO(4), _______, _______, _______
    ),
    [4] = LAYOUT_60_b_iso(
        _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
        _______,     RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______,
        _______,     M_JQUERY, M_DIV, M_DIVEND, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLASH, _______,
        _______, BL_TOGG,  _______, _______, M_JSLOG, M_VDUMP, _______, _______, _______, LWIN(KC_Z), LSFT(LWIN(KC_Z)), _______,        _______, _______,
        _______,   _______,   _______,              KC_UNDS, _______, A(KC_DEL),                       _______, _______, _______, _______, TO(0)
    ),
    [5] = LAYOUT_60_b_iso(
        _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LGUI(KC_Q),
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RSFT(KC_BSLASH), _______,
        _______, _______,  M_EMAIL_W, M_PW_W, _______, _______, _______, _______, _______, A(KC_LEFT), A(KC_RIGHT), LGUI(KC_T),        KC_PGUP, _______,
        _______,   _______,   _______,              _______, _______, _______,                       _______, LGUI(A(KC_ESC)), LGUI(S(KC_T)), KC_PGDOWN, LGUI(KC_W)
    ),
};

static uint16_t key_timer;
bool BL_flashing = true;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (BL_flashing && record->event.pressed) {
        backlight_level_noeeprom(255);
        key_timer = timer_read();
    }

    switch (keycode) {
        case BL_TOGG:
            if (record->event.pressed)
                BL_flashing = !BL_flashing;
            return false;
    }

    if (record->event.pressed) {
		switch(keycode){
			case M_JQUERY:
				SEND_STRING("$('')");
				return false; break;
			case M_DIV:
				SEND_STRING("<div>");
				return false; break;
			case M_DIVEND:
				SEND_STRING("</div>");
				return false; break;
			case M_PHPTAG:
				SEND_STRING("<?php ?>");
				return false; break;
			case M_VDUMP:
				SEND_STRING("var_dump();");
				return false; break;
			case M_JSLOG:
				SEND_STRING("console.log();");
				return false; break;
			case M_EMAIL_W:
				SEND_STRING("");	//DO NOT COMMIT THESE LINES !!!
				return false; break;
			case M_PW_W:
				SEND_STRING("");	//DO NOT COMMIT THESE LINES !!!
				return false; break;
		}
	}
    return true;
}

void matrix_scan_user(void) {
    if (timer_elapsed(key_timer) > 17 && get_backlight_level()) //Delay  [10-30]
	backlight_level_noeeprom(0);
}
