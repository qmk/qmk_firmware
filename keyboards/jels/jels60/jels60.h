/*  copyright 2022 Joah Nelson (Jels)
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERAHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#define ____ KC_NO


#define LAYOUT_all( \
    K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13, K1x13,  \
    K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, K2x13,         \
    K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x12,                \
    K3x0, K3x1, K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12, K3x13,         \
    K4x0, K4x1, K4x2,       K4x4,       K4x6,             K4x9, K4x10, K4x11, K4x12, K4x13          \
){ \
    {K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13}, \
    {K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, K1x13}, \
    {K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x12, K2x13}, \
    {K3x0, K3x1, K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12, K3x13}, \
    {K4x0, K4x1, K4x2, ____, K4x4, ____, K4x6, ____, ____, K4x9, K4x10, K4x11, K4x12, K4x13}  \
}

#define LAYOUT_ansi( \
    K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13, \
    K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, K2x13, \
    K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x12,        \
    K3x0,       K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12,        \
    K4x0, K4x1, K4x2,             K4x6,                         K4x10, K4x11, K4x12, K4x13  \
){ \
    {K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13}, \
    {K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, ____ }, \
    {K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x12, K2x13}, \
    {K3x0, ____, K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12, ____ }, \
    {K4x0, K4x1, K4x2, ____, ____, ____, K4x6, ____, ____, ____, K4x10, K4x11, K4x12, K4x13}  \
}

#define LAYOUT_split_space( \
    K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13, K1x13,  \
    K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, K2x13,         \
    K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x12,                \
    K3x0, K3x1, K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12, K3x13,         \
    K4x0, K4x1, K4x2,       K4x4,       K4x6,             K4x9,        K4x11, K4x12, K4x13          \
){ \
    {K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13}, \
    {K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, K1x13}, \
    {K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x12, K2x13}, \
    {K3x0, K3x1, K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12, K3x13}, \
    {K4x0, K4x1, K4x2, ____, K4x4, ____, K4x6, ____, ____, K4x9,  ____, K4x11, K4x12, K4x13}  \
}

#define LAYOUT_tsangan_split_bs( \
    K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13, K1x13,  \
    K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, K2x13,         \
    K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x12,                \
    K3x0,       K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12, K3x13,         \
    K4x0, K4x1, K4x2,              K4x6,                        K4x10,        K4x12, K4x13          \
){ \
    {K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13}, \
    {K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, K1x13}, \
    {K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x12, K2x13}, \
    {K3x0, ____, K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12, K3x13}, \
    {K4x0, K4x1, K4x2, ____, ____, ____, K4x6, ____, ____, ____, K4x10,  ____, K4x12, K4x13}  \
}

#define LAYOUT_iso( \
    K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13,         \
    K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, K2x12,         \
    K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x13,                \
    K3x0, K3x1, K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12, K3x13,         \
    K4x0, K4x1, K4x2,              K4x6,                        K4x10,        K4x12, K4x13          \
){ \
    {K0x0, K0x1, K0x2, K0x3, K0x4, K0x5, K0x6, K0x7, K0x8, K0x9, K0x10, K0x11, K0x12, K0x13}, \
    {K1x0, K1x1, K1x2, K1x3, K1x4, K1x5, K1x6, K1x7, K1x8, K1x9, K1x10, K1x11, K1x12, ____ }, \
    {K2x0, K2x1, K2x2, K2x3, K2x4, K2x5, K2x6, K2x7, K2x8, K2x9, K2x10, K2x11, K2x12, K2x13}, \
    {K3x0, K3x1, K3x2, K3x3, K3x4, K3x5, K3x6, K3x7, K3x8, K3x9, K3x10, K3x11, K3x12, K3x13}, \
    {K4x0, K4x1, K4x2, ____, ____, ____, K4x6, ____, ____, ____, K4x10,  ____, K4x12, K4x13}  \
}



