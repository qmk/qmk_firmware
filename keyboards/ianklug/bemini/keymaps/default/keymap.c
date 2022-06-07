/* Copyright 2022 Ian Klug
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

// how long (ms) to hold buttons tapped by the encoder
#define TAP_CODE_DELAY 10

//      bemini v1 key layout, player 1 configuration
//      .-----------------------------------------------------------------------------------------.
//      |                                                                                         |
//      |                                    .-------.-------.-------.-------.        .-------.   |
//      |                                    |       |       |       |       |        |       |   |
//      |                                    |       |       |       |       |        |  K12  |   |
//      |                                    |  K02  |  K04  |  K06  |  K08  |        |       |   |
//      |            .-------.               |       |       |       |       |        +-------+   |
//      |            |       |               |       |       |       |       |        |       |   |
//      |            |K13/ENC|           .---+---+---+---+---+---+---+---+---+---.    |  K11  |   |
//      |            |       |           |       |       |       |       |       |    |       |   |
//      |            '-------'           |       |       |       |       |       |    +-------+   |
//      |                                |  K01  |  K03  |  K05  |  K07  |  K09  |    |       |   |
//      |                                |       |       |       |       |       |    |  K10  |   |
//      |                                |       |       |       |       |       |    |       |   |
//      |                                '-------'-------'-------'-------'-------'    '-------'   |
//      |                                                                                         |
//      '-----------------------------------------------------------------------------------------'

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
//	K01      K02      K03      K04      K05      K06      K07      K08      K09      K10      K11      K12      K13
	KC_Z,    KC_S,    KC_X,    KC_D,    KC_C,    KC_F,    KC_V,    KC_T,    KC_G,    KC_ENT,  KC_1,    KC_TAB,  KC_LSFT
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_LSFT);
        } else {
            tap_code(KC_LCTL);
        }
    }
    return true;
}
