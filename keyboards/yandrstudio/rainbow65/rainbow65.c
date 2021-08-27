/* Copyright 2021 JasonRen(biu)
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

#include "rainbow65.h"


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
    // Key Matrix to LED Index
    //clo
      // 0       1       2       3       4       5       6       7       8       9       10      11      12      13      14  // r0
       { 0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13,     NO_LED},
       {14,     15,     16,     17,     18,     19,     20,     21,     22,     23,      24,     25,     26,     27,     NO_LED},
       {28,     29,     30,     31,     32,     33,     34,     35,     36,     37,      38,      39,    40, NO_LED,     NO_LED},
       {41,     42,     43,     44,     45,     46,     47,     48,     49,     50,      51,     52,     53, NO_LED,     NO_LED},
       {54,     55,     56, NO_LED, NO_LED,     59, NO_LED, NO_LED,     62,     63,      64,     65,     66,     67,     NO_LED},
    },
    {
      // LED Index to Physical Position
      {0, 0}, {16, 0}, {32, 0}, {48, 0}, {64, 0}, {80, 0}, {96, 0}, {112, 0}, {128, 0}, {144, 0}, {160, 0}, {176, 0}, {192, 0}, {208, 0},
      {0, 16}, {16, 16}, {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16}, {112, 16}, {128, 16}, {144, 16}, {160, 16}, {176, 16}, {192, 16}, {208, 16},
      {0, 32}, {16, 32}, {32, 32}, {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32}, {192, 32},
      {0, 48}, {16, 48}, {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48}, {112, 48}, {128, 48}, {144, 48}, {160, 48}, {176, 48}, {192, 48},
      {0, 64}, {16, 64}, {32, 64}, {48, 64}, {64, 64}, {80, 64}, {96, 64}, {112, 64}, {128, 64}, {144, 64}, {160, 64}, {176, 64}, {192, 64}, {208, 64},

    },
    {
      // LED Index to Flag
      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,       4,      4,      4,      4,
      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,       4,      4,      4,      4,
      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,       4,      4,      4,
      4,      4,      4,      4,      4,      4,      4,      4,      4,      4,       4,      4,      4,
      4,      4,      4,      255,  255,      4,      255,  255,      4,      4,       4,      4,      4,      4,
    }
};

// void rgb_matrix_indicators_kb(void) {
//   if (rgb_matrix_is_enabled()) {
//     if (biton32(layer_state) == 1) {     // UPPER_LAYER = BLUE
//         rgb_matrix_set_color(57, 100, 0, 0);
//         rgb_matrix_set_color(58, 0, 100, 0);
//         rgb_matrix_set_color(60, 100, 0, 0);
//         rgb_matrix_set_color(61, 100, 0, 0);
//     } else if (biton32(layer_state) == 2)
//     {
//         rgb_matrix_set_color(57, 100, 0, 0);
//         rgb_matrix_set_color(58, 100, 0, 0);
//         rgb_matrix_set_color(60, 0, 100, 0);
//         rgb_matrix_set_color(61, 100, 0, 0);
//     } else if (biton32(layer_state) == 3)
//     {
//         rgb_matrix_set_color(57, 100, 0, 0);
//         rgb_matrix_set_color(58, 100, 0, 0);
//         rgb_matrix_set_color(60, 100, 0, 0);
//         rgb_matrix_set_color(61, 0, 100, 0);
//     } else if (biton32(layer_state) != 0)
//     {
//         rgb_matrix_set_color(57, 150, 0, 0);
//         rgb_matrix_set_color(58, 150, 0, 0);
//         rgb_matrix_set_color(60, 150, 0, 0);
//         rgb_matrix_set_color(61, 150, 0, 0);
//     }
//   }
// }

#endif

#ifdef RGB_DISABLE_WHEN_USB_SUSPENDED
void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
