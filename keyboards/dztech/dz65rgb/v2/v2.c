/* Copyright 2020 DZTECH <moyi4681@live.cn>
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
    { 0, C8_8,  C7_8,  C6_8 },
    { 0, C9_8,  C7_7,  C6_7 },
    { 0, C9_7,  C8_7,  C6_6 },
    { 0, C9_6,  C8_6,  C7_6 },
    { 0, C9_5,  C8_5,  C7_5 },
    { 0, C9_4,  C8_4,  C7_4 },
    { 0, C9_3,  C8_3,  C7_3 },
    { 0, C9_2,  C8_2,  C7_2 },
    { 0, C9_1,  C8_1,  C7_1 },
    { 0, C2_9,  C3_9,  C4_9 },
    { 0, C1_9,  C3_10, C4_10 },
    { 0, C1_10, C2_10, C4_11 },
    { 0, C1_11, C2_11, C3_11 },
    { 0, C1_13, C2_13, C3_13 },
    { 0, C1_14, C2_14, C3_14 },

    { 0, C1_7,  C2_7,  C3_7 },
    { 0, C1_6,  C2_6,  C3_6 },
    { 0, C1_5,  C2_5,  C3_5 },
    { 0, C1_4,  C2_4,  C3_4 },
    { 0, C1_3,  C2_3,  C3_3 },
    { 0, C1_2,  C2_2,  C4_3 },
    { 0, C1_1,  C3_2,  C4_2 },
    { 0, C2_1,  C3_1,  C4_1 },
    { 0, C9_9,  C8_9,  C7_9 },
    { 0, C9_10, C8_10, C7_10 },
    { 0, C9_11, C8_11, C7_11 },
    { 0, C9_12, C8_12, C7_12 },
    { 0, C9_13, C8_13, C7_13 },
    { 0, C9_14, C8_14, C7_14 },
    { 0, C1_15, C2_15, C3_15 },

    { 0, C1_8,  C2_8,  C3_8 },
    { 1, C9_6,  C8_6,  C7_6 },
    { 1, C9_5,  C8_5,  C7_5 },
    { 1, C9_4,  C8_4,  C7_4 },
    { 1, C9_3,  C8_3,  C7_3 },
    { 1, C9_2,  C8_2,  C7_2 },
    { 1, C9_1,  C8_1,  C7_1 },
    { 1, C2_9,  C3_9,  C4_9 },
    { 1, C1_9,  C3_10, C4_10 },
    { 1, C1_10, C2_10, C4_11 },
    { 1, C1_11, C2_11, C3_11 },
    { 1, C1_12, C2_12, C3_12 },
    { 1, C1_13, C2_13, C3_13 },
    { 0, C1_16, C2_16, C3_16 },

    { 1, C9_8,  C7_7,  C6_7 },
    { 1, C1_5,  C2_5,  C3_5 },
    { 1, C1_4,  C2_4,  C3_4 },
    { 1, C1_3,  C2_3,  C3_3 },
    { 1, C1_2,  C2_2,  C4_3 },
    { 1, C1_1,  C3_2,  C4_2 },
    { 1, C9_9,  C8_9,  C7_9 },
    { 1, C9_10, C8_10, C7_10 },
    { 1, C9_11, C8_11, C7_11 },
    { 1, C9_12, C8_12, C7_12 },
    { 1, C1_14, C2_14, C3_14 },
    { 1, C1_15, C2_15, C3_15 },
    { 1, C1_16, C2_16, C3_16 },
    { 0, C9_15, C8_15, C6_14 },

    { 1, C8_8,  C7_8,  C6_8 },
    { 1, C1_8,  C2_8,  C3_8 },
    { 1, C1_7,  C2_7,  C3_7 },
    { 1, C2_1,  C3_1,  C4_1 },
    { 1, C9_14, C8_14, C7_14 },
    { 1, C9_15, C8_15, C6_14 },
    { 1, C9_16, C7_15, C6_15 },
    { 1, C8_16, C7_16, C6_16 },
    { 0, C8_16, C7_16, C6_16 },
    { 0, C9_16, C7_15, C6_15 }
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
