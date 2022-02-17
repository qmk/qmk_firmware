/* Copyright 2020
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
#include "sixpack.h"

void matrix_init_kb(void) {
    setPinOutput(B6);  // Backlight cathodes Col.3
    setPinOutput(F6);  // Backlight cathodes Col.2
    setPinOutput(F7);  // Backlight cathodes Col.1

    matrix_init_user();
}
