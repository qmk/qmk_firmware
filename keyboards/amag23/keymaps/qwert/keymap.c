/* Copyright 2021
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    BASE,
    FN1
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_all( /* Base Layer */
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      MO(FN1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
      KC_LSFT, KC_Z,    KC_X,    KC_C,             KC_SPC
  ),
  [FN1] = LAYOUT_all( /* Function Layer */
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
      _______, RGB_TOG, RGB_VAI, RGB_MOD, RGB_HUI, _______,
      _______, _______, RGB_VAD, RGB_RMOD,RGB_HUD, _______,
      _______, _______, _______, _______,          _______
  ),
};
// clang-format on

