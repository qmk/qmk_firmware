/* Copyright 2021 swiftrax
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
    SAY_OWO = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SAY_OWO:
        if (record->event.pressed) {
            // when keycode SAY_OWO is pressed
            SEND_STRING("OWO");
        } else {
            // when keycode SAY_OWO is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,
		SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,   SAY_OWO,              SAY_OWO,   SAY_OWO,   SAY_OWO),

	[1] = LAYOUT(
    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,              KC_TRNS,   KC_TRNS,   KC_TRNS)
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
  oled_write_P(PSTR("OWO\nWhat's\nthis?"), false);
    return false;
}
#endif
