/* Copyright 2020 tominabox1, Richard Goulter <richard.goulter@gmail.com>
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

#if defined(RGB_MATRIX_ENABLE)
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0,  1,  2,  3,  4,  5,      6,  7,  8,  9, 10, 11},
        {12, 13, 14, 15, 16, 17,     18, 19, 20, 21, 22, 23},
        {24, 25, 26, 27, 28, 29,     30, 31, 32, 33, 34, 35},
        {36, 37, 38, 39, 40, 41, NO_LED, 42, 43, 44, 45, 46}
    }, {
        // LED Index to Physical Position
        {  0,  0}, { 20,  0}, { 40,  0}, {61,  0}, {81,  0}, {101,  0}, {122,  0}, {142,  0}, {162,  0}, {183,  0}, {203,  0}, {224,  0},
        {  0, 21}, { 20, 21}, { 40, 21}, {61, 21}, {81, 21}, {101, 21}, {122, 21}, {142, 21}, {162, 21}, {183, 21}, {203, 21}, {224, 21},
        {  0, 42}, { 20, 42}, { 40, 42}, {61, 42}, {81, 42}, {101, 42}, {122, 42}, {142, 42}, {162, 42}, {183, 42}, {203, 42}, {224, 42},
        {  0, 64}, { 20, 64}, { 40, 64}, {61, 64}, {81, 64},       {111, 64},      {142, 64}, {162, 64}, {183, 64}, {203, 64}, {224, 64},
        {220, 32}, {176, 32}, {132, 32}, {88, 32}, {44, 32}, {0, 32}
    }, {
        // LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 1, 1,   1,  1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2
    }
};


void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
