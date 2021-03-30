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
#include "colorlice.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    { 0,  1,   2,   3,  4,  5,   6,  7,   8,  9,   10,  11,  12,   13,  14,  15  },
    { 30,  29,   28,   27,  26,  25,   24,  23,   22,  21,   20,  19,  18,   17,  16, NO_LED  },
    { 31,  32,   33,   34,  35,  36,   37,  38,   39,  40,   41,  42,  43, NO_LED,  44, NO_LED },
    { 58,  57,   56,   55,  54,  53, NO_LED,  52,   51,  50,   49,  48,  47, 46,    45, NO_LED},
    { 59,  NO_LED, 60,   61,  62,  NO_LED, NO_LED,63, NO_LED,  NO_LED, 64,  65,66,67, 68, NO_LED }
}, {
    { 0,   0 }, { 15,   0 }, { 30,   0 }, { 45,   0 }, { 60,   0 }, { 75,   0 }, { 90,   0 }, { 105,   0 }, { 120,   0 }, {  135,   0 }, {  150,   0 }, {  165,   0 }, {  180,   0 }, {  195,   0 }, {  210,   0 }, {   224,   0 },
    {  224,  16 }, {  210,  16 }, {  195,  16 }, {  180,  16 }, {  165,  16 }, {  150,  16 }, { 135,  16 }, { 120,  16 }, { 90,  16 }, { 75,  16 }, { 60,  16 }, { 45,  16 }, { 30,  16 }, { 15,  16 }, { 0,  16 },
    { 0,  32 }, { 15,  32 }, { 30,  32 }, { 45,  32 }, { 60,  32 }, { 75,  32 }, { 90,  32 }, { 135,  32 }, { 150,  32 }, {  165,  32 }, {  180,  32 }, {  195,  32 }, {  210,  32 }, {  224,  32 },
    {  225,  48 }, {  224,  48 }, {  210,  48 }, {  195,  48 }, {  180,  48 }, {  165,  48 }, { 150,  48 }, { 135,  48 }, { 90,  48 }, { 75,  48 }, { 60,  48 }, { 45,  48 }, { 30,  48 }, { 15, 48 },
    { 15, 64 }, { 45,  64 }, { 75,  64 }, { 90,  64 }, { 150, 64 }, { 180, 64 }, {  210,  64 }, {  215,  64 }, {  220,  64 }, {  225,  64 }
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
#endif

#ifdef RGB_MATRIX_ENABLE
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
#endif

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        writePin(B2, !led_state.num_lock);
        writePin(C6, !led_state.caps_lock);
        writePin(B7, !led_state.scroll_lock);
    }
    return res;
}
