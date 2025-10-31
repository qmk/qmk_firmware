/*
Copyright 2019 Yiancar

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  DCAPS = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    KC_1,     KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,     KC_0,    KC_SCLN,  KC_CIRC,  KC_BSPC,  KC_ENT,     KC_0,  KC_1,  KC_2,  KC_3,  KC_4,
    KC_TAB,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Z,  KC_U,  KC_I,     KC_O,    KC_P,     KC_RBRC,  KC_PLUS,              KC_5,  KC_6,  KC_7,  KC_8,  KC_9,
    DCAPS,    KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,     KC_L,    KC_BSLS,  KC_RBRC,  KC_DLR,   KC_EQL,     KC_0,  KC_1,  KC_2,  KC_3,  KC_4,
    KC_LSFT,  KC_Y,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,  KC_MINS,                                  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,
                                          KC_SPC
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DCAPS:
      if (record->event.pressed) {
        // When keycode DCAPS is pressed.
        // This is needed for mac.
        tap_code(KC_CAPS);
      } else {
        // When keycode DCAPS is released.
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {
  gpio_set_pin_output(B0);
  gpio_write_pin_low(B0);
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        gpio_write_pin_high(B0);
    } else {
        gpio_write_pin_low(B0);
    }
    return false;
}
