/* Copyright 2022 @fOmey
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
 
#include "ak81_ve.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 12, 11, 10, 9,      8,      7,      6,  5,      4,      NO_LED, 3,  2,  1,      0 },            // 13 keys
  { 27, 26, 25, 24,     23,     22,     21, 20,     19,     18,     17, 16, 15,     14,     13 },   // 15 keys
  { 42, 41, 40, 39,     38,     37,     36, 35,     34,     33,     32, 31, 30,     29,     28 },   // 15 keys
  { 56, 55, 54, 53,     52,     51,     50, 49,     48,     47,     46, 45, 44,     NO_LED, 43 },   // 14 keys
  { 70, 69, 68, 67,     66,     65,     64, 63,     62,     61,     60, 59, NO_LED, 58,     57 },   // 14 keys
  { 79, 78, 77, NO_LED, NO_LED, NO_LED, 76, NO_LED, NO_LED, NO_LED, 75, 74, 73,     72,     71 }    // 9 keys
}, { 
  // LED Index to Physical Positon
  { 240,  0 }, { 224,  0 }, { 208,  0 }, { 192, 0 },   { 176, 0 },  { 160, 0 },  { 144, 0 },  { 128, 0 },  { 112, 0 },  { 96, 0 },  { 80, 0 },  { 64, 0 },             { 32, 0 },
  { 240, 13 }, { 224, 13 }, { 208, 13 }, { 192 , 13 }, { 176, 13 }, { 160, 13 }, { 144, 13 }, { 128, 13 }, { 112, 13 }, { 96, 13 }, { 80, 13 }, { 64, 13}, { 48, 13 }, { 32, 13 }, { 16, 13 },
  { 240, 26 }, { 224, 26 }, { 208, 26 }, { 192 , 26 }, { 176, 26 }, { 160, 26 }, { 144, 26 }, { 128, 26 }, { 112, 26 }, { 96, 26 }, { 80, 26 }, { 64, 26}, { 48, 26 }, { 32, 26 }, { 16, 26 },
  { 240, 39 },       { 216, 39 },        { 192 , 39 }, { 176, 39 }, { 160, 39 }, { 144, 39 }, { 128, 39 }, { 112, 39 }, { 96, 39 }, { 80, 39 }, { 64, 39}, { 48, 39 }, { 32, 39 }, { 16, 39 },
  { 240, 52 }, { 224, 52 }, { 208, 52 }, { 192 , 52 }, { 176, 52 }, { 160, 52 }, { 144, 52 }, { 128, 52 }, { 112, 52 }, { 96, 52 }, { 80, 52 }, { 64, 52}, { 48, 52 },       { 24, 52 },
  { 240, 64 }, { 224, 64 }, { 208, 64 }, { 192, 64 },  { 176, 64 },                                        { 112, 64 },                                    { 48, 64 }, { 32, 64 }, { 16, 64 },
  { 0, 26 }, { 0, 46 }, { 0, 64 }, { 48, 64 }, { 72, 64 }, { 104, 64 }, { 136, 64 }, { 168, 64 }, { 208, 64 }, { 232, 58 }, { 232, 45 }, { 232, 32 }, { 232, 20 }, { 232, 7 }, { 176, 0 }, { 112, 0 }
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 8, 
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 
  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
} };
#endif

#if !defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (clockwise) {
        switch (get_highest_layer(layer_state)) {
          case 0:
            tap_code(KC_VOLU);
            break;
          case 1:
            rgb_matrix_step();
            break;
          default:
            tap_code(KC_VOLU);
            break;
        }
      }
    else {
        switch (get_highest_layer(layer_state)) {
          case 0:
            tap_code(KC_VOLD);
            break;
          case 1:
            rgb_matrix_step_reverse();
            break;
          default:
            tap_code(KC_VOLD);
            break;
        }
    }
    return true;
}
#endif