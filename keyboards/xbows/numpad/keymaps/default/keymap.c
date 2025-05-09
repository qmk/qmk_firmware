/* Copyright 2021 Shulin Huang <mumu@x-bows.com>
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
  /* Keymap VANILLA: (Base Layer) Default Layer
   *
   * |-------------------------------|
   * |  Esc  |  Tab  |   BS  |   Fn  |
   * |-------------------------------|
   * |  NUM  |   /   |   *   |   =   |
   * |-------------------------------|
   * |   7   |  8    |   9   |   -   |
   * |-------------------------------|
   * |   4   |   5   |   6   |   +   |
   * |-------------------------------|
   * |   1   |  2   |    3   | ENTER |
   * |-------------------------------|
   * |        0     |    .   |
   * |-----------------------|
   */
  [0] = LAYOUT(
    KC_ESC ,  KC_TAB,   KC_BSPC,  MO(1),
    KC_NUM,   KC_PSLS,  KC_PAST,  KC_EQL,
    KC_P7,    KC_P8,    KC_P9,    KC_PMNS,
    KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
         KC_P0,       KC_PDOT),
  [1] = LAYOUT(
    QK_BOOT,   EE_CLR,    KC_TRNS,   KC_TRNS,
    KC_CALC,   KC_MYCM,   KC_MSEL,   KC_MAIL,
    RM_NEXT,   RM_VALU,   RM_HUEU,   KC_VOLD,
    RM_SPDD,   RM_TOGG,   RM_SPDU,   KC_VOLU,
    KC_TRNS,   RM_VALD,   KC_TRNS,   KC_TRNS,
        KC_TRNS,          KC_TRNS)
};
