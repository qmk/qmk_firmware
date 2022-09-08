/* Copyright 2020 gregorio
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
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
                                       ENC_PRESS,
            KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
            KC_P7  , KC_P8  , KC_P9  , KC_PPLS,
            KC_P4  , KC_P5  , KC_P6  ,
            KC_P1  , KC_P2  , KC_P3  , KC_PENT,
                     KC_P0  , LT(2, KC_PDOT)
            ),
    [1] = LAYOUT(
                                       KC_TRNS,
            KC_C   , KC_SLSH, CL_STAR, KC_MINS,
            KC_7   , KC_8   , KC_9   , CL_PLUS,
            KC_4   , KC_5   , KC_6   ,
            KC_1   , KC_2   , KC_3   , KC_EQL,
                     KC_0   , KC_DOT
            ),
    [2] = LAYOUT(
                                       KC_TRNS,
            KC_TRNS, KC_N   , KC_S   , KC_R   ,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                     KC_TRNS, KC_TRNS
            ),
    [3] = LAYOUT(
                                       KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, QK_BOOT  , KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                     KC_TRNS, KC_TRNS
            ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (get_highest_layer(layer_state) == 0) {
            uint16_t mapped_code = 0;
            if (clockwise) {
                mapped_code = handle_encoder_cw();
            } else {
                mapped_code = handle_encoder_ccw();
            }
            if (mapped_code != 0) {
                tap_code16(mapped_code);
            }
        } else {
            if (clockwise) {
                if (oled_mode == OLED_MODE_CALC) {
                    handle_encoder_cw();
                } else if (oled_mode == OLED_MODE_DEFAULT) {
                    change_encoder_mode(false);
                }
            } else {
                if (oled_mode == OLED_MODE_CALC) {
                    handle_encoder_ccw();
                } else if (oled_mode == OLED_MODE_DEFAULT) {
                    change_encoder_mode(true);
                }
            }
        }
    }
    return true;
}
