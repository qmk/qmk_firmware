/* Copyright 2021 Dino Fizzotti 
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
#pragma once

#include "quantum.h"

#define LAYOUT_fn_row( \
    K000,       K001, K002, K003, K004,    K005, K006, K007, K008,    K009, K010, K011, K012 \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006, }, \
    { K007,  K008,  K009,  K010,  K011,  K012,  KC_NO }, \
}
