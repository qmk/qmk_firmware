/*
Copyright 2022 <dennis@kruyt.org>

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

enum Layer {
    _NUMPAD = 0,      // Standard QWERTY layer
    _MOUSE,           // Function key layer
    _RGB,             // RGB
};
#define _NP _NUMPAD
#define _MS _MOUSE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * ,-------------------.
   * | Fx | Fx | Fx | Fx |
   * |----|----|----|----|
   * | NL | /  | *  | -  |
   * |----|----|----|----|
   * | 7  | 8  | 9  |    |
   * |----|----|----| +  |
   * | 4  | 5  | 6  |    |
   * |----|----|----|----|
   * | 1  | 2  | 3  |    |
   * |----|----|----| En |
   * |    0    | .  |    |
   * `-------------------'
   */

  [_NUMPAD] = LAYOUT_numpad_6x4(
    TO(_MS), RGB_TOG, RGB_MODE_FORWARD, KC_VOLU,
    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, 
    KC_P7,   KC_P8,   KC_P9,   
    KC_P4,   KC_P5,   KC_P6,   KC_PPLS, 
    KC_P1,   KC_P2,   KC_P3,   
    KC_P0, KC_PDOT,  KC_PENT  
  ),

  [_MOUSE] = LAYOUT_numpad_6x4(
    TO(_RGB), RGB_TOG, RGB_MODE_FORWARD, KC_VOLU,
    _______, KC_BTN1, KC_BTN2, KC_BTN3, 
    _______,   KC_MS_U,   _______,   
    KC_MS_L,   KC_P5,   KC_MS_R,   _______, 
    _______,   KC_MS_D,   _______,   
    _______, _______,  _______
  ),

  [_RGB] = LAYOUT_numpad_6x4(
    TO(_NP), RGB_TOG, RGB_MODE_FORWARD, _______,
    _______, _______, _______, _______, 
    RGB_HUI,   RGB_VAI,   RGB_HUD	,   
    RGB_SAD,   _______,   RGB_SAI,   _______, 
    _______,   RGB_VAD,   _______,   
    _______, _______,  _______
  ),
};