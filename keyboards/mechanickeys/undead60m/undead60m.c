/* Copyright 2021 jfescobar18
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
	  
#include "quantum.h"
bool encoder_update_kb(uint8_t index, bool clockwise) {
  if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
      switch (get_highest_layer(layer_state)) {
        case 0: /* Layer 1: Volume */
          if (clockwise) {
              tap_code(KC_VOLD);
          } else {
              tap_code(KC_VOLU);
          }
          break;
        case 1: /* Layer 2: Scroll */
          if (clockwise) {
              tap_code(KC_WH_U);
          } else {
              tap_code(KC_WH_D);
          }
          break;
        case 2: /* Layer 3: Change Track */
          if (clockwise) {
              tap_code(KC_MPRV);
          } else {
              tap_code(KC_MNXT);
          }
          break;
        case 3: /* Layer 4: Brightness */
          if (clockwise) {
              tap_code(KC_BRID);
          } else {
              tap_code(KC_BRIU);
          }
          break;
        default: /* Default: Volume */
          if (clockwise) {
              tap_code(KC_VOLU);
          } else {
              tap_code(KC_VOLD);
          }
          break;
      }
  }
  return true;
}
