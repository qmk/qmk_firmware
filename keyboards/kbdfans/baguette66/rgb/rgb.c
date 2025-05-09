/* Copyright 2022 DZTECH <moyi4681@Live.cn>
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,  1,  2,  3,  4,  5,  6,  7,   8,  9,  10, 11,    12,    13,  15 },
    {  30, 29, 28, 27, 26, 25, 24, 23,  22, 21, 20, 19,    18,    17,  16 },
    {  31, 32, 33, 34, 35, 36, 37, 38,  39, 40, 41, 42,    43,NO_LED,  14 },
    {  57, 56, 55, 54, 53, 52, 51, 50,  49, 48, 47, 46,    45,    44, NO_LED},
    {  NO_LED, 58, 59, NO_LED, NO_LED,  60, NO_LED, NO_LED,  61,  NO_LED,  62,  NO_LED,  63, 64,  65 }
}, {
    {0,0},{15,0},{30,0},{45,0},{60,0},{75,0},{90,0},{105,0},{120,0},{135,0},{150,0},{165,0},{180,0},{195,0}, {210,0},{224,0},
    {224,16}, {206,16},{188,16},{173,16},{158,16},{143,16},{128,16},{113,16},{98,16},{83,16},{68,16},{53,16},{38,16},{23,16},{4,16},
    {6,32},{26,32},{41,32},{56,32},{71,32},{86,32},{101,32},{116,32},{131,32},{146,32},{161,32},{176,32},{201,32},
    {220,48},{205,48},{187,48},{169,48},{154,48},{139,48},{124,48},{109,48},{94,48},{79,48},{64,48},{49,48},{34,48},{9,48},
    {21,64},{39,64},{96,64},{152,64},{171,64},{195,64},{210,64},{224,64}
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1, 1, 1
} };

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock)
    {
        rgb_matrix_set_color(31, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
