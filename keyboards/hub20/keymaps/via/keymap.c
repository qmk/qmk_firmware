/* Copyright 2020 joshajohnson
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

#define MO_NLCK LT(1, KC_NUM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
                 KC_MUTE,  KC_MPLY,
       KC_PMNS,  KC_PAST,  KC_PSLS,    MO_NLCK,
       KC_PPLS,    KC_P7,    KC_P8,      KC_P9,
       KC_PPLS,    KC_P4,    KC_P5,      KC_P6,
       KC_PENT,    KC_P1,    KC_P2,      KC_P3,
       KC_PENT,  KC_PDOT,    KC_P0,      KC_P0
),
    [1] = LAYOUT_all(
                   QK_BOOT,  _______,
       RGB_TOG,  RGB_RMOD, RGB_MOD,    _______,
       _______,  RGB_VAD,  RGB_VAI,    _______,
       _______,  RGB_HUD,  RGB_HUI,    _______,
       _______,  RGB_SAD,  RGB_SAI,    _______,
       _______,  _______,  _______,    _______
),
    [2] = LAYOUT_all(
                 _______,  _______,
       _______,  _______,  _______,    _______,
       _______,  _______,  _______,    _______,
       _______,  _______,  _______,    _______,
       _______,  _______,  _______,    _______,
       _______,  _______,  _______,    _______
),
    [3] = LAYOUT_all(
                 _______,  _______,
       _______,  _______,  _______,    _______,
       _______,  _______,  _______,    _______,
       _______,  _______,  _______,    _______,
       _______,  _______,  _______,    _______,
       _______,  _______,  _______,    _______
)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left Encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* Right Encoder */
        if (clockwise) {
            tap_code(KC_MNXT);
        } else {
            tap_code(KC_MPRV);
        }
    }
    return true;
}
