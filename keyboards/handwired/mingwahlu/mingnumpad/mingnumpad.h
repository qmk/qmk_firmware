/* Copyright 2020 mingwahlu
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define ___ KC_NO


#define LAYOUT_numpad_6x4( \
    k00, k01, k02, K03,\
    k10, k11, K12, K13,\
    K20, K21, K22,     \
    K30, K31, K32, K33,\
    K40, K41, K42,     \
    K50,      K52, K53  \
) { \
    { k00, k01, k02, K03 }, \
    { k10, k11, K12, K13 }, \
    { K20, K21, K22, ___ }, \
    { K30, K31, K32, K33 }, \
    { K40, K41, K42, ___ }, \
    { K50, ___, K52, K53 }  \
}
