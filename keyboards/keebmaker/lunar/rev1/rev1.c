/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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
#include "rev1.h"

void matrix_init_kb(void) {
  matrix_init_user();
};

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
    {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11 },
    {  23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12 },
    {  24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 },
    {  47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36 },
    {  48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59 }
}, {
    {   0,   0 }, {  20,   0 }, {  40,   0 }, {  60,   0 }, {  80,   0 }, {  100,   0 }, {  120,   0 }, {  140,   0 }, {  160,   0 }, {  180,   0 }, {  200,    0 }, {  220,    0 },
    { 220,  12 }, { 200,  12 }, { 180,  12 }, { 160,  12 }, { 140,  12 }, {  120,  12 }, {  100,  12 }, {   80,  12 }, {   60,  12 }, {   40,  12 }, {   20,   12 }, {    0,   12 },
    {   0,  24 }, {  20,  24 }, {  40,  24 }, {  60,  24 }, {  80,  24 }, {  100,  24 }, {  120,  24 }, {  140,  24 }, {  160,  24 }, {  180,  24 }, {  200,   24 }, {  220,   24 },
    { 220,  36 }, { 200,  36 }, { 180,  36 }, { 160,  36 }, { 140,  36 }, {  120,  36 }, {  100,  36 }, {   80,  36 }, {   60,  36 }, {   40,  36 }, {   20,   36 }, {    0,   36 },
    {   0,  48 }, {  20,  48 }, {  40,  48 }, {  60,  48 }, {  80,  48 }, {  100,  48 }, {  120,  48 }, {  140,  48 }, {  160,  48 }, {  180,  48 }, {  200,   48 }, {  220,   48 },
    }, {
    1,4,4,4,4,4,4,4,4,4,4,1,
    1,4,4,4,4,4,4,4,4,4,4,1,
    1,4,4,4,4,4,4,4,4,4,4,1,
    1,4,4,4,4,4,4,4,4,4,4,1,
    1,1,1,1,1,1,1,1,1,1,1,1
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
