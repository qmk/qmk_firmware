/* Copyright 2020 Tom Swartz
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _NP,
    _FN
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KC_00 = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* NumberPad Layer
    ,---------------------------------------.
    | Back  | Num   | /     | *     | -     |
    | Space | Lock  |       |       |       |
    |-------+-------+-------+-------+-------|
    | Tab   | 7     | 8     | 9     | +     |
    |       | Home  | Up    | PgUp  |       |
    |-------+-------+-------+-------|       |
    | Layer | 4     | 5     | 6     |       |
    | Toggle| Left  |       | Right |       |
    |-------+-------+-------+-------+-------|
    | Page  | 1     | 2     | 3     | Enter |
    | Up    | End   | Down  | PgDn  |       |
    |-------+-------+-------+-------|       |
    | Page  | 00    | 0     | .     |       |
    | Down  |       |       |       |       |
    `---------------------------------------'
*/
    [_NP] = LAYOUT(
        KC_BSPC,   KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,    KC_7,    KC_8,   KC_9,
        TG(_NP),   KC_4,    KC_5,   KC_6,    KC_PPLS,
        KC_PGUP,   KC_1,    KC_2,   KC_3,
        KC_PGDOWN, KC_00,   KC_0,   KC_PDOT, KC_PENT
    ),
/* Macropad/Function Layer
    ,---------------------------------------.
    | `~    | Play  | F13   | Prev  | Next  |
    |       | Pause |       |       |       |
    |-------+-------+-------+-------+-------|
    | Tab   | F14   | F15   | 9     | +     |
    |       |       |       | PgUp  |       |
    |-------+-------+-------+-------|       |
    | Layer | 4     | 5     | 6     |       |
    | Toggle| Left  |       | Right |       |
    |-------+-------+-------+-------+-------|
    | U     | B     | 2     | 3     | Enter |
    |       |       | Down  | PgDn  |       |
    |-------+-------+-------+-------|       |
    | D     | F     | 0     | .     |       |
    |       |       |       |       |       |
    `---------------------------------------'
*/
    [_FN] = LAYOUT(
        KC_GRV,  KC_MPLY, KC_F13,  KC_MPRV, KC_MNXT,
        _______, KC_F14,  KC_F15,  _______,
        _______, _______, _______, _______, _______,
        KC_U,    KC_B,    _______, _______,
        KC_D,    KC_F,    _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_00:
            if (record->event.pressed) {
                // when keycode DOUBLEZERO is pressed
                SEND_STRING("00");
            }
            break;
    }
    return true;
}
