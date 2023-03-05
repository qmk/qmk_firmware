/* Copyright 2020 Geekboards ltd. (geekboards.ru / geekboards.de)
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
    {13,19,20,26}, {6,0,38,33},
}, {
    // LED Index to Physical Position
    {85,46},
    {85,64},{67,64},{49,64},{31,64},{13,64},
    {31,46},
    {0,55},{0,46},{0,37},{0,27},{0,18},{0,9},
    {31,18},
    {13,0},{31,0},{49,0},{67,0},{85,0},
    {85,18},{139,18},
    {139,0},{157,0},{175,0},{193,0},{211,0},
    {193,18},
    {224,9},{224,18},{224,27},{224,37},{224,46},{224,55},
    {193,46},
    {211,64},{193,64},{175,64},{157,64},
    {139,46},
    {139,64},{121,64},{103,64},
}, {
    // LED Index to Flag, 2=backlight, 4=key
    4,
    2, 2, 2, 2, 2, 
    4, 
    2, 2, 2, 2, 2, 2,
    4, 
    2, 2, 2, 2, 2,
    4, 4,
    2, 2, 2, 2, 2,
    4,
    2, 2, 2, 2, 2, 2,
    4, 
    2, 2, 2, 2,
    4,
    2, 2, 2
} };

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
