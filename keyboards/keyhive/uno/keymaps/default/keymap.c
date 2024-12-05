/* Copyright 2020 Snipeye
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

enum uno_keycode
{
  UNO = SAFE_RANGE
};

enum encoder_names {
	_ENCODER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
            UNO
          )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case UNO:
			if (record->event.pressed) {
				SEND_STRING("Hello!");
			}
			break;
			return false;
    }
    return true;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(255, 255, 255);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _ENCODER) { /* First encoder */
        if (clockwise) {
            tap_code(KC_A);
        } else {
            tap_code(KC_B);
        }
		return false;
    }
	return true;
}

