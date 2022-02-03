/*  copyright 2021 Joah Nelson (Jels)
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
    K0B0, K0B1, K0A1, K0A2, K0B2, K0B3, K0A3, K0A4, K0B4, K0B5, K0A5, K0A6, K0B6, K0B7,         K0A7, K0A8, K0B8, \
    K1A0, K1A1, K1B1, K1B2, K1A2, K1A3, K1B3, K1B4, K1A4, K1A5, K1B5, K1B6, K1A6, K1A7, K2B7,   K2A7, K2A8, K1A8, \
    K2B0, K2B1, K2A1, K2A2, K2B2, K2B3, K2A3, K2A4, K2B4, K2B5, K2A5, K2A6, K2B6, K3A7,         K1B7, K1B8, K2B8, \
    K3A0, K3A1, K3B1, K3B2, K3A2, K3A3, K3B3, K3B4, K3A4, K3A5, K3B5, K3B6, K3A6,                                 \
    K4B0, K4B1, K4A1, K4A2, K4B2, K4B3, K4A3, K4A4, K4B4, K4B5, K4A5, K4A6, K4B6, K4B7,               K4A7,       \
    K5A0, K5A1, K5B1,                   K5B3,                         K5A5, K5A6, K5B6, K5B7,   K5A7, K5A8, K4A8  \
){ \
    {____, K0A1, K0A2, K0A3, K0A4, K0A5, K0A6, K0A7, K0A8}, \
    {K0B0, K0B1, K0B2, K0B3, K0B4, K0B5, K0B6, K0B7, K0B8}, \
    {K1A0, K1A1, K1A2, K1A3, K1A4, K1A5, K1A6, K1A7, K1A8}, \
    {____, K1B1, K1B2, K1B3, K1B4, K1B5, K1B6, K1B7, K1B8}, \
    {____, K2A1, K2A2, K2A3, K2A4, K2A5, K2A6, K2A7, K2A8}, \
    {K2B0, K2B1, K2B2, K2B3, K2B4, K2B5, K2B6, K2B7, K2B8}, \
    {K3A0, K3A1, K3A2, K3A3, K3A4, K3A5, K3A6, K3A7, ____}, \
    {____, K3B1, K3B2, K3B3, K3B4, K3B5, K3B6, ____, ____}, \
    {____, K4A1, K4A2, K4A3, K4A4, K4A5, K4A6, K4A7, K4A8}, \
    {K4B0, K4B1, K4B2, K4B3, K4B4, K4B5, K4B6, K4B7, ____}, \
    {K5A0, K5A1, ____, ____, ____, K5A5, K5A6, K5A7, K5A8}, \
    {____, K5B1, ____, K5B3, ____, ____, K5B6, K5B7, ____}  \
}

#define LAYOUT_ansi( \
    K0B0, K0B1, K0A1, K0A2, K0B2, K0B3, K0A3, K0A4, K0B4, K0B5, K0A5, K0A6, K0B6, K0B7,         K0A7, K0A8, K0B8, \
    K1A0, K1A1, K1B1, K1B2, K1A2, K1A3, K1B3, K1B4, K1A4, K1A5, K1B5, K1B6, K1A6, K1A7, K2B7,   K2A7, K2A8, K1A8, \
    K2B0, K2B1, K2A1, K2A2, K2B2, K2B3, K2A3, K2A4, K2B4, K2B5, K2A5, K2A6, K2B6, K3A7,         K1B7, K1B8, K2B8, \
    K3A0, K3A1, K3B1, K3B2, K3A2, K3A3, K3B3, K3B4, K3A4, K3A5, K3B5, K3B6, K3A6,                                 \
    K4B0, K4A1, K4A2, K4B2, K4B3, K4A3, K4A4, K4B4, K4B5, K4A5, K4A6, K4B6, K4B7,               K4A7,             \
    K5A0, K5A1, K5B1,                   K5B3,                         K5A5, K5A6, K5B6, K5B7,   K5A7, K5A8, K4A8  \
){ \
    {____, K0A1, K0A2, K0A3, K0A4, K0A5, K0A6, K0A7, K0A8}, \
    {K0B0, K0B1, K0B2, K0B3, K0B4, K0B5, K0B6, K0B7, K0B8}, \
    {K1A0, K1A1, K1A2, K1A3, K1A4, K1A5, K1A6, K1A7, K1A8}, \
    {____, K1B1, K1B2, K1B3, K1B4, K1B5, K1B6, K1B7, K1B8}, \
    {____, K2A1, K2A2, K2A3, K2A4, K2A5, K2A6, K2A7, K2A8}, \
    {K2B0, K2B1, K2B2, K2B3, K2B4, K2B5, K2B6, K2B7, K2B8}, \
    {K3A0, K3A1, K3A2, K3A3, K3A4, K3A5, K3A6, K3A7, ____}, \
    {____, K3B1, K3B2, K3B3, K3B4, K3B5, K3B6, ____, ____}, \
    {____, K4A1, K4A2, K4A3, K4A4, K4A5, K4A6, K4A7, K4A8}, \
    {K4B0, K4B1, K4B2, K4B3, K4B4, K4B5, K4B6, K4B7, ____}, \
    {K5A0, K5A1, ____, ____, ____, K5A5, K5A6, K5A7, K5A8}, \
    {____, K5B1, ____, K5B3, ____, ____, K5B6, K5B7, ____}  \
}


#define LAYOUT_iso( \
    K0B0, K0B1, K0A1, K0A2, K0B2, K0B3, K0A3, K0A4, K0B4, K0B5, K0A5, K0A6, K0B6, K0B7,         K0A7, K0A8, K0B8, \
    K1A0, K1A1, K1B1, K1B2, K1A2, K1A3, K1B3, K1B4, K1A4, K1A5, K1B5, K1B6, K1A6, K1A7, K3A7,   K2A7, K2A8, K1A8, \
    K2B0, K2B1, K2A1, K2A2, K2B2, K2B3, K2A3, K2A4, K2B4, K2B5, K2A5, K2A6, K2B6, K2B7,         K1B7, K1B8, K2B8, \
    K3A0, K3A1, K3B1, K3B2, K3A2, K3A3, K3B3, K3B4, K3A4, K3A5, K3B5, K3B6, K3A6,                                 \
    K4B0, K4A1, K4A2, K4B2, K4B3, K4A3, K4A4, K4B4, K4B5, K4A5, K4A6, K4B6, K4B7,               K4A7,       \
    K5A0, K5A1, K5B1,                   K5B3,                         K5A5, K5A6, K5B6, K5B7,   K5A7, K5A8, K4A8  \
){ \
    {____, K0A1, K0A2, K0A3, K0A4, K0A5, K0A6, K0A7, K0A8}, \
    {K0B0, K0B1, K0B2, K0B3, K0B4, K0B5, K0B6, K0B7, K0B8}, \
    {K1A0, K1A1, K1A2, K1A3, K1A4, K1A5, K1A6, K1A7, K1A8}, \
    {____, K1B1, K1B2, K1B3, K1B4, K1B5, K1B6, K1B7, K1B8}, \
    {____, K2A1, K2A2, K2A3, K2A4, K2A5, K2A6, K2A7, K2A8}, \
    {K2B0, K2B1, K2B2, K2B3, K2B4, K2B5, K2B6, K2B7, K2B8}, \
    {K3A0, K3A1, K3A2, K3A3, K3A4, K3A5, K3A6, K3A7, ____}, \
    {____, K3B1, K3B2, K3B3, K3B4, K3B5, K3B6, ____, ____}, \
    {____, K4A1, K4A2, K4A3, K4A4, K4A5, K4A6, K4A7, K4A8}, \
    {K4B0, ____, K4B2, K4B3, K4B4, K4B5, K4B6, K4B7, ____}, \
    {K5A0, K5A1, ____, ____, ____, K5A5, K5A6, K5A7, K5A8}, \
    {____, K5B1, ____, K5B3, ____, ____, K5B6, K5B7, ____}  \
}
