/* Copyright 2021 Rodrigo Chandia <rodrigo.chandia@gmail.com>
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
#include "regelatworktrackball.h"

enum layer_names {
    _MOUSE,
    _CNFIG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MOUSE] = LAYOUT(
      XXXXXXX,    XXXXXXX,      MO(_CNFIG),
      XXXXXXX,    KC_WH_SHIFT,  XXXXXXX,
      KC_MS_BTN1, KC_MS_BTN3,   KC_MS_BTN2
  ),
  [_CNFIG] = LAYOUT(
      _______, _______, _______,
      RGB_HUI, RGB_MOD, RGB_VAI,
      _______, _______, RGB_VAD
  )
};

