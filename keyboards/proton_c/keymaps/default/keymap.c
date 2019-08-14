/* Copyright 2018 Jack Humbert
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

/*                        ________
 *           ,-----------| usb-c  |-----------,
 *           |O 5v                     A9/TX O| J -
 *           |O GND                   A10/RX O| I -
 *           |O DFU                      GND O|
 *           |O 3.3v                     GND O|
 *       - Q |O A2                    SDA/B7 O| H -
 *       - P |O A1                    SCL/B6 O| G -
 *       - O |O A0                        B5 O| F -
 *       - N |O B8                        B4 O| E -
 *       - M |O B13/SCLK     C13/LED []   B3 O| D -
 *       - L |O B14/MISO                  B2 O| C -
 *       - K |O B15/MOSI                  B1 O| B -
 *           |O B9                        B0 O| A -
 *            =----==---============---==----=
 *       - Z |O B10                       A4 O|
 *       - Y |O B11                       A5 O|
 *       - X |O B12                       A6 O| U -
 *       - W |O B14/SWC                   A7 O| T -
 *       - V |O B13/SWD                   A8 O| S -
 *           |O RST                      A15 O| R -
 *           '--------------------------------'
 *
 * */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_board(
        //  B0,   B1,   B2,   B3,   B4,   B5,   B6,   B7,   A10,  A9,
            KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, \

          // B9,   B15,  B14,  B13,  B8,   A0,   A1,   A2,
             KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, \

          // Breakaway
          // A15,  A8,   A7,   A6,
             KC_S, KC_T, KC_U, KC_V, \

          // A13,   A14,  B12,  B11,  B10
             KC_W, KC_X, KC_Y, KC_Z, KC_SPACE ) \
};
