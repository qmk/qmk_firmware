/*
Copyright 2020 Alabahuy

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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_5x4(
        KC_NLCK, KC_PSLS, KC_PAST, KC_INS,
        KC_P7,   KC_P8,   KC_P9,   KC_PEQL,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        MO(1),   KC_P0,   KC_PDOT, KC_PENT
    ),

    [1] = LAYOUT_ortho_5x4(
        KC_TRNS, RGB_HUI, RGB_HUD,  KC_TRNS,
        RGB_SAI, RGB_SAD, KC_MNXT,  KC_MPRV,
        RGB_VAI, RGB_VAD, KC_MSTP,  KC_MPLY,
        KC_COPY, KC_PSTE, KC_MYCM,  KC_CALC,
        KC_TRNS, RGB_TOG, QK_BOOT,    KC_TRNS
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
    return true;
}
