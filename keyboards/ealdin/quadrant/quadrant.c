/* Copyright 2020 Ealdin Keyboards
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
#include "quadrant.h"


// Rotary encoder functions:
__attribute__((weak)) void encoder_update_user(uint8_t index, bool clockwise) {
  uint16_t mapped_code = 0;
  if (index == 0) {
    if (clockwise) {
        switch(get_highest_layer(layer_state)){
            case 0:
            default:
                mapped_code = KC_VOLD;
                break;
            case 1:
                mapped_code = KC_MEDIA_PREV_TRACK;
                break;
            case 2:
                mapped_code = KC_PGUP;
                break;
        }
    } else {
        switch(get_highest_layer(layer_state)){
            case 0:
            default:
                mapped_code = KC_VOLU;
                break;
            case 1:
                mapped_code = KC_MEDIA_NEXT_TRACK;
                break;
            case 2:
                mapped_code = KC_PGDN;
                break;
        }
    }
    tap_code(mapped_code);
  }
}

void keyboard_pre_init_kb(void) {
    setPinOutput(F0);

    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        writePin(F0, led_state.caps_lock);
    }
    return true;
}

