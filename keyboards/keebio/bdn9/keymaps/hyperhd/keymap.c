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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |                 | Knob 2: Page Dn/Up |
        | Press: Mute       | Toggle: Layer 1 | Press: Play/Pause  |
        | Toggle: Layer 2   | Up              | Toggle: Layer 3    |
        | Left              | Down            | Right              |
     */
    [0] = LAYOUT(
        KC_MUTE     , TG(1)  , KC_MPLY  ,
        C(S(KC_TAB)), KC_UP  , C(KC_TAB),
        KC_LEFT     , KC_DOWN, KC_RGHT
    ),
    /*
        | RESET          | N/A  | Media Stop      |
        | Held: Layer 2  | Max  | Toggle: Layer 0 |
        | Desk Previous  | Min  | Desk Next       |
     */
    [1] = LAYOUT(
        XXXXXXX      , TG(1)        , KC_STOP      ,
        MO(2)        , C(G(KC_PGUP)), KC_F5        ,
        C(G(KC_LEFT)), C(G(KC_PGDN)), C(G(KC_RGHT))
    ),
    [2] = LAYOUT(
        RESET        , XXXXXXX      , XXXXXXX      ,
        XXXXXXX      , XXXXXXX      , XXXXXXX      ,
        XXXXXXX      , XXXXXXX      , XXXXXXX      
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGUP);
        } else {
            tap_code(KC_PGDN);
        }
    }
}
