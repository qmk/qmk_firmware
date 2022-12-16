/* Copyright 2020 Alabahuy
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

#include "dokb16.h"


#ifdef RGB_MATRIX_ENABLE

 led_config_t g_led_config = { {
  // Key Matrix to LED Index
  { 0,    1,   2,   3},
  { 4,    5,   6,    7},
  { 8,     9,    10,    11},
  { 12,     13,    14,    15}
}, {
    {0,0},  {75,0}, {150,0}, {224,0},
{0,22},{75,22},{150,22},{224,22},
{0,43},{75,43},{150,43},{224,43},
{0,64},{75,64},{150,64},{224,64},
}, { 
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4
} };

void suspend_power_down_kb(void) {
  rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void) {
  rgb_matrix_set_suspend_state(false);
}

#endif