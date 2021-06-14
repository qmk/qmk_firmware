/* Copyright 2020 Tom Swartz
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
#define LAYOUT( \
   K05,  K15,  K25,  K35,  K45,  \
   K04,  K14,  K24,  K34,        \
   K03,  K13,  K23,  K33,  K43,  \
   K02,  K12,  K22,  K32,        \
   K01,  K11,  K21,  K31,  K41   \
) \
{ \
 { K05,  K15,  K25,  K35,  K45 }, \
 { K04,  K14,  K24,  K34       }, \
 { K03,  K13,  K23,  K33,  K43 }, \
 { K02,  K12,  K22,  K32       }, \
 { K01,  K11,  K21,  K31,  K41 }  \
}
