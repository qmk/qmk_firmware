/* Copyright 2021 DZTECH <moyi4681@Live.cn>
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
    {  0,  1,  2,  3,      4,      5,  6,      7,       8, 9,  10, 11, 12, 13,    15},
    {  30, 29, 28, 27,     26,     25, 24,     23,     22, 21, 20, 19, 18, 17,    16},
    {  31, 32, 33, 34,     35,     36, 37,     38,     39, 40, 41, 42, 43, 44,    45},
    {  59, 58, 57, 56,     55,     54, 53,     52,     51, 50, 49, 48, 14, 47,    46},
    {  60, 61, 62, 63,     64,     65, 66,     67,     68, 69, 70, 71, NO_LED,72, 73},
    {  83, 82, 81, NO_LED, NO_LED, 80, NO_LED, NO_LED, 79, 78, 77, 76, NO_LED,75 ,74}
}, {
    {0, 0},   {15, 0},  {30, 0},{45, 0}, {60, 0}, {75, 0}, {90, 0}, {105, 0}, {120, 0}, {135, 0}, {150, 0}, {165, 0}, {180, 0},  {195, 0}, {210, 0}, {224, 0},
    {224, 12}, {218, 12},{192, 12},{176, 12},{160, 12},{144, 12},{128, 12},{112, 12},{96, 12},{80, 12},{64, 12},{48, 12},{32, 12},{16, 12},{0, 12},
    {0, 25},{16, 25}, {32, 25}, {48, 25},  {64, 25},  {80, 25},  {96, 25},  {112, 25}, {128, 25}, {144, 25}, {160, 25},{176, 25}, {192, 25},   {218, 25}, {224, 25},
{224, 38},{200, 38},{176, 38},{160, 38},{144, 38},{128, 38},{112, 38},{96, 38},{80, 38},{64, 38},{48, 38},{32, 38},{16, 38},{0, 38},
    {0, 51},{16, 51}, {32, 51}, {48, 51},  {64, 51},  {80, 51},  {96, 51},  {112, 51}, {128, 51}, {144, 51}, {160, 51},   {189, 51}, {218, 51},   {224, 51},
{224, 64},{218, 64},{192, 64},{176, 64},{160, 64},{144, 64}, {80, 64}, {32, 64},{16, 64},{0, 64}
}, {
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,1,4,1,1,1,4,4,4,
4,4,4,4
} };


bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock)
    {
        rgb_matrix_set_color(59, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
