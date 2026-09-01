/* Copyright 2025 Shulin Huang <mumu@x-bows.com>
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
 const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {

  {0, C3_3,  C2_3, C1_3},   // L01
  {0, C3_4,  C2_4, C1_4},   // L02
  {0, C9_5,  C8_5, C7_5},   // L03
  {0, C9_6,  C8_6, C7_6},   // L04

  {0, C6_1,  C5_1, C4_1},   // L05
  {0, C6_2,  C5_2, C4_2},   // L06
  {0, C6_3,  C5_3, C4_3},   // L07
  {0, C6_6,  C5_6, C4_6},   // L08

  {0, C9_1,  C8_1, C7_1},   // L09
  {0, C9_2,  C8_2, C7_2},   // L10
  {0, C9_3,  C8_3, C7_3},   // L11
  {0, C3_14,  C2_14, C1_14},   // L12

  {0, C3_11,  C2_11, C1_11},   // L13
  {0, C3_12,  C2_12, C1_12},   // L14
  {0, C3_13,  C2_13, C1_13},   // L15


  {0, C6_9,  C5_9, C4_9},      // L16
  {0, C6_10,  C5_10, C4_10},   // L17
  {0, C6_11,  C5_11, C4_11},   // L17
  {0, C6_14,  C5_14, C4_14},   // L19

  {0, C6_16,  C5_16, C4_16},   // L20
  {0, C6_15,  C5_15, C4_15},   // L21

 };
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(4, 0xFF, 0xFF, 0xFF);
    }
    return true;
}

#endif
