/* Copyright 2022 evan cook <evan@evancook.audio>
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
 * ,-----------------------------------------------.
 * |   1   |   2   |   3   |   4   |   5   |   -   |
 * |-------+-------+-------|-------|-------|-------|
 * |   6   |   7   |   8   |   9   |   0   |   R   |
 * |-------+-------+-------|-------|-------|-------|
 * |   /   |   Q   |   W   |   E   |   U   |   V   |
 *  -------+-------+-------|-------|-------|-------|
 * | ENTER |   A   |   S   |   D   | SPACE |   O   |
 * |       |-------+-------+-------|       |-------|
 * |       |   Z   |   X   |   C   |       |   N   |
 * ,-----------------------------------------------.
 */
[0] = LAYOUT(
  KC_1,       KC_2,      KC_3,      KC_4,      KC_5,      KC_MINS,
  KC_6,       KC_7,      KC_8,      KC_9,      KC_0,      KC_R,
  KC_SLSH,    KC_Q,      KC_W,      KC_E,      KC_U,      KC_V,
  KC_ENT,     KC_A,      KC_S,      KC_D,      KC_SPC,    KC_O,
              KC_Z,      KC_X,      KC_C,                 KC_N     
)
};
