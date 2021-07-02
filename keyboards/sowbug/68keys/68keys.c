/* Copyright 2021 Mike Tsao
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

// 68keys.c

#include "68keys.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
 // Key Matrix to LED Index
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
  { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 },
  { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, NO_LED, NO_LED, NO_LED },
  { 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, NO_LED, NO_LED, NO_LED },
  { 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position
  {0, 0}, {12, 0}, {25, 0}, {38, 0}, {51, 0}, {64, 0}, {77, 0}, {90, 0}, {103, 0}, {116, 0}, {129, 0}, {142, 0}, {155, 0}, {175, 0}, {198, 0}, {211, 0}, {3, 12}, {19, 12}, {32, 12}, {45, 12}, {58, 12}, {71, 12}, {84, 12}, {97, 12}, {110, 12}, {123, 12}, {136, 12}, {149, 12}, {162, 12}, {178, 12}, {198, 12}, {211, 12}, {4, 25}, {22, 25}, {35, 25}, {48, 25}, {61, 25}, {74, 25}, {87, 25}, {100, 25}, {113, 25}, {126, 25}, {139, 25}, {152, 25}, {173, 25}, {8, 38}, {29, 38}, {42, 38}, {55, 38}, {68, 38}, {81, 38}, {94, 38}, {107, 38}, {120, 38}, {133, 38}, {146, 38}, {170, 38}, {198, 38}, {1, 51}, {17, 51}, {34, 51}, {82, 51}, {131, 51}, {147, 51}, {163, 51}, {185, 51}, {198, 51}, {211, 51}
}, {
  // LED Index to Flag
  LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
}
};

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}
#endif  // #ifdef RGB_MATRIX_ENABLE
