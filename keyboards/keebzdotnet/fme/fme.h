/*
Copyright 2021 keebnewb

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

#define LAYOUT_all( \
    k00, k13, k14, k12, k10,      \
    k11, k04, k02, k03,           \
    k22, k32, k21, k01            \
){ \
    { k00, k01, k02, k03, k04 },  \
    { k10, k11, k12, k13, k14 },  \
    { ___, k21, k22, ___, ___ },  \
    { ___, ___, k32, ___, ___ }   \
}
