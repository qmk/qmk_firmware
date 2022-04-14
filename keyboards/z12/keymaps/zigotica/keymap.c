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
#include "raw_hid.h"

#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t* data, uint8_t length) {
    layer_clear();
    if (data[0] == 99) {
        layer_on(_BASE);
    }
    else {
        layer_on(data[0]);
    }
}
#endif

// Custom Keycodes
#define MODE_1 TO(_BASE)
#define MODE_2 TO(_FIGMA)
#define MODE_3 TO(_BROWSER)
#define MODE_4 TO(_VIM)

enum custom_keycodes {
    VIM_SIF = SAFE_RANGE,
    VIM_SIP,
    VIM_RIF,
    VIM_RIP,
    VIM_NEW
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VIM_SIF:// Search in File
            if (record->event.pressed) {
                register_code(KC_ESC);
                tap_code(KC_SLASH);
            } else { // released
                unregister_code(KC_ESC);
            }
        break;
        case VIM_SIP:// Search in Project
            if (record->event.pressed) {
                register_code(KC_ESC);
                SEND_STRING(":Ag ");
            } else { // released
                unregister_code(KC_ESC);
            }
        break;
        case VIM_RIF:// Replace in File
            if (record->event.pressed) {
                register_code(KC_ESC);
                SEND_STRING(":%s/a/b/g");
            } else { // released
                unregister_code(KC_ESC);
            }
        break;
        case VIM_RIP:// Replace in Project
            if (record->event.pressed) {
                register_code(KC_ESC);
                SEND_STRING(":cdo %s/a/b/g");
            } else { // released
                unregister_code(KC_ESC);
            }
        break;
        case VIM_NEW:// New buffer
            if (record->event.pressed) {
                SEND_STRING("\e:vnew\n");
            } else { // released
                unregister_code(KC_ENT);
                unregister_code(KC_ESC);
            }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * BASE Layer
 *
 * ,-----------------------------.
 * |       | BASE | FIGM |       |
 * |-------+------+------+-------|
 * |VOL/PLY| BROW |  VIM | SCROLL|
 * |-------+------+------+-------|
 *    |-------+-------+-------|
 *    |   o   |   o   |   o   |
 *    |-------+-------+-------|
 *    |   o   |   o   |   o   |
 *    |-------+-------+-------|
 */
    [_BASE] = LAYOUT(
               MODE_1, MODE_2,
    ZK_MEDIA,  MODE_3, MODE_4,  _______,
    _______,      _______,      _______,
    _______,      _______,      _______
    ),
/*
 * FIGMA Layer
 *
 * ,-----------------------------.
 * |       | BASE | FIGM |       |
 * |-------+------+------+-------|
 * |  TABS | BROW |  VIM | ZOOM  |
 * |-------+------+------+-------|
 *    |-------+-------+-------|
 *    |ZOOMFIT| GRIDS |  FULL |
 *    |-------+-------+-------|
 *    |ZOOM100|  NEXT | COLOR |
 *    |-------+-------+-------|
 */
    [_FIGMA] = LAYOUT(
             _______, _______,
    _______, _______, _______,  _______,
    LSFT(KC_1), LCTL(KC_G), LGUI(KC_BSLS),
    LSFT(KC_0), KC_N,       LCTL(KC_C)
    ),
/*
 * BROWSER Layer
 *
 * ,-----------------------------.
 * |       | BASE | FIGM |       |
 * |-------+------+------+-------|
 * |  TABS | BROW |  VIM | SCROLL|
 * |-------+------+------+-------|
 *    |-------+-------+-------|
 *    |SEARCH | BOOKM | DEVTL |
 *    |-------+-------+-------|
 *    |ZOOM100| MUTE  | READ  |
 *    |-------+-------+-------|
 */
    [_BROWSER] = LAYOUT(
             _______, _______,
    _______, _______, _______,  _______,
    G(KC_F),   G(KC_D),   G(A(KC_I)),
    G(KC_0),   C(KC_M),   G(A(KC_R))
    ),
/*
 * VIM Layer
 *
 * ,-----------------------------.
 * |       | BASE | FIGM |       |
 * |-------+------+------+-------|
 * |BUFFER | BROW |  VIM | SCROLL|
 * |-------+------+------+-------|
 *    |-------+-------+-------|
 *    |SRCH FL|REPL FL|NEW BUF|
 *    |-------+-------+-------|
 *    |SRCH PR|REPL PR|   o   |
 *    |-------+-------+-------|
 */
    [_VIM] = LAYOUT(
             _______, _______,
    _______, _______, _______,  _______,
    VIM_SIF,      VIM_RIF,      VIM_NEW,
    VIM_SIP,      VIM_RIP,      _______
    ),
};
