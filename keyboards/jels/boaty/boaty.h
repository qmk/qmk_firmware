/*  Copyright 2022 Joah Nelson (jels)
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

#define ___ KC_NO


#define LAYOUT_all( \
                                            K00, \
                                            K11, K10, \
                                            K20, K21, K22, \
                                            K30, K31, K32, K33, \
                                            K40, K41, K42, K43, K44, \
                                            K50, K51, K52, K53, K54, K55, \
                \
                K60, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6a, K6b, K6c, K6d,\
                     K70, K71, K72, K73, K74, K75, K76, K77, K78, K79, K7a, K7b,\
                          K80, K81, K82, K83, K84, K85, K86, K87, K88, K89,\
                                    K90, K91, K92, K93, K94, K95 \
){ \
    {___, ___, ___, ___, K30, K31, K32, K33, K20, K21, K22}, \
    {___, ___, ___, ___, K40, K41, K42, K43, K44, K10, K11}, \
    {___, ___, ___, ___, K50, K51, K52, K53, K54, K55, K00}, \
    {K71, K72, K73, K74, K75, K67, K68, K69, K6a, K6b, K6c}, \
    {K61, K81, K82, K83, K84, K76, K77, K78, K79, K7a, K7b}, \
    {K62, K63, K64, K65, K66, K85, K86, K87, K88, K89, K6d}, \
    {K60, K70, K80, K90, K91, ___, K92, K93, K94, K95, ___} \
}

