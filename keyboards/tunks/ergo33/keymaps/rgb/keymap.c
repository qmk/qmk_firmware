/* Copyright 2020 Mika Kuitunen 
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

enum layers {
    _BASE = 0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        UG_PREV,  UG_NEXT, UG_TOGG, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        UG_HUED,  UG_HUEU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        UG_SATD,  UG_SATU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        UG_VALD,  UG_VALU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS,                                                 KC_TRNS,
                                                KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
};
