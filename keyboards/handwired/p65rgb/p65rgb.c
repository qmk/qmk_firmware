/* Copyright 2019 marhalloweenvt
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

#include "p65rgb.h"

led_config_t g_led_config = { {
    { 0,   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16 },
    { 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17 },
    { 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50 },
    { 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51 },
    { 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82 }
}, {
    { 0,   0 }, { 15,   0 }, { 30,   0 }, { 45,   0 }, { 60,   0 }, { 75,   0 }, { 90,   0 }, {105,   0 }, {120,   0 }, {135,   0 }, {150,   0 }, {165,   0 }, {180,   0 }, {195,   0 }, {205,   0 }, {210,   0 }, {224,   0 },
    { 224,16 }, {224,  16 }, {210,  16 }, {180,  16 }, {165,  16 }, {150,  16 }, {135,  16 }, {120,  16 }, {105,  16 }, { 90,  16 }, { 75,  16 }, { 60,  16 }, { 45,  16 }, { 30,  16 }, { 15,  16 }, {  0,  16 }, {  0,  16 },
    { 0,  32 }, {  0,  32 }, { 15,  32 }, { 30,  32 }, { 45,  32 }, { 60,  32 }, { 75,  32 }, { 90,  32 }, {105,  32 }, {120,  32 }, {135,  32 }, {150,  32 }, {165,  32 }, {190,  32 }, {205,  32 }, {210,  32 }, {224,  32 },
    { 224, 8 }, {224,  48 }, {210,  48 }, {195,  48 }, {180,  48 }, {150,  48 }, {135,  48 }, {120,  48 }, {105,  48 }, { 90,  48 }, { 75,  48 }, { 60,  48 }, { 45,  48 }, { 30,  48 }, { 15,  48 }, {  0,  48 }, {  0,  48 },
    { 0,  64 }, {  0,  64 }, {  0,  64 }, { 15,  64 }, { 15,  64 }, { 40,  64 }, { 90,  64 }, {105,  64 }, {150,  64 }, {180,  64 }, {180,  64 }, {195,  64 }, {210,  64 }, {220,  64 }, {224,  64 }
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 2,
    2, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    2, 2, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 2,
    2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2
} };

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
