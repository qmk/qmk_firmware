/* Copyright 2020 Ealdin Keyboards
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
#include "quadrant.h"

void quadrant_led_on() {
  writePinHigh(F0);
}

void quadrant_led_off() {
  writePinLow(F0);
}

void keyboard_pre_init_kb(void) {
  // Initialize Caps Lock LED
  setPinOutput(F0);
  keyboard_pre_init_user();
}

// Rotary encoder functions:

#define MEDIA_KEY_DELAY 5

uint8_t layer = 0;

uint32_t layer_state_set_kb(uint32_t state) {
  state = layer_state_set_user(state);
  layer = biton32(state);
  return state;
}

void encoder_update_kb(uint8_t index, bool clockwise) {
  uint16_t mapped_code = 0;
  if (index == 0) {
    if (clockwise) {
        switch(layer){
            case 0:
            default:
                mapped_code = KC_VOLD;
                break;
            case 1:
                mapped_code = KC_MEDIA_PREV_TRACK;
                break;
            case 2:
                mapped_code = KC_PGUP;
                break;
        }
    } else {
        switch(layer){
            case 0:
            default:
                mapped_code = KC_VOLU;
                break;
            case 1:
                mapped_code = KC_MEDIA_NEXT_TRACK;
                break;
            case 2:
                mapped_code = KC_PGDN;
                break;
        }
    }
    uint16_t held_keycode_timer = timer_read();
    register_code(mapped_code);
    while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
    unregister_code(mapped_code);
  }
}
