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
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}
void rgb_matrix_indicators_kb(void) {
    if (host_keyboard_led_state().caps_lock) {  // Capslock = RED
        //rgb_matrix_set_color(44, 200, 0, 0);
        rgb_matrix_set_color(46, 200, 0, 0);

    }
    //if (host_keyboard_led_state().scroll_lock) {  // Capslock = RED
      //  rgb_matrix_set_color(15, 200, 0, 0);

   // }
}

#endif  // #ifdef RGB_MATRIX_ENABLE
