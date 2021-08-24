/* Copyright 2019 AbstractKB
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

// Defines the keycodes used by our macros in process_record_user
/*enum custom_keycodes {
  MYKEY = SAFE_RANGE
};*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_A,	RGB_TOG,	KC_C,
    KC_X,	KC_Y,		KC_Z
  )
};

/*bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}*/

/*void matrix_init_user(void) {

}*/

/*void matrix_scan_user(void) {

}*/

/*void led_set_user(uint8_t usb_led) {

}*/

bool encoder_update_user(uint8_t index, bool clockwise) {
	if (index == 0) { /* First encoder */
		if (clockwise) {
			tap_code(KC_O);
		} else {
			tap_code(KC_P);
		}
	} else if (index == 1) { /* Second encoder */
		if (clockwise) {
			rgblight_increase_hue_noeeprom();
		} else {
			rgblight_decrease_hue_noeeprom();
		}
	} else if (index == 2) {
		if (clockwise) {
			tap_code(KC_M);
		} else {
			tap_code(KC_R);
		}
	}
    return true;
}
