/* Copyright 2019 Yiancar
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
#ifndef RGB_BACKLIGHT_NK65
#error RGB_BACKLIGHT_NK65 not defined, recheck config.h
#endif

#include "nk65.h"
#include "drivers/led/issi/is31fl3733.h"

/* Indicator LEDS are part of the LED driver
 * Top LED is blue only. LED driver 2 RGB 7 Green channel
 * Middle LED is blue and red. LED driver 2 RGB 6 Red and Blue channel
 * Bottom LED is red only LED driver 2 RGB 6 Green channel.
 */
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        if (led_state.caps_lock) {
            IS31FL3733_set_color( 7+64-1, 0, 255, 0 );
        } else {
            IS31FL3733_set_color( 7+64-1, 0, 0, 0 );
        }
    }
    return res;
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;
    if (state & (1UL << 1)) {
        R = 255;
        B = 255;
    }
    if (state & (1UL << 2)) {
        G = 255;
    }

    IS31FL3733_set_color( 6+64-1, R, G, B );
  return state;
}
