/* Copyright 2021 Brandon Lewis
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

#include "ristretto.h"

enum layers {
	_BASE,
	_RAISE,
	_LOWER,
	_ADJUST
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
	if(index == 0) {
		if (clockwise) {
			tap_code(KC_VOLD);
		} else {
			tap_code(KC_VOLU);
			}
		}
	return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
	oled_write_P(PSTR("\n\n"), false);
	oled_write_ln_P(PSTR("LAYER"), false);
	oled_write_ln_P(PSTR(""), false);
	switch (get_highest_layer(layer_state)) {
		case _BASE:
			oled_write_P(PSTR("BASE\n"), false);
			break;
		case _RAISE:
			oled_write_P(PSTR("RAISE\n"), false);
			break;
		case _LOWER:
			oled_write_P(PSTR("LOWER\n"), false);
			break;
		case _ADJUST:
			oled_write_P(PSTR("ADJ\n"), false);
			break;
	}
    return false;
}

#endif
