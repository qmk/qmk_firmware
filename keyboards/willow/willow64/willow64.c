/* Copyright 2021 Hanachi
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
#include "willow64.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {  3,     4,     11,      12, 21, 22, NO_LED,  NO_LED},
  {  2,     5,     10,      13, 20, 23, NO_LED,  NO_LED},
  {  1,     6,      9,      14, 19, 24, NO_LED,  NO_LED},
  {  0,     7,      8,      15, 18, 25, 28,      NO_LED},
  {NO_LED, NO_LED, NO_LED, 16, 17, 26, 27,      NO_LED},
  {NO_LED, 35, 36, 45, 46,     53,     54,  61},
  {NO_LED, 34, 37, 44, 47,     52,     55,  62},
  {NO_LED, 33, 38, 43, 48,     51,     56,  58},
  {    29, 32, 39, 42, 49,     50,     60,  57},
  {    30, 31, 40, 41, NO_LED, NO_LED, 59,  63},
}, {
{0, 33},{7, 23},{11, 12},{15, 1},{28, 3},{26, 15},{24, 27},{20, 38},
{33, 38},{37, 26},{39, 14},{40, 2},{52, 0},{52, 12},{50, 24},{47, 36},
{43, 47},{54, 51},{58, 40},{61, 29},{63, 17},{64, 5},{76, 12},{75, 24},
{72, 36},{69, 47},{63, 59},{74, 64},{80, 52},{123, 52},{128, 64},{139, 59},
{134, 47},{130, 36},{128, 24},{127, 12},{138, 5},{139, 17},{141, 29},{144, 40},
{149, 51},{160, 47},{156, 36},{152, 24},{151, 12},{151, 0},{163, 2},{164, 14},
{166, 26},{169, 38},{183, 38},{179, 27},{176, 15},{175, 3},{187, 3},{189, 14},
{192, 26},{209, 37},{212, 26},{201, 14},{199, 3},{211, 3},{216, 14},{224, 3},
}, {
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,
LED_FLAG_KEYLIGHT,
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_KEYLIGHT,
LED_FLAG_MODIFIER,
LED_FLAG_MODIFIER,


} };

void keyboard_pre_init_kb(void) {
    rgb_matrix_set_flags(LED_FLAG_MODIFIER|LED_FLAG_UNDERGLOW|LED_FLAG_KEYLIGHT);
    keyboard_pre_init_user();
}

#endif
