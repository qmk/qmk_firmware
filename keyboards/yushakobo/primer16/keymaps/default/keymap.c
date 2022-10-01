/* Copyright 2022 yushakobo
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
  //,-----------------------------------|
                 KC_F2,  KC_EQL,
  //|--------+--------+--------+--------|
        KC_P7,   KC_P8,   KC_P9, KC_PSLS,
  //|--------+--------+--------+--------|
        KC_P4,   KC_P5,   KC_P6, KC_PAST,
  //|--------+--------+--------+--------|
        KC_P1,   KC_P2,   KC_P3, KC_PMNS,
  //|--------+--------+--------+--------|
        KC_P0, KC_PDOT, KC_PENT, KC_PPLS
  //|-----------------------------------|
  )
};

//A description for expressing the layer position in LED mode.
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (get_highest_layer(state)) {
    case 1:
      rgblight_sethsv_at(HSV_BLUE, 0);
      break;
    case 2:
      rgblight_sethsv_at(HSV_RED, 0);
      break;
    case 3:
      rgblight_sethsv_at(HSV_GREEN, 0);
      break;
    default: //  for any other layers, or the default layer
      rgblight_sethsv_at( 0, 0, 0, 0);
      break;
    }
    rgblight_set_effect_range( 1, 5);
#endif
return state;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN), ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
};
#endif
