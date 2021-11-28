/* Copyright 2020
   Sergi Meseguer <zigotica@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "zigotica.h"

// Custom Keycodes
#define MODE_1 TO(_TERMINAL)
#define MODE_2 TO(_FIGMA)
#define MODE_3 TO(_BROWSER)
#define MODE_4 TO(_VIM)

enum custom_keycodes {
    VIM_SIP = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VIM_SIP:
            if (record->event.pressed) {
                register_code(KC_ESC);
                SEND_STRING(":Ag ");
            } else {
                // released
                unregister_code(KC_ESC);
            }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * TERMINAL Layer
 *
 * ,-----------------------------.
 * |       | TERM | FIGM |       |
 * |-------+------+------+-------|
 * |  VOL  | BROW |  VIM | SCROLL|
 * |-------+------+------+-------|
 *    |-------+-------+-------|
 *    | MEDIA |   o   |   o   |
 *    |-------+-------+-------|
 *    |   o   |   o   |   o   |
 *    |-------+-------+-------|
 */
    [_TERMINAL] = LAYOUT(
               MODE_1, MODE_2,
    ZK_MEDIA,  MODE_3, MODE_4,  _______,
    _______,      _______,      _______,
    _______,      _______,      _______
    ),
/*
 * VIM Layer
 *
 * ,-----------------------------.
 * |       | TERM | FIGM |       |
 * |-------+------+------+-------|
 * |BUFFER | BROW |  VIM | SCROLL|
 * |-------+------+------+-------|
 *    |-------+-------+-------|
 *    |SEARCH |   o   |   o   |
 *    |-------+-------+-------|
 *    |   o   |   o   |   o   |
 *    |-------+-------+-------|
 */
    [_VIM] = LAYOUT(
             _______, _______,
    _______, _______, _______,  _______,
    VIM_SIP,      _______,      _______,
    _______,      _______,      _______
    ),
/*
 * FIGMA Layer
 *
 * ,-----------------------------.
 * |       | TERM | FIGM |       |
 * |-------+------+------+-------|
 * |  VOL  | BROW |  VIM | ZOOM  |
 * |-------+------+------+-------|
 *    |-------+-------+-------|
 *    | ZOOM  | GRIDS |  FULL |
 *    |-------+-------+-------|
 *    |   o   |   o   |   o   |
 *    |-------+-------+-------|
 */
    [_FIGMA] = LAYOUT(
             _______, _______,
    _______, _______, _______,  _______,
    LSFT(KC_1), LCTL(KC_G), LGUI(KC_BSLS),
    _______,      _______,      _______
    ),
/*
 * BROWSER Layer
 *
 * ,-----------------------------.
 * |       | TERM | FIGM |       |
 * |-------+------+------+-------|
 * |  TABS | BROW |  VIM | SCROLL|
 * |-------+------+------+-------|
 *    |-------+-------+-------|
 *    |SEARCH | BOOKM | DEVTL |
 *    |-------+-------+-------|
 *    |   o   |   o   |   o   |
 *    |-------+-------+-------|
 */
    [_BROWSER] = LAYOUT(
             _______, _______,
    _______, _______, _______,  _______,
    G(KC_F),      G(KC_D),   G(A(KC_I)),
    _______,      _______,      _______
    ),
};
