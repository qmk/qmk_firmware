/* Copyright 2024 set_st
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

enum keycodes {
  KC_CYCLE_LAYERS = QK_USER,
};

enum layers{
  BASE,
  FN,
  MEDIA,
  LIGHT
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// 1st layer on the cycle
#define LAYER_CYCLE_START 0
// Last layer on the cycle
#define LAYER_CYCLE_END   4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
      KC_MEDIA_PLAY_PAUSE,
      KC_CYCLE_LAYERS, LGUI(KC_C), LGUI(KC_V), LCTL(KC_SPC), KC_KP_5,
      KC_KP_6, KC_KP_7, KC_KP_8, LCTL(KC_LEFT), LCTL(KC_RIGHT)
  ),
  [FN] = LAYOUT(
      _______,
      KC_CYCLE_LAYERS, _______, _______, _______, _______,
      _______, _______, _______, _______, _______
  ),
  [MEDIA] = LAYOUT(
      KC_MEDIA_PLAY_PAUSE,
      KC_CYCLE_LAYERS, _______, _______, _______, _______,
      KC_MEDIA_PLAY_PAUSE, _______, _______, KC_VOLD, KC_VOLU
  ),
  [LIGHT] = LAYOUT(
      _______,
      KC_CYCLE_LAYERS, RGB_MOD, RGB_RMOD, _______, _______,
      RGB_TOG, _______, _______, RGB_VAD, RGB_VAI
  ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
  [FN] = { ENCODER_CCW_CW(LCTL(KC_LEFT), LCTL(KC_RIGHT)) },
  [MEDIA] = { ENCODER_CCW_CW(_______, _______) },
  [LIGHT] = { ENCODER_CCW_CW(_______, _______) }
};
#endif