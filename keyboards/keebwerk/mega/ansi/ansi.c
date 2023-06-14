/* Copyright 2020 Yiancar
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
#ifndef RGB_BACKLIGHT_KW_MEGA
#error RGB_BACKLIGHT_KW_MEGA not defined, recheck config.h
#endif

#include "ansi.h"
#include "drivers/led/issi/is31fl3733.h"

uint8_t R = 0;
uint8_t G = 0;
uint8_t B = 0;

/* Indicator LEDs are part of the LED driver
 * Here the LEDs are used to indicate layers 1, 2 and 3.
 * Below there is a commented out example of how to use the indicators for capslock.
 */
// bool led_update_kb(led_t led_state) {
//     bool res = led_update_user(led_state);
//     if(res) {
//         if (led_state.caps_lock) {
//             G = 255;
//         } else {
//             G = 0;
//         }
//         IS31FL3733_set_color( 6+64-1, R, G, B );
//     }
//     return res;
// }

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    R = 0;
    G = 0;
    B = 0;
    if (IS_LAYER_ON_STATE(layer_state, 1)) {
        G = 255;
    }
    if (IS_LAYER_ON_STATE(layer_state, 2)) {
        R = 255;
    }
    if (IS_LAYER_ON_STATE(layer_state, 3)) {
        B = 255;
    }
    IS31FL3733_set_color( 6+64-1, R, G, B );
  return state;
}
