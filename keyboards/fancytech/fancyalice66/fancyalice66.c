/* Copyright 2022 chent7 <https://github.com/chent7>
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

#include "fancyalice66.h"

#ifdef RGB_MATRIX_ENABLE

#define XX NO_LED

led_config_t g_led_config = {{
    //It's mirrored
    { 14, XX, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0  },
    { 29, 28, 27, 26, 25, 24, 23, 22, 21, XX, 20, 19, 18, 17, 16, 15 },
    { 43, XX, 42, 41, 40, 39, 38, 37, 36, XX, 35, 34, 33, 32, 31, 30 },
    { XX, 56, XX, 55, 54, 53, 52, 51, 50, XX, 49, 48, 47, 46, 45, 44 },
    { 65, 64, 63, XX, XX, 62, XX, XX, 61, 60, XX, XX, 59, 58, XX, 57 }
}, {
    //Key matrix (0 -> 65)
    {224, 0},           {194, 0}, {180, 0}, {164, 0}, {150, 0}, {135, 0}, {120, 0}, {105, 0}, {90,  0}, {75,  0}, {60,  0}, {45,  0}, {30,  0}, {15,  0}, {0,   0},
    {224,16}, {209,16}, {194,16}, {180,16}, {164,16}, {150,16}, {135,16}, {120,16}, {105,16},           {75, 16}, {60, 16}, {45, 16}, {30, 16}, {15, 16}, {0,  16},
    {224,32},           {194,32}, {180,32}, {164,32}, {150,32}, {135,32}, {120,32}, {105,32},           {75, 32}, {60, 32}, {45, 32}, {30, 32}, {15, 32}, {0,  32},
              {209,48},           {180,48}, {164,48}, {150,48}, {135,48}, {120,48}, {105,48},           {75, 48}, {60, 48}, {45, 48}, {30, 48}, {15, 48}, {0,  48},
    {224,64}, {209,64}, {194,64},                     {150,64},                     {105,64}, {90, 64},                     {45, 64}, {30, 64},           {0,  64},

    //Underglow (66 -> 81)
    {0,  64}, {0,  32}, {0,   0}, {37,  0}, {75,  0}, {112, 0}, {149, 0}, {187, 0}, {224, 0}, {224,32}, {224,64}, {187,64}, {149,64}, {112,64}, {75, 64}, {37, 64}
}, {
    //Key matrix (0 -> 65)
	4,    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
	4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4, 1,
	4,    1, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4, 1,
	   4,    4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4, 1,
	4, 4, 4,       1,       4, 1,       4, 1,    1,

    //Underglow (66 -> 81)
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
}};

__attribute__ ((weak))
void rgb_matrix_indicators_user(void)
{
    if (host_keyboard_led_state().caps_lock)
    {
        rgb_matrix_set_color(43, 0xFF, 0xFF, 0xFF);
    }
}

#endif

#if defined(ENCODER_ENABLE) && !defined(VIA_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { 
        return false; 
    }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return true;
}
#endif
