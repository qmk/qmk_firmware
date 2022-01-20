/* Copyright 2019 T.Shinohara
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

enum layer_number {
  _NUMBER = 0,
  _CURSOL,
  _MOUSE
};

#define NUMBER TO(_NUMBER)
#define CURSOL TO(_CURSOL)
#define MOUSE  TO(_MOUSE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NUMBER] = LAYOUT(
    NUMBER,   CURSOL,   MOUSE,
    KC_P7,    KC_P8,    KC_P9,
    KC_P4,    KC_P5,    KC_P6,
    KC_P1,    KC_P2,    KC_P3,
    KC_P0,    KC_BSPC,  KC_ENT
  ),
  [_CURSOL] = LAYOUT(
    NUMBER,   CURSOL,   MOUSE,
    KC_HOME,  KC_UP,    KC_PGUP,
    KC_LEFT,  KC_ESC,   KC_RIGHT,
    KC_END,   KC_DOWN,  KC_PGDN,
    KC_DEL,   KC_BSPC,  KC_ENT
  ),
  [_MOUSE] = LAYOUT(
    NUMBER,   CURSOL,   MOUSE,
    LGUI(KC_X),   LGUI(KC_C),  LGUI(KC_V),
    LGUI(KC_Z),  LGUI(KC_F),  KC_AGIN,
    XXXXXXX,  XXXXXXX,  XXXXXXX,
    KC_DEL,   KC_BSPC,  KC_ENT
  ),
};
