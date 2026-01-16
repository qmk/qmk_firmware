/* Copyright 2019 joaofbmaia
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
  
  /* LAYER 0
  * ,-----------------------.
  * |  F13  |  F14  | F15/FN|  Hold for FN
  * |-------+-------+-------|
  * |  F16  |  F17  |  F18  |
  * `-------+-------+-------'
  */
  [0] = LAYOUT(
    KC_F13, KC_F14, LT(1, KC_F15),
    KC_F16, KC_F17, KC_F18
  ),

  /* LAYER 1
  * ,-----------------------.
  * |UG_TOGG|RGBMOD+|       |
  * |-------+-------+-------|
  * |RGBHUE+|RGBBRI+|Spec FN|   Hold along with previous to access special funtions (QK_BOOT)
  * `-------+-------+-------'
  */
  [1] = LAYOUT(
    UG_TOGG, UG_NEXT, KC_TRNS,
    UG_HUEU, UG_VALU, MO(2)
  ),

  /* LAYER 2
  * ,-----------------------.
  * | QK_BOOT |RGBMOD-|       |
  * |-------+-------+-------|
  * |RGBHUE-|RGBBRI-|       |
  * `-------+-------+-------'
  */
  [2] = LAYOUT(
    QK_BOOT, UG_PREV, KC_NO,
    UG_HUED, UG_VALD, KC_TRNS
  )
  
};
