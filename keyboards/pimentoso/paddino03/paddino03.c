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

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  for (int i = 0; i < 5; i++) {
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
  matrix_init_user();
}

void matrix_scan_kb(void) {
  // put your looping keyboard code here
  // runs every cycle (a lot)
  matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  // put your per-action keyboard code here
  // runs for every action, just before processing by the firmware
  return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
  led_set_user(usb_led);
}

uint8_t selected_layer = 0;
void encoder_update_kb(uint8_t index, bool clockwise) {
    if (clockwise) {
        if (selected_layer < 3) {
            selected_layer ++;
        } else {
            selected_layer = 0;
        }
    } else {
        if (selected_layer > 0) {
            selected_layer --;
        } else {
            selected_layer = 3;
        }
    }
    layer_move(selected_layer);
}
