/* Copyright 2021 mtei
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

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
     /* If none of the keys are pressed,
      *  there is no need to wait for time for the next line. */
     if (key_pressed) {
#    ifdef MATRIX_IO_DELAY
#        if MATRIX_IO_DELAY > 0
         wait_us(MATRIX_IO_DELAY);
#        endif
#    else
         wait_us(30);
#    endif
     }
}
