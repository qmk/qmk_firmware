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
#include QMK_KEYBOARD_H


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        { 0, 1, 2, 3 },  \
        { 6, 5, 4, NO_LED },  \
        { 7, 8, 9, 10 },  \
        { 13, 12, 11, NO_LED },  \
        { NO_LED, 14, 15, 16 }  \
    },
    {
      // LED Index to Physical Position
        {0,0},    {75,0},   {149,0},  {224,0}, \
        {224,16}, {149,16}, {75,16}, \
        {0,32},   {75,32},  {149,32}, {224,32}, \
        {224,48}, {149,48}, {75,48},\
                  {75,64},  {149,64}, {224,64}\
    },
    {
      // LED Index to Flag
      4, 4, 4, 4, \
      4, 4, 4, \
      4, 4, 4, 4, \
      4, 4, 4, \
         4, 4, 4 \
    }
};


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
