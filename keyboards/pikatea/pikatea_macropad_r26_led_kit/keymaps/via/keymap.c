/* Copyright 2022 Jack Kester
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

#define LAYOUT_via( \
    k00, k01, k02, k03, k04, \
    k10, k11,      k13, k14, \
    E00A, E00B \
) \
{ \
    { k00, k01, k02, k03, k04, k10, k11, k13, k14, E00A, E00B} \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_via(
        KC_F15,  KC_MEDIA_PREV_TRACK,   KC_MUTE,    KC_MEDIA_NEXT_TRACK,    KC_MEDIA_PLAY_PAUSE,
        KC_F20,  KC_F21,              KC_F22,    KC_F23,
        KC_VOLD, KC_VOLU
    ),
    [1] = LAYOUT_via(
        _______,  _______,   _______,    _______,    _______,
        _______,  _______,              _______,    _______,
        _______, _______
    ),
    [2] = LAYOUT_via(
        _______,  _______,   _______,    _______,    _______,
        _______,  _______,              _______,    _______,
        _______, _______
    ),
    [3] = LAYOUT_via(
        _______,  _______,   _______,    _______,    _______,
        _______,  _______,              _______,    _______,
        _______, _______
    )
};

