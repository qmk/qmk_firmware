/*
Copyright 2025 Snappy Key <snappykey@gmail.com>

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
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    TO(1),                  KC_MPLY,
    KC_F13, KC_F14, KC_F15, KC_F16,
    KC_F17, KC_F18, KC_F19, KC_F20,
    KC_F21, KC_F22, KC_F23, KC_F24
  ),
  [1] = LAYOUT(
    TO(2),                                    KC_TRNS,
    LSFT(KC_F13), LSFT(KC_F14), LSFT(KC_F15), LSFT(KC_F16),
    LSFT(KC_F17), LSFT(KC_F18), LSFT(KC_F19), LSFT(KC_F20),
    LSFT(KC_F21), LSFT(KC_F22), LSFT(KC_F23), LSFT(KC_F24)
  ),
  [2] = LAYOUT(
      TO(3),                                    KC_TRNS,
      LCTL(KC_F13), LCTL(KC_F14), LCTL(KC_F15), LCTL(KC_F16),
      LCTL(KC_F17), LCTL(KC_F18), LCTL(KC_F19), LCTL(KC_F20),
      LCTL(KC_F21), LCTL(KC_F22), LCTL(KC_F23), LCTL(KC_F24)
  ),
  [3] = LAYOUT(
      TO(0),                                    KC_TRNS,
        LALT(KC_F13), LALT(KC_F14), LALT(KC_F15), LALT(KC_F16),
        LALT(KC_F17), LALT(KC_F18), LALT(KC_F19), LALT(KC_F20),
        LALT(KC_F21), LALT(KC_F22), LALT(KC_F23), LALT(KC_F24)
  )

};
layer_state_t layer_state_set_user(layer_state_t state) {
    if (!gpio_read_pin(B6)) {
        switch (get_highest_layer(state)) {
        case 0:
	         gpio_write_pin_low(F7);
             gpio_write_pin_low(B2);
             gpio_write_pin_low(B5);
	    	break;
        case 1:
             gpio_write_pin_high(F7);
             gpio_write_pin_low(B2);
             gpio_write_pin_low(B5);
            break;
        case 2:
		     gpio_write_pin_high(F7);
             gpio_write_pin_high(B2);
             gpio_write_pin_low(B5);
            break;
        case 3:
             gpio_write_pin_high(F7);
             gpio_write_pin_high(B2);
             gpio_write_pin_high(B5);
            break;
        }
    }
  return state;
}
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(_______, _______) },
    [2] = { ENCODER_CCW_CW(_______, _______) },
    [3] = { ENCODER_CCW_CW(_______, _______) }
};
#endif
