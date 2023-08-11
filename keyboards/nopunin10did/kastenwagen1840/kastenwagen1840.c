/* Copyright 2022 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
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

#ifndef LAYER_LED_DISABLE

void keyboard_pre_init_kb(void) {
    setPinOutput(LED_INDICATOR_TOP);
    setPinOutput(LED_INDICATOR_MID);
    setPinOutput(LED_INDICATOR_BOT);
    keyboard_pre_init_user();
}

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    writePinHigh(LED_INDICATOR_TOP);
    writePinHigh(LED_INDICATOR_MID);
    writePinHigh(LED_INDICATOR_BOT);

    switch(get_highest_layer(state) % 4) {
    case 1:
        writePinLow(LED_INDICATOR_TOP);
        writePinLow(LED_INDICATOR_MID);
        break;
    case 2:
        writePinLow(LED_INDICATOR_TOP);
        writePinLow(LED_INDICATOR_BOT);
        break;
    case 3:
        writePinLow(LED_INDICATOR_MID);
        writePinLow(LED_INDICATOR_BOT);
        break;
    }
    return state;
}

#endif

bool encoder_update_kb(uint8_t index, bool clockwise) {
   if (!encoder_update_user(index, clockwise)) { return false; }
   if (clockwise) {
       tap_code(KC_PGUP);
   } else {
       tap_code(KC_PGUP);
   }
   return true;
};
