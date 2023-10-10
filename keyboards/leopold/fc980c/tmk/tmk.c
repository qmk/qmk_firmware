/*
Copyright 2017 Balz Guenat

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "tmk.h"

#include "../fc980c.h"

void matrix_init_kb(void) {
    fc980c_matrix_init_kb();

    matrix_init_user();
}

void eeconfig_init_kb(void) {
    fc980c_eeconfig_init_kb();

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    fc980c_keyboard_post_init_kb();

    keyboard_post_init_user();
}
