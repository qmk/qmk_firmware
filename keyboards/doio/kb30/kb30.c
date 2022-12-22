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

#include "kb30.h"


#ifdef RGB_MATRIX_ENABLE

 led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 0,    1,   2,   3,    4,   5,    6},
  { 7,    8,    9,   10,  11,   12,  13},
  { 14,   15,   16,  17,  18,   19,   NO_LED },
  { 20,   21,   22,   23,  NO_LED,   24,  NO_LED},
  { 25,   26,  27,  28,   29,   NO_LED,   NO_LED},
  { 30,   31,  32,  33,   34,  35}
}, {
{0,0}, {37,0}, {75,0}, {112,0}, {149,0}, {187,0}, {224,0},
{0,16}, {37,16}, {75,16}, {112,16}, {149,16}, {187,16}, {224,16},
{0,32}, {37,32}, {75,32}, {112,32}, {149,32}, {187,32},
{0,48}, {37,48}, {75,48}, {112,48},           {187,48},
{0,64}, {37,64}, {65,64}, {112,64}, {149,64}, 
{187,64}, {173,64}, {186,64}, {198,64}, {211,64},{224,64}, 
}, { 
    4,4,4,4,4,4,4,
    4,4,4,4,4,4,4,
    4,4,4,4,4,4,
    4,4,4,4,4,
    4,4,4,4,4,
    4,4,4,4,4,4
} };

void suspend_power_down_kb(void) {
  rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void) {
  rgb_matrix_set_suspend_state(false);
}

#endif



