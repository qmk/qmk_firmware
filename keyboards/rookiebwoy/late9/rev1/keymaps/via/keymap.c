/* Copyright 2021 rookiebwoy
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

// Layers declarations
enum layers {
    _BL,
    _OL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* BL: Base Layer
 * ,-----------------------.
 * |MO(OP) | ↑     | BSPC  |
 * |       |       |       |
 * |-------+-------+-------|
 * | <-    | ↓     | ->    |
 * |       |       |       |
 * |-------+-------+-------|
 * | 1     | 2     | 3     |
 * |       |       |       |
 * |-------+-------+-------|
 * | 4     | 5     | 6     |
 * |       |       |       |
 * |-------+-------+-------|
 * | 7     | 8     | 9     |
 * |       |       |       |
 * |-------+-------+-------|
 * | 0     | .     | =     |
 * |       |       |       |
 * `-----------------------'
 */
  [_BL] = LAYOUT(
    MO(1),         KC_UP,         KC_BSPC,
    KC_LEFT,       KC_DOWN,       KC_RIGHT,
    KC_P1,         KC_P2,         KC_P3,
    KC_P4,         KC_P5,         KC_P6,
    KC_P7,         KC_P8,         KC_P9,
    KC_P0,         KC_PDOT,       KC_PEQL
  ),

/* OP: Operators Layer
 * ,-----------------------.
 * |MO(OP) | ↑     | BSPC  |
 * |       |       |       |
 * |-------+-------+-------|
 * | <-    | ↓     | ->    |
 * |       |       |       |
 * |-------+-------+-------|
 * | /     | *     | -     |
 * |       |       |       |
 * |-------+-------+-------|
 * | (     | )     | +     |
 * |       |       |       |
 * |-------+-------+-------|
 * | &     | %     | ^     |
 * |       |       |       |
 * |-------+-------+-------|
 * | |     | .     | =     |
 * |       |       |       |
 * `-----------------------'
 */
  [_OL] = LAYOUT(
    MO(1),         KC_UP,         KC_BSPC,
    KC_LEFT,       KC_DOWN,       KC_RIGHT,
    KC_PSLS,       KC_PAST,       KC_PMNS,
    LSFT(KC_9),    LSFT(KC_0),    KC_PPLS,
    LSFT(KC_7),    LSFT(KC_5),    LSFT(KC_6),
    LSFT(KC_BSLS), KC_PDOT,       KC_PEQL
  ),
};