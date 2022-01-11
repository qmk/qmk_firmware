/* Copyright 2021 Alan Pocklington
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

enum ajp10304_layers {
  _QWERTY,
  _COLEMAK,
  _MAC,
  _LOWER,
  _MLWR,
  _RAISE,
  _MRSE,
  _FUNC,
  _MFNC,
  _FUNC2,
  _MFNC2,
  _ADJUST,
  _MOUSE,
  _NUMPAD
};

enum ajp10304_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  MAC,
  FUNC,
  MFNC,
  FUNC2,
  MFNC2,
  LOWER,
  MLWR,
  RAISE,
  MRSE,
  MOUSE,
  NUMPAD,
  M_CUSTOM,
  M_WORD_SEL,
  M_WORD_SEL_MAC,
  M_LINE_SEL,
  M_LINE_SEL_MAC,
  M_LINE_DEL,
  M_LINE_DEL_MAC,
  M_DUP,
  M_DUP_MAC,
  M_JOIN,
  M_JOIN_MAC,
  M_MODE,
  M_MODE_MAC
};
