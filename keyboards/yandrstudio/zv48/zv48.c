/* Copyright 2020 zvecr <git@zvecr.com>
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
#include "zv48.h"

void keyboard_pre_init_kb(void){
    // Workaround for reversible pcb/mcu
    palSetLineMode(C13, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(C15, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(B7, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(A0, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(A1, PAL_MODE_OUTPUT_OPENDRAIN);

    keyboard_pre_init_user();
}


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
		{ 0, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, \
		{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, \
		{ NO_LED, 1, NO_LED, NO_LED, NO_LED, NO_LED }, \
		{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, \
		{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, \
		{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, \
		{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, \
		{ NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED } \
    },
    {
      // LED Index to Physical Position
      {0, 0}, {16, 0}

    },
    {
      // LED Index to Flag
      4,      4
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
