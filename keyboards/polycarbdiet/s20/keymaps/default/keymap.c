/* Copyright 2020 Muhammad Galib (polycarbdiet) <pd.keyboards@gmail.com>
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
    [0] = LAYOUT_ortho_5x4(
        KC_ESC,  KC_PAST, KC_PSLS, KC_BSPC,
        KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_PDOT, MO(1),   UG_TOGG
    ),
    [1] = LAYOUT_ortho_5x4(
        KC_NUM,  KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS,
        KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS,
        QK_BOOT, MO(2),   KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_ortho_5x4(
        UG_TOGG, UG_HUEU, UG_SATU, UG_VALU,
        UG_NEXT, UG_HUED, UG_SATD, UG_VALD,
        BL_TOGG, BL_ON,   BL_UP,   BL_STEP,
        KC_TRNS, BL_OFF,  BL_DOWN, BL_BRTG,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_ortho_5x4(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
