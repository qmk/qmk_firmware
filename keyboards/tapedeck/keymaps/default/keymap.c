/* Copyright 2023 Gowla
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
#include "print.h"

#define BASE 0 

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_ESC,            KC_MNXT,           KC_MPLY,     KC_MNXT, KC_MPLY,
        RGB_MODE_RAINBOW,  RGB_MODE_RGBTEST,  RGB_M_K,     RGB_TOG, KC_MPLY,
        KC_F1,             KC_F2,             KC_F3,       KC_F14
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE] = { ENCODER_CCW_CW(KC_WH_D, KC_WH_U), ENCODER_CCW_CW(KC_BRID, KC_BRIU) }
};
#endif




