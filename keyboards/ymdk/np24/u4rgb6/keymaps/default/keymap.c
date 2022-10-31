/* Copyright 2021 Simon Arlott
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

enum layer_names {
    L_NUM,
    L_BL,
    L_RGB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_NUM] = LAYOUT_ortho_6x4(
        KC_ESC,  KC_CALC, MO(L_BL),MO(L_RGB),
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_P0,   KC_PDOT, KC_PENT
    ),
    [L_BL] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, BL_ON,   _______, BL_INC,
        _______, BL_TOGG, _______, BL_INC,
        _______, BL_OFF,  _______, BL_DEC,
        BL_BRTG, _______, _______, BL_DEC
    ),
    [L_RGB] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, RGB_MOD, _______, RGB_VAI,
        _______, RGB_TOG, _______, RGB_VAI,
        _______, RGB_RMOD,_______, RGB_VAD,
        RGB_M_R, _______, _______, RGB_VAD
    )
};
