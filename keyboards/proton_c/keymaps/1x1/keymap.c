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
 *           |O 5v       |________|    A9/TX O|
 *           |O GND                   A10/RX O|
 *           |O DFU                      GND O|
 *           |O 3.3v                     GND O|
 *           |O A2                    SDA/B7 O|
 *           |O A1                    SCL/B6 O|
 *           |O A0                        B5 O|
 *           |O B8                        B4 O|
 *           |O B13/SCLK     C13/LED []   B3 O|
 *           |O B14/MISO                  B2 O|
 *           |O B15/MOSI                  B1 O|
 *           |O B9                        B0 O|  A -
 *            =----==---============---==----=
 *           |O B10                       A4 O|
 *           |O B11                       A5 O|
 *           |O B12                       A6 O|
 *           |O B14/SWC                   A7 O|
 *           |O B13/SWD                   A8 O|
 *           |O RST                      A15 O|
 *           '--------------------------------'
 *
 *           ,--------------,
 *           | B0 | B1 | B2 |
 *           '--------------'
 * */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
                  //   B0,
    [0] = LAYOUT_1x1( KC_A )
};

