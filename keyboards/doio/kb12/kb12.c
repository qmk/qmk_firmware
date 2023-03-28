/* Copyright 2022 DOIO
 * Copyright 2022 DOIO2022 <https://github.com/DOIO2022>
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


#ifdef RGB_MATRIX_ENABLE

 led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 0,    1,   2,   3, NO_LED },
  { 4,    5,   6,    7, NO_LED},
  { 8,     9,    10,    11, NO_LED}
}, {
{0,0}, {75,0}, {150,0}, {224,0},{0,32},{75,32},{150,32},{224,32},{0,64},{75,64},{150,64},{224,64}, 
}, { 
    4,4,4,4,4,4,4,4,4,4,4,4
} };
#endif

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
      return false;
    }
    if (clockwise) {
        tap_code_delay(KC_PGUP, 10);
    } else {
        tap_code_delay(KC_PGDN, 10);
    }
    return true;
}
