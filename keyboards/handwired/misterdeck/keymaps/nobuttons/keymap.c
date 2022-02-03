/* Copyright 2021 Chris Broekema (broekema@gmail.com)
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
#include "joystick.h"

enum layers {
  NORMAL_LAYER = 0
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [NORMAL_LAYER] = LAYOUT( C(S(KC_F1)), C(S(KC_F2)), C(S(KC_F3)), C(S(KC_F4)),
			   C(S(KC_F5)), C(S(KC_F6)), C(S(KC_F7)), C(S(KC_F8)),
			   C(S(KC_F9)), C(S(KC_F10)), C(S(KC_F11)), C(S(KC_F12))),
};



joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
    [0] = JOYSTICK_AXIS_IN(F4, 0, 512, 1023),
    [1] = JOYSTICK_AXIS_IN(F5, 0, 512, 1023),
    [2] = JOYSTICK_AXIS_IN(F6, 0, 512, 1023),
    [3] = JOYSTICK_AXIS_IN(F7, 0, 512, 1023)
};
