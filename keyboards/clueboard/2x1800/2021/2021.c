/* Copyright 2017 Zach White <skullydazed@gmail.com>
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

/* Portions of this file are based on LEDControl by Eberhard Fahle. You can
 * find the original code here: <https://github.com/wayoda/LedControl>
 *
 * The license for that code follows.
 *
 *    LedControl.h - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 *
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 *
 *    This permission notice shall be included in all copies or
 *    substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */
#include "2021.h"
#include "max7219.h"

void matrix_init_kb(void) {
    max7219_init();
    max7219_set_led(0, 0, true);
}

__attribute__ ((weak))
bool encoder_update_keymap(int8_t index, bool clockwise) {
    return false;
}

#define NUM_COLUMNS 8*MAX7219_CONTROLLERS
uint8_t led_position[2] = {0,0};  // The location of the cursor in the matrix

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_keymap(index, clockwise)) {
        // Encoder 1, left
        if (index == 0 && clockwise) {
            if (led_position[0] < NUM_COLUMNS-1) {  // turned right
                led_position[0]++;
            } else {
                led_position[0]=0;
            }
        } else if (index == 0) {
            if (led_position[0] > 0) {  // turned left
                led_position[0]--;
            } else {
                led_position[0]=NUM_COLUMNS-1;
            }
        }

        // Encoder 2, right
        else if (index == 1 && clockwise) {
            if (led_position[1] < 7) {  // turned right
                led_position[1]++;
            } else {
                led_position[1]=0;
            }
        } else if (index == 1) {
            if (led_position[1] > 0) {  // turned left
                led_position[1]--;
            } else {
                led_position[1]=7;
            }
        }

        max7219_set_led(led_position[1], led_position[0], true);
    }
    return true;  // FIXME: check which I should return
}
