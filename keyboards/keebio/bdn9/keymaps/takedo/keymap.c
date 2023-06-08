/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Discord Mute | Discord Overlay  | Screenshot |
        | Medal Clip   |                  |            |
        | Volume Down  | Media Play/Pause | Volume Up  |
     */
    [0] = LAYOUT(
        KC_LALT,         S(RSFT(KC_GRV)),   S(LWIN(SWIN(KC_S))),
        KC_F10,          XXXXXXX,           XXXXXXX,
        KC_VOLD,         KC_MPLY,           KC_VOLU
    ),
};
