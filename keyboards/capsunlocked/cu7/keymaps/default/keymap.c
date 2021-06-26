/*
Copyright 2021 CapsUnlocked

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

#define MEDIA_KEY_DELAY 10

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
             MO(1),
    KC_1,    KC_2,    KC_3,
    KC_4,    KC_5,    KC_6
  ),
  [1] = LAYOUT(
             _______,
    RGB_MOD, KC_UP,   RESET,
    KC_LEFT, KC_DOWN, KC_RGHT
  ),
};

// Volume up/down on the encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
  uint16_t held_keycode_timer = timer_read();

  if (clockwise) {
    register_code(KC_VOLU);
    while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {}
    unregister_code(KC_VOLU);
  }
  else {
    register_code(KC_VOLD);
    while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY) {}
    unregister_code(KC_VOLD);
  }

  return true;
}
