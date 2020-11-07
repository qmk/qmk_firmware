/* Copyright 2020 Regan Palmer
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
#include "rainkeeb.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	KEYMAP(
		KC_Q, KC_E, KC_T, KC_U, KC_O, 
		KC_W, KC_R, KC_Y, KC_I, KC_P, 
		KC_A, KC_D, KC_G, KC_H, KC_K, KC_ENT, 
		KC_S, KC_F, KC_MPLY, KC_J, KC_L, 
		KC_Z, KC_C, KC_B, KC_N, KC_COMM, KC_BSPC, 
		KC_X, KC_V, KC_PSCR, KC_M, KC_DOT, 
		KC_LCTL, KC_LGUI, MO(1), KC_RGUI, KC_RCTL, 
		KC_LALT, KC_LSFT, KC_SPC, KC_RALT),

	KEYMAP(
		KC_1, KC_3, KC_5, KC_7, KC_9, 
		KC_2, KC_4, KC_6, KC_8, KC_0, 
		KC_ESC, KC_BSLS, KC_MINS, KC_LBRC, KC_SCLN, KC_TRNS, 
		KC_GRV, KC_UP, KC_TRNS, KC_RBRC, KC_QUOT, 
		KC_TAB, KC_LEFT, KC_RGHT, KC_EQL, KC_TRNS, KC_TRNS, 
		KC_CAPS, KC_DOWN, MO(2), KC_SLSH, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	KEYMAP(
		KC_F1, KC_F3, KC_F5, KC_F7, KC_F9, 
		KC_F2, KC_F4, KC_F6, KC_F8, KC_F10, 
		KC_F11, KC_F13, KC_F15, KC_HOME, KC_PGUP, KC_TRNS, 
		KC_F12, KC_F14, RESET, KC_PGDN, KC_END, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
	switch (get_highest_layer(layer_state)) {
        case 0:
             if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
            break;
        case 1:
            if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
            break;
		case 2:
			if (clockwise) {
            tap_code(KC_MS_WH_RIGHT);
        } else {
            tap_code(KC_MS_WH_LEFT);
        }
			break;
    }
}

char wpm[10];

void oled_task_user(void) {
	sprintf(wpm, "WPM: %03d", get_current_wpm());

    // Host Keyboard Layer Status
	oled_write_P(PSTR("       rainkeeb \n"), false);
    oled_write_P(PSTR(" Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Raise\n"), false);
            break;
		case 2:
			oled_write_P(PSTR("Higher\n"), false);
			break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
	oled_write_P(PSTR(" "), false);
	oled_write(wpm, false);
}