/* Copyright 2021 Kyle McCreery
 * Copyright 2021 Jonavin Eng
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
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "keymap.h"


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
	_FN2,
	_FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_LANDSCAPE(
        TT(1), TT(2), KC_MUTE,

        KC_NLCK,  KC_PSLS,  KC_PAST, KC_PMNS, KC_PPLS,      KC_LGUI,
        KC_BSPC,  KC_P7,    KC_P8,   KC_P9,   KC_PDOT,      KC_RSFT,
        KC_TAB,   KC_P4,    KC_P5,   KC_P6,   KC_COMMA,     KC_RCTL,
        KC_P0,    KC_P7,    KC_P8,   KC_P9,   KC_PENT,      KC_RALT,

                 _______, _______, _______

    ),
    [_FN1] = LAYOUT_LANDSCAPE(
        _______,  _______, _______,

        _______,  KC_F10,   KC_F11,  KC_F12,  KC_PSCR,      _______,
        _______,  KC_F7,    KC_F8,   KC_F9,   KC_SLCK,      _______,
        _______,  KC_F4,    KC_F5,   KC_F6,   KC_PAUS,      _______,
        _______,  KC_F1,    KC_F2,   KC_F3,   _______,      _______,

                 _______, _______, _______

    ),
	[_FN2] = LAYOUT_LANDSCAPE(
        _______,  _______, _______,

        _______,  RGB_HUD,  RGB_SPI, RGB_HUI, KC_NO,        _______,
        _______,  RGB_RMOD, RGB_TOG, RGB_MOD, KC_NO,        _______,
        _______,  RGB_VAD,  RGB_SPD, RGB_VAI, KC_NO,        _______,
        _______,  RGB_SAD,  KC_NO,   RGB_SAI, _______,      _______,

                  _______,  _______, _______

    ),
	[_FN3] = LAYOUT_LANDSCAPE(
        _______,  _______, _______,

        _______,  _______,  _______,  _______, _______,     _______,
        _______,  _______,  _______,  _______, _______,     _______,
        _______,  _______,  _______,  _______, _______,     _______,
        _______,  _______,  _______,  _______, _______,     _______,

                  _______,  _______, _______
   )
};


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case 1:
            if (clockwise) {
                   tap_code(KC_BRIU);
            } else {
                tap_code(KC_BRID);
                break;
            }
    }
    return true;
};
#endif

#ifdef OLED_DRIVER_ENABLE
	oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		return OLED_ROTATION_180;       // flips the display 180 degrees for horizontal/landscape
	}

    static void render_logo(void) {     // Render MechWild "MW" Logo  -- landscape version from Mercutio
        static const char PROGMEM logo_1[] = {0x97, 0x98, 0x99, 0x9A,0x00};
        static const char PROGMEM logo_2[] = {0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x00};
        static const char PROGMEM logo_3[] = {0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xB6, 0x00};
        static const char PROGMEM logo_4[] = {0xB6, 0xB6, 0xB6, 0x9B, 0x9C, 0x9D, 0x9E, 0x00};
        oled_set_cursor(0,0);
        oled_write_P(logo_1, false);
        oled_set_cursor(0,1);
        oled_write_P(logo_2, false);
        oled_set_cursor(0,2);
        oled_write_P(logo_3, false);
        oled_set_cursor(0,3);
        oled_write_P(logo_4, false);
    }

	void oled_task_user(void) {
		render_logo();
		oled_set_cursor(8,2);

		oled_write_ln_P(PSTR("Layer"), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            break;
        case _FN1:
            oled_write_ln_P(PSTR("FN 1"), false);
            break;
        case _FN2:
            oled_write_ln_P(PSTR("FN 2"), false);
            break;
        case _FN3:
            oled_write_ln_P(PSTR("FN 3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
	oled_write_ln_P(PSTR(""), false);
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
 /*    oled_write_ln_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false); */
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR") : PSTR("   "), false);
}
#endif
