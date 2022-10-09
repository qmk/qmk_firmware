/* Copyright 2020 drhigsby
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

#define LAYOUT( \
    k000, k001, k002, k003, k004, k005, k006, k007, k008, k009, \
    k100, k101, k102, k103, k104, k105, k106, k107, k108, k109,  \
    k200, k201, k202, k203, k204, k205, k206, k207, k208, k209,   \
          		k302, k303, k304, k305, k306, k307         		   \
) { \
    { k000, k001, k002, k003, k004, k005, k006, k007, k008, k009 },   \
    { k100, k101, k102, k103, k104, k105, k106, k107, k108, k109 },    \
    { k200, k201, k202, k203, k204, k205, k206, k207, k208, k209 },     \
    { KC_NO, KC_NO, k302, k303, k304, k305, k306, k307, KC_NO, KC_NO }   \
}
