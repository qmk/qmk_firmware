/*
Copyright 2020 Jonathon Carstens jonathon@lizardtrick.com

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

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *
     *  Left    Middle  Right
     *  VolDn   PgDn    Alt+Tab    (Rotary Counterclockwise)
     *  VolUp   PgUp    Tab        (Rotary Clockwise)
     *  Mute    Play    Next       (Rotary Click)
     *
     *
     *
     *   ┌───┬───┬───┬───┐
     *   │TG1│ / │ * │ - │
     *   ├───┼───┼───┼───┤
     *   │ 7 │ 8 │ 9 │   │
     *   ├───┼───┼───┤ + │
     *   │ 4 │ 5 │ 6 │   │
     *   ├───┼───┼───┼───┤
     *   │ 1 │ 2 │ 3 │   │
     *   ├───┴───┼───┤Ent│
     *   │   0   │ . │   │
     *   └───────┴───┴───┘
     */

    [_BASE] = LAYOUT(
        KC_MUTE,    KC_MPLY,    KC_MNXT,
        KC_NUM,     KC_PSLS,    KC_PAST,    KC_PMNS,
        KC_P7,      KC_P8,      KC_P9,      KC_PPLS,
        KC_P4,      KC_P5,      KC_P6,
        KC_P1,      KC_P2,      KC_P3,      KC_PENT,
        KC_P0,                  KC_PDOT
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {           /* Left Encoder */
        if (clockwise) {
            tap_code16(KC_VOLU);
        } else {
            tap_code16(KC_VOLD);
        }
    } else if (index == 1) {    /* Middle Encoder */
        if (clockwise) {
            tap_code16(KC_PGDN);
        } else {
            tap_code16(KC_PGUP);
        }
    } else if (index == 2) {    /* Right Encoder */
        if (clockwise) {
            tap_code16(KC_TAB);
        } else {
            tap_code16(S(KC_TAB));
        }
    }
    return true;
}
