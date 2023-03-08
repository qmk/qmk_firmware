/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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

#pragma once

#include "quantum.h"

#define ___ KC_NO

//      NUM      /       *       -
//      7        8       9       +
//      4        5       6       CALC
//      1        2       3       RET
//      0                        .

// clang-format off
#define LAYOUT( \
    k00, k01, k02, k03,\
    k10, k11, k12, k13,\
    k20, k21, k22, k23,\
    k30, k31, k32, k33,\
    k40,           k43 \
)\
{\
    { k00, k01, k02, k03 },\
    { k10, k11, k12, k13 },\
    { k20, k21, k22, k23 },\
    { k30, k31, k32, k33 },\
    { k40, ___, ___, k43 } \
}
// clang-format on