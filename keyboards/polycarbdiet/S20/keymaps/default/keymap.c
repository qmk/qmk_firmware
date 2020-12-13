/* Copyright 2020 Muhammad Galib <muhammadmgalib@gmail.com>
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
    //_BASE,
    //_FN
    _0,
    _1,
    _2
};

// Defines the keycodes used by our macros in process_record_user
/*
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NLCK, KC_PAST, KC_PSLS, KC_BSPC,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PMNS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_PDOT, MO(1)
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        KC_MPRV, KC_MPLY, KC_MNXT, _______,
        KC_VOLD, KC_MUTE, KC_VOLU, _______,
        _______, MO(2),   _______
    ),
    [2] = LAYOUT(
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______
    ),
};


/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}
*/
