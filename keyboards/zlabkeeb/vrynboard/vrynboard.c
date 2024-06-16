/*
Copyright 2024 zlabkeeb (zlabkeeb@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "zlabkeeb.h"

const uint8_t max_layer = 3;
uint8_t current_display_mode = 0;

bool key_pressed = false;

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_user(keycode, record)) {
    return false;
  }
#ifdef OLED_ENABLE
  key_pressed = record->event.pressed;
#endif
  switch (keycode) {
    case LT(0, KC_NO):
      if (record->event.pressed) {
        // on tap
        if (record->tap.count) {
          if (get_highest_layer(layer_state) >= max_layer) {
            layer_clear();
          } else {
            layer_move(get_highest_layer(layer_state) + 1);
          }
        }
#ifdef OLED_ENABLE
        // on hold
        else {
          current_display_mode = (current_display_mode + 1) % 3;
        }
#endif
      }
      return false;
  }
  return true;
}

#ifdef OLED_ENABLE
uint32_t flash_timer = 0;
bool layer_changed = false;

// when the layer is changed, flash the layer number on the screen
layer_state_t layer_state_set_kb(layer_state_t state) {
  flash_timer = timer_read();
  layer_changed = true;

  return layer_state_set_user(state);
}
#endif
