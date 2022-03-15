/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#include "makeymakey.h"

pin_t pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;

void keyboard_post_init_kb(void) {
    for(uint8_t row = 0; row < MATRIX_ROWS; row++)
    {
        for(uint8_t col = 0; col < MATRIX_COLS; col++)
        {
            writePinLow(pins[row][col]); //Disable internal pull-up resistors
        }
    }

    keyboard_post_init_user();
}
