// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

 /* This program is free software: you can redistribute it and/or modify
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

/* Layer Setup +for kodeboard<bukil@2024>*/
#define _DL 0
#define _FL 1
#define _CL 2
#define _ML 3

/*ENCODER_DEFINE AND OP*/

#define ENCODERS_PAD_A { GP3}
#define ENCODERS_PAD_B { GP4}

/*ENCODER FUNCTION FOR LYR*/



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* setup
     * ┌───┬───┬───┬─────────┐
     * │ 7 │ 8 │ 9 │ /       │
     * ├───┼───┼───┼─────────┤
     * │ 4 │ 5 │ 6 │ *       │
     * ├───┼───┼───┼─────────┤
     * │ 1 │ 2 │ 3 │ -       │
     * ├───┼───┼───┼─────────┤
     * │ 0 │ . │Ent│ LAYER   │
     * └───┴───┴───┴─────────┘
     */
    [_DL] = LAYOUT_K0DEPAD(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, MO(_FL)
    ),
	[_FL] = LAYOUT_K0DEPAD(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, MO(_CL)
    ),
	[_CL] = LAYOUT_K0DEPAD(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, MO(_ML)
    ),
	[_ML] = LAYOUT_K0DEPAD(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, MO(_DL)
    ),
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] = {ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [2] = {ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    [3] = {ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif