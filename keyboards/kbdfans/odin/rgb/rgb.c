/* Copyright 2021 Dztech
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
led_config_t g_led_config = {
    {
        { 0,   NO_LED,   1,      2,      3,      4, NO_LED,      5,      6,      7,      8,  9,     10, 11,     12,     13, 14, 15, 16,     17 },
        { 36,      35,  34,     33,     32,     31,     30,     29,     28,     27,     26, 25,     24, 23, NO_LED,     22, 21, 20, 19,     18 },
        { 37,      38,  39,     40,     41,     42,     43,     44,     45,     46,     47, 48,     49, 50, NO_LED,     51, 52, 53, 54,     55 },
        { 75,      74,  73,     72,     71,     70,     69,     68,     67,     66,     65, 64, NO_LED, 63, NO_LED, NO_LED, 58, 57, 56, NO_LED },
        { 76,  NO_LED,  77,     78,     79,     80,     81,     82,     83,     84,     85, 86, NO_LED, 87, NO_LED,     88, 89, 90, 91,     92 },
        { 103,    102, 101, NO_LED, NO_LED, NO_LED,    100, NO_LED, NO_LED, NO_LED, NO_LED, 99, NO_LED, 98,     97,     96, 95, 94, 93, NO_LED }
    }, {
        {   0,  0 }, {  24,  0 }, {  36,  0 }, {  48,  0 }, {  60,  0 }, {  84,  0 }, {  96,  0 }, { 108,  0 }, { 120,  0 }, { 132,  0 }, { 144,  0 }, { 156,  0 }, { 168,  0 }, { 180,  0 }, { 192,  0 }, { 204,  0 }, { 216,  0 }, { 224,  0 },
        { 224, 14 }, { 216, 14 }, { 204, 14 }, { 192, 14 }, { 180, 14 }, { 156, 14 }, { 144, 14 }, { 132, 14 }, { 120, 14 }, { 108, 14 }, { 96,  14 }, {  84, 14 }, {  72, 14 }, {  60, 14 }, {  48, 14 }, {  36, 14 }, {  24, 14 }, { 12,  14 }, {   0, 14 },
        {   0, 27 }, {  12, 27 }, {  24, 27 }, {  36, 27 }, {  48, 27 }, {  60, 27 }, {  72, 27 }, {  84, 27 }, {  96, 27 }, { 108, 27 }, { 120, 27 }, { 132, 27 }, { 144, 27 }, { 156, 27 }, { 180, 27 }, { 192, 27 }, { 204, 27 }, { 216, 27 }, { 224, 33 },
        { 216, 40 }, { 204, 40 }, { 192, 40 }, { 224,  0 }, {   0,  0 }, {   0, 64 }, { 224, 64 }, { 156, 40 }, { 132, 40 }, { 120, 40 }, { 108, 40 }, {  96, 40 }, {  84, 40 }, {  72, 40 }, {  60, 40 }, {  48, 40 }, {  36, 40 }, {  24, 40 }, {  12, 40 }, {   0, 40 },
        {   0, 52 }, {  24, 52 }, {  36, 52 }, {  48, 52 }, {  60, 52 }, {  72, 52 }, { 84,  52 }, {  96, 52 }, { 108, 52 }, { 120, 52 }, { 132, 52 }, { 156, 52 }, { 180, 52 }, { 192, 52 }, { 204, 52 }, { 216, 52 }, { 224, 58 },
        { 216, 64 }, { 204, 64 }, { 192, 64 }, { 180, 64 }, { 168, 64 }, { 156, 64 }, { 132, 64 }, {  72, 64 }, {  24, 64 }, { 12,  64 }, {   0, 64 }
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(75, 0xFF, 0xFF, 0xFF);
    }
    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(21, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
