/* Copyright 2020 DmNosachev
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

void matrix_init_kb(void) {
  /* LED pins setup */
  setPinOutput(LED_KANA_PIN);
  setPinOutput(LED_CAPS_LOCK_PIN);
  setPinOutput(LED_CTRL_XFER_PIN);
  setPinOutput(LED_NUM_LOCK_PIN);
  setPinOutput(LED_KB_LOCK_PIN);
  
  writePinHigh(LED_KANA_PIN);
  writePinHigh(LED_CAPS_LOCK_PIN);
  writePinHigh(LED_CTRL_XFER_PIN);
  writePinHigh(LED_NUM_LOCK_PIN);
  writePinHigh(LED_KB_LOCK_PIN);

    matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(LED_NUM_LOCK_PIN, !led_state.num_lock);
        writePin(LED_CAPS_LOCK_PIN, !led_state.caps_lock);
        writePin(LED_CTRL_XFER_PIN, !led_state.scroll_lock);
    }
    return res;
}
