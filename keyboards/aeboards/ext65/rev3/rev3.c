/* Copyright 2022 Harrison Chan (Xelus)
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
#include "rev3.h"

#define LED_NUM_LOCK_PIN F5
#define LED_CAPS_LOCK_PIN F4
#define LED_SCROLL_LOCK_PIN F1
#define LED_4 F0

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.
  // Set our LED pins as output
  setPinOutput(LED_NUM_LOCK_PIN);
  setPinOutput(LED_CAPS_LOCK_PIN);
  setPinOutput(LED_SCROLL_LOCK_PIN);
  setPinOutput(LED_4);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(LED_NUM_LOCK_PIN, led_state.num_lock);
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
        writePin(LED_SCROLL_LOCK_PIN, led_state.scroll_lock);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
      case 1:
        writePinHigh(LED_4);
        break;
      default: //  for any other layers, or the default layer
        writePinLow(LED_4);
        break;
      }
    return layer_state_set_user(state);
}
