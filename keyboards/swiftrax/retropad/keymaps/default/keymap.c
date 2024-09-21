  /* Copyright 2020 swiftrax
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

[0] = LAYOUT(
  TO(1), //windows
  KC_MSTP, KC_MPLY,
  KC_MPRV, KC_MNXT),

[1] = LAYOUT( //macOS
  TO(2),
  KC_MSTP, KC_MPLY,
  KC_MRWD, KC_MFFD),

[2] = LAYOUT(
  TO(0),
  KC_HOME, KC_PGUP,
  KC_END,  KC_PGDN),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if(IS_LAYER_ON(2)){
    if (clockwise)
      tap_code(KC_LEFT);
    else
      tap_code(KC_RGHT);
  }
  else{
    if(clockwise)
      tap_code(KC_VOLU);
    else
      tap_code(KC_VOLD);
  }
    return true;
}

void matrix_init_user(void) {
  // set top LED to output and off (active low)
  gpio_set_pin_output(D5);
  gpio_write_pin_high(D5);
  // set middle LED to output and off (active low)
  gpio_set_pin_output(D4);
  gpio_write_pin_high(D4);
  // set bottom LED to output and off (active low)
  gpio_set_pin_output(D3);
  gpio_write_pin_high(D3);
}

// write to above indicators in a binary fashion based on current layer
layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin(D5, get_highest_layer(state));
    gpio_write_pin(D4, !layer_state_cmp(state, 1));
    gpio_write_pin(D3, !layer_state_cmp(state, 2));
    return state;
}
