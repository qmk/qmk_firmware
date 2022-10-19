/* Copyright 2021 paprikman
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
#include QMK_KEYBOARD_H

uint16_t layer_timer;

enum layer_keycodes {
  TG_LAYER = USER00
};

uint8_t get_hold_layer(void) {
  switch(get_highest_layer(layer_state)) {
    case 0:
    case 1:
      return 1;
    case 2:
    case 3:
      return 3;
    default:
      return 1;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case TG_LAYER:
      if (record->event.pressed) {
        layer_timer = timer_read();
        layer_on(get_hold_layer());
      } else {
        layer_off(get_hold_layer());

        if (timer_elapsed(layer_timer) < TAPPING_TERM) {
          layer_invert(2);
        }
      }

      return false;
      break;
  }

  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
            KC_VOLD, KC_MUTE, KC_VOLU,
    TG_LAYER, KC_MPRV, KC_MPLY, KC_MNXT
  ),
  [1] = LAYOUT(
          RGB_TOG, RGB_MOD, RGB_VAI,
    KC_NO, RGB_SPI, RGB_SPD, RGB_VAD
  ),
  [2] = LAYOUT(
            KC_F1, KC_F2, KC_F3,
    TG_LAYER, KC_F4, KC_F5, KC_F6
  ),
  [3] = LAYOUT(
      LCTL(KC_PSCR), KC_NUM, KC_SCRL,
    KC_NO, _______, _______, _______
  ),
};
