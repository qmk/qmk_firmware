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
#include "tdcq64_2s.h"




#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        { NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }, \
        { NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }, \
        { NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }, \
        { NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }, \
        { NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED }  \
    },
    {
      // LED Index to Physical Position
        {0,48},        {32,48},        {64,48},        {96,48},         {128,48},         {160,48},         {192,48},\
                       {192,0},        {160,0},        {128,0},         {96,0},           {64,0},           {32,0},            {0,0}
    },
    {
      // LED Index to Flag
      2,2,2,2,2,2,2,2,2,2,2,2,2,2
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
