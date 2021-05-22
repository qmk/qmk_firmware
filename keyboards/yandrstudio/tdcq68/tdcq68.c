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
#include "tdcq68.h"




#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        { 0,  1,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }, \
        { NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }, \
        { NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED, NO_LED,  NO_LED }, \
        { NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED, NO_LED,  NO_LED,  NO_LED }, \
        { NO_LED,  NO_LED,  NO_LED,  NO_LED, NO_LED, NO_LED, NO_LED,  NO_LED, NO_LED,  NO_LED,  NO_LED, NO_LED, NO_LED,  NO_LED,  NO_LED }  \
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
