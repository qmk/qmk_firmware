/* Copyright 2022 ryanbaekr
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

#define ___ KC_NO

#define LAYOUT_numpad_5x4(         \
    k00, k11, k02, k03, \
    k10, k21, k12,      \
    k20, k31, k22, k13, \
    k30, k41, k32,      \
    k40,      k42, k33  \
){ \
    { k00, ___, k02, k03 },  \
    { k10, k11, k12, k13 },  \
    { k20, k21, k22, ___ },  \
    { k30, k31, k32, k33 },  \
    { k40, k41, k42, ___ }   \
}
