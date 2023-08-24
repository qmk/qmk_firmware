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
#ifndef RGB_BACKLIGHT_NK87
#error RGB_BACKLIGHT_NK87 not defined, recheck config.h
#endif

#include "nk87.h"
#include "drivers/led/issi/is31fl3733.h"

/* Indicator LEDS are part of the LED driver
 * Top LED is blue only. LED driver 2 RGB 63 Blue channel
 * Middle LED is blue and red. LED driver 2 RGB 63 Red and Green channel
 * Bottom LED is red only LED driver 2 RGB 48 Blue channel.
 */
uint8_t CAPS = 0;
uint8_t FN1 = 0;
uint8_t FN2 = 0;

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        if (led_state.caps_lock) {
            CAPS = 255;
        } else {
            CAPS = 0;
        }
    }
    is31fl3733_set_color( 63+64-1, FN1, FN1, CAPS );
    is31fl3733_set_color( 48+64-1, 0, 0, FN2 );
    return res;
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    if (state & (1UL << 1)) {
        FN1 = 255;
    } else {
        FN1 = 0;
    }
    if (state & (1UL << 2)) {
        FN2 = 255;
    } else {
        FN2 = 0;
    }
  return state;
}
