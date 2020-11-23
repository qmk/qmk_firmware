/*

QMK Firmware for dekuNukem/duckyPad

Copyright (C) 2020 Anthony Som

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "duckypad.h"

led_config_t g_led_config = { {
    { 2, 1, 0, 3, 4, 5, 8, 7, 6, 9, 10, 11, 14, 13, 12, NO_LED, NO_LED }
}, {
    {224, 0},
    {112, 0},
    {0, 0},
    {0, 16},
    {112, 16},
    {224, 16},
    {224, 32},
    {112, 32},
    {0, 32},
    {0, 48},
    {112, 48},
    {224, 48},
    {224, 64},
    {112, 64},
    {0, 64},
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
} };

void keyboard_pre_init_kb(void) {
    setPinOutput(A0);
    writePinHigh(A0);
    writePinLow(A0);
    wait_ms(10);
    writePinHigh(A0);

    keyboard_pre_init_user();
}
