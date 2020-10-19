 /* Copyright HarshitGoel96 2020
  * With permission form jpconstantineau, the original maintainer of the Ergo Travel hardware.
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


enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  //,--------+--------+--------+--------+--------+--------+--------.        ,--------+--------+--------+--------+--------+--------+--------.
     KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS,          KC_EQL, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,          KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,           KC_SPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  //|--------+--------+--------+--------+--------+--------+--------|        |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_LGUI, KC_LALT, _______,           _______,   KC_SPC,           KC_SPC,  _______,            KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
  //`--------+--------+--------+--------+--------+--------+--------/        \--------+--------+--------+--------+--------+--------+--------'
  ),

  [_LOWER] = LAYOUT(
  _______,  _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______,           _______, _______,         _______,  _______,          _______, _______, _______, _______

  ),

  [_RAISE] = LAYOUT(
 
_______,  _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______,           _______, _______,         _______,  _______,          _______, _______, _______, _______
  
  ),

  [_ADJUST] = LAYOUT(
     _______,  _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______,  _______, _______, _______, _______, _______,         _______,  _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______,           _______, _______,         _______,  _______,          _______, _______, _______, _______
  )

};

