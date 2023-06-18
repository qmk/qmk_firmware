/* Copyright 2023 Cutie Club

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

typedef union {
    uint32_t raw;
    struct {
        uint8_t indicator_key : 8;
    };
} keyboard_config_t;

// clang-format off
#define LAYOUT_right_all( \
    k00, k01, k02, k03, k04, \
    k10, k11, k12, k13, k14, \
    k20, k21, k22, k23, k24, \
    k30, k31, k32, k33, k34, \
    k40, k41, k42, k43, k44  \
) \
{ \
    { k00, k01, k02, k03, k04 }, \
    { k10, k11, k12, k13, k14 }, \
    { k20, k21, k22, k23, k24 }, \
    { k30, k31, k32, k33, k34 }, \
    { k40, k41, k42, k43, k44 }  \
}
// clang-format on

// clang-format off
#define LAYOUT_left_all( \
    k00, k01, k02, k03, k04, \
    k10, k11, k12, k13, k14, \
    k20, k21, k22, k23, k24, \
    k30, k31, k32, k33, k34, \
    k40, k41, k42, k43, k44  \
) \
{ \
    { k04, k03, k02, k01, k00 }, \
    { k14, k13, k12, k11, k10 }, \
    { k24, k23, k22, k21, k20 }, \
    { k34, k33, k32, k31, k30 }, \
    { k44, k43, k42, k41, k40 }  \
}
// clang-format on
