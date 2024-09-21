/* Copyright 2021 FREE WING,Y.Sakamoto
 * http://www.neko.ne.jp/~freewing/
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
    _BASE
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMK00 = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_NUM,
        KC_TAB, KC_PSLS, KC_PAST, KC_BSPC,
        KC_P7,  KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,  KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,  KC_P2,   KC_P3,   KC_PENT,
        KC_P0,  QMK00,   KC_PDOT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMK00:
            if (record->event.pressed) {
                // when keycode QMK00 is pressed
                SEND_STRING(SS_TAP(X_KP_0) SS_TAP(X_KP_0));
            } else {
                // when keycode QMK00 is released
            }
            break;
    }
    return true;
}
