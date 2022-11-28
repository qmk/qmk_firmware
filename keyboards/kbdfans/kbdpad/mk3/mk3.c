/* Copyright 2022 DZTECH <moyi4681@Live.cn>
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
#include "mk3.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,  1,  2,  3        },
    {  7,  6,  5,  4        },
    {  8,  9,  10, 11       },
    {  14, 13, 12, NO_LED   },
    {  15, 16, 17, 18       },
    {  20, NO_LED, 19,NO_LED }
}, {
    {0, 0},   {75, 0},  {150, 0},{224, 0}, 
    {224, 12.8}, {150, 12.8},{75, 12.8},{0, 12.8},
    {0, 25.6}, {75, 25.6},{150, 25.6},{224, 32}, 
    {150, 38.4}, {75, 38.4},{0, 38.4},
    {0, 51.2}, {75, 51.2},{150, 51.24},{224, 57.6}, 
    {150, 64}, {37.5, 64}                                                                                  
}, {
4,4,4,4,
4,4,4,4,
4,4,4,4,
4,4,4,
4,4,4,4,
4,4
} };


__attribute__ ((weak))
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) { 
        return false;
    }
{
    if (host_keyboard_led_state().num_lock)
    {
        rgb_matrix_set_color(7, 0xFF, 0xFF, 0xFF);
    }
}
#endif
