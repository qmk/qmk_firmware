/* Copyright 2021 jrfhoutx
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */


#define LAYOUT_all( \
    K10, K11, K01, K02, K12, K13, K03, K04, K14, K15, K05, K06, K16, K17, K07, \
    K30, K31, K21, K22, K32, K33, K23, K24, K34, K35, K25, K26,      K37, K27, \
    K50, K51, K41, K42, K52, K53, K43, K44, K54, K55, K45,      K56, K57, K47, \
    K70, K71, K61, K62,      K73, K63,      K74, K75, K65,      K76, K77, K67  \
) \
{ \
    { ___, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { ___, K21, K22, K23, K24, K25, K26, K27 }, \
    { K30, K31, K32, K33, K34, K35, ___, K37 }, \
    { ___, K41, K42, K43, K44, K45, ___, K47 }, \
    { K50, K51, K52, K53, K54, K55, K56, K57 }, \
    { ___, K61, K62, K63, ___, K65, ___, K67 }, \
    { K70, K71, ___, K73, K74, K75, K76, K77 }  \
}
