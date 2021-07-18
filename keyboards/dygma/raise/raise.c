/* Copyright 2018-2021 James Laird-Wah, Islam Sharabash
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "i2c_master.h"
#include <string.h>
#include "raise.h"

void matrix_init_kb(void) {
    set_all_leds_to(0, 0, 0);
    matrix_init_user();
}

void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_user(void) {}
