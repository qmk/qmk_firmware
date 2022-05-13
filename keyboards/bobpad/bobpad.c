/* Copyright 2021 Ananya Kirti
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

#include "bobpad.h"

bool led_update_kb(led_t led_state) {
    if (!led_update_user(led_state)) { return false; }
    
    writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
    return true;
};

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    
    if(IS_LAYER_ON(1)) { // on Raise layer
      if (clockwise) {
          tap_code(KC_A);
      } else {
          tap_code(KC_B);
      }
    }
    // default layer
    else {
      if (clockwise) {
          tap_code(KC_C);
      } else {
          tap_code(KC_D);
      }
    }
    return true;
}