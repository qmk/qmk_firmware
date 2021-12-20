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

#include "fruitbar.h"

enum layers {
	_BASE,
	_FN
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_kb(index, clockwise)) { return false; }
	if(index == 0) {
		if (clockwise) {
			tap_code(KC_VOLD);
		} else {
			tap_code(KC_VOLU);
			}
		}
	return true;
}


#ifdef OLED_DRIVER_ENABLE

void oled_task_user(void) {
  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case _BASE:
      oled_write_P(PSTR("Default\n"), false);
      break;
    case _FN:
      oled_write_P(PSTR("Function\n"), false);
      break;
    default:
      oled_write_P(PSTR("huh\n"), false);
  }
}
#endif