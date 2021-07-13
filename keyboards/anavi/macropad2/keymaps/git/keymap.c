/* Copyright 2021 Leon Anavi <leon@anavi.org>
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

enum custom_keycodes {
	GITCOMMIT = SAFE_RANGE,
	GITPUSH
};

void keyboard_post_init_user(void) {
	// Set backlight to the maximum brightness
	backlight_level(2);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case GITCOMMIT:
		if (record->event.pressed) {
			SEND_STRING("git commit -s\n");
		}
	break;
	case GITPUSH:
		if (record->event.pressed) {
			SEND_STRING("git push\n");
		}
	}
	return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    GITCOMMIT, GITPUSH
  )
};
