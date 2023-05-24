/* Copyright 2021 drhigsby
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

#include "ogurec.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT_ortho_3x12( \
    k011, k010, k009, k008, k007, k006, k005, k004, k003, k002, k001, k000, \
    k111, k110, k109, k108, k107, k106, k105, k104, k103, k102, k101, k100,  \
    k211, k210, k209, k208, k207, k206, k205, k204, k203, k202, k201, k200    \
) \
{ \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011 }, \
    { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111 },  \
    { k200, k201, k202, k203, k204, k205, k206, k207, k208, k209, k210, k211 }    \
}

#define LAYOUT_ortho_3x12_1x2uC( \
    k011, k010, k009, k008, k007, k006, k005, k004, k003, k002, k001, k000, \
    k111, k110, k109, k108, k107, k106, k105, k104, k103, k102, k101, k100,  \
    k211, k210, k209, k208, k207,    k205,    k204, k203, k202, k201, k200    \
) \
{ \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, k010, k011 }, \
    { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109, k110, k111 },  \
    { k200, k201, k202, k203, k204, k205, KC_NO, k207, k208, k209, k210, k211 }   \
}
