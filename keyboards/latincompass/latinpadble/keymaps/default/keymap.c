 /* Copyright 2021 haierwangwei2005
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
        KC_PGUP,
        KC_KP_7, KC_KP_8, KC_KP_9, MO(1),
        KC_P4, KC_P5, KC_P6, KC_KP_PLUS,
        KC_P1, KC_P2, KC_P3, KC_KP_MINUS,
        KC_P0, KC_PDOT,KC_DELETE, KC_KP_ENTER
    ),
    [1] = LAYOUT(
        KC_NUM,
		RGB_TOG, RGB_MOD, RGB_M_K, RGB_M_X,
        RGB_SAI, RGB_SAD, RGB_HUI, RGB_HUD,
        RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD,
        RGB_SPI, RGB_SPD, RGB_TOG, KC_TRNS
    )
};
