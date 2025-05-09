/* Copyright 2021 zhouqiong19840119
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
    [0] = LAYOUT_ortho_2x3(
        KC_P1, KC_P2, MO(1),
        KC_P3, KC_P4, KC_P3),
    [1] = LAYOUT_ortho_2x3(
        RM_TOGG, RM_NEXT, MO(1),
        AU_ON,   AU_OFF,  MI_ON),
    [2] = LAYOUT_ortho_2x3(
        KC_P4, KC_P5, MO(1),
        KC_P1, KC_P2, KC_P3),
};
