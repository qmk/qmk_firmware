/* Copyright 2020
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_5x4(
    KC_A, KC_B,  KC_C,  KC_D,
    KC_E, KC_F,  KC_G,  KC_H,
    KC_I, KC_J,  KC_K,  KC_L,
    KC_M, KC_N,  KC_O,  KC_P,
    KC_Q, KC_R,  KC_S,  KC_T
  ),
  [1] = LAYOUT_ortho_5x4(
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS
  ),
  [2] = LAYOUT_ortho_5x4(
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS
  ),

  [3] = LAYOUT_ortho_5x4(
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS
  )
};

void encoder_update_user(uint8_t index, bool clockwise) {
  uint8_t layer = biton32(layer_state);
  if (index == 0) /* Right encoder */ {
    if (clockwise) {
      register_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 3
      }));
      unregister_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 3
      }));
    } else {
      register_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 2
      }));
      unregister_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 2
      }));
    }
  } else if (index == 1) /* Left encoder */ {
    if (clockwise) {
      register_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 1
      }));
      unregister_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 1
      }));
    } else {
      register_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 0
      }));
      unregister_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 4, .col = 0
      }));
    }
  }
}
