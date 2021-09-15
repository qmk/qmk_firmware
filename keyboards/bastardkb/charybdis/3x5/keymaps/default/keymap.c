/* 
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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
  [0]    = LAYOUT_split_3x5_3(
      KC_Q,             KC_W,             KC_E,             KC_R,             KC_T,                   KC_Y,             KC_U,               KC_I,         KC_O,         KC_P,  
      GUI_T(KC_A),      ALT_T(KC_S),      SFT_T(KC_D),      CTL_T(KC_F),      KC_G,                   KC_H,             CTL_T(KC_J),        SFT_T(KC_K),  ALT_T(KC_L),  GUI_T(KC_SCLN), 
      KC_Z,             KC_X,             KC_C,             KC_V,             KC_B,                   KC_N,             KC_M,               KC_COMM,      KC_DOT,       KC_SLSH,  
                                          KC_BSPC,          KC_ENT,           KC_TAB,                 KC_ESC,           KC_SPC,             U_NP

  )
};
