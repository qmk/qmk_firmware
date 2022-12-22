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

#include "nk87.h"
#include "quantum.h"

#include "indicator.h"

#ifdef RGB_MATRIX_ENABLE

uint8_t caps = 0;
uint8_t fn1 = 0;
uint8_t fn2 = 0;


bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        caps = 255;
    } else {
        caps = 0;
    }

    indicators_update(caps, fn1, fn2);

    return true;
}


__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    if (state & (1UL << 1)) {
        fn1 = 255;
    } else {
        fn1 = 0;
    }
    if (state & (1UL << 2)) {
        fn2 = 255;
    } else {
        fn2 = 0;
    }
  return state;
}

#endif // RGB_MATRIX_ENABLE