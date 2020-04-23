/* Copyright 2020 Michele Ferri <zomgsako@gmail.com>
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
#include "paddino03.h"
#include "tmk_core/common/eeprom.h"
#include "print.h"

void keyboard_pre_init_kb(void) {
  // Set the layer LED IO as outputs
  setPinOutput(LAYER_INDICATOR_LED_0);
  setPinOutput(LAYER_INDICATOR_LED_1);
  setPinOutput(LAYER_INDICATOR_LED_2);
  setPinOutput(LAYER_INDICATOR_LED_3);
  keyboard_pre_init_user();
}

void shutdown_user() {
  // Shutdown all layer LEDs
  writePinLow(LAYER_INDICATOR_LED_0);
  writePinLow(LAYER_INDICATOR_LED_1);
  writePinLow(LAYER_INDICATOR_LED_2);
  writePinLow(LAYER_INDICATOR_LED_3);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
  // Turn on LED of current layer
  uint8_t layer = biton32(state);
  writePin(LAYER_INDICATOR_LED_0, layer == 0);
  writePin(LAYER_INDICATOR_LED_1, layer == 1);
  writePin(LAYER_INDICATOR_LED_2, layer == 2);
  writePin(LAYER_INDICATOR_LED_3, layer == 3);
  return layer_state_set_user(state);
}

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  for (int i = 0; i < 4; i++) {
    writePin(LAYER_INDICATOR_LED_0, true);
    writePin(LAYER_INDICATOR_LED_1, false);
    writePin(LAYER_INDICATOR_LED_2, false);
    writePin(LAYER_INDICATOR_LED_3, false);
    wait_ms(100);
    writePin(LAYER_INDICATOR_LED_0, false);
    writePin(LAYER_INDICATOR_LED_1, true);
    writePin(LAYER_INDICATOR_LED_2, false);
    writePin(LAYER_INDICATOR_LED_3, false);
    wait_ms(100);
    writePin(LAYER_INDICATOR_LED_0, false);
    writePin(LAYER_INDICATOR_LED_1, false);
    writePin(LAYER_INDICATOR_LED_2, true);
    writePin(LAYER_INDICATOR_LED_3, false);
    wait_ms(100);
    writePin(LAYER_INDICATOR_LED_0, false);
    writePin(LAYER_INDICATOR_LED_1, false);
    writePin(LAYER_INDICATOR_LED_2, false);
    writePin(LAYER_INDICATOR_LED_3, true);
    wait_ms(100);
  }

  writePin(LAYER_INDICATOR_LED_0, true);
  writePin(LAYER_INDICATOR_LED_1, false);
  writePin(LAYER_INDICATOR_LED_2, false);
  writePin(LAYER_INDICATOR_LED_3, false);

  matrix_init_user();
}

uint8_t selected_layer = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ENCODER_PRESS:
      if (record->event.pressed) {
        // Do something when pressed
      } else {
        // Do something else when release
        if (selected_layer < 3) {
            selected_layer ++;
        }
        else {
            selected_layer = 0;
        }
        layer_move(selected_layer);
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

void encoder_update_kb(uint8_t index, bool clockwise) {
    uint16_t keycode = get_encoder_key(clockwise ? ENCODER_CW : ENCODER_CCW);
    if (keycode > 0) {
        tap_code(keycode);
    }
}

uint16_t get_encoder_key(uint8_t rotation) {
    // look for the mapped keycode on this layer
    keyevent_t pressed;
    switch (rotation) {
        case ENCODER_CW:
            // find keycode mapped to fake button at row0, col8
            pressed = (keyevent_t){ .key = (keypos_t){.row = 0, .col = 8}, .pressed = true, .time = (timer_read() | 1)};
            break;
        default:
            // find keycode mapped to fake button at row0, col7
            pressed = (keyevent_t){ .key = (keypos_t){.row = 0, .col = 7}, .pressed = true, .time = (timer_read() | 1)};
            break;
    }
    return get_event_keycode(pressed);
}
