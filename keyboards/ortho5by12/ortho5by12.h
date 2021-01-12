/* Copyright 2019 Yiancar
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
#define XXX KC_NO
#include "quantum.h"

#define LAYOUT_ortho_5x12( \
        K00,  K01,  K02,  K03,  K04,  K05,  K10,  K11,  K12,  K13,  K14,  K15, \
        K20,  K21,  K22,  K23,  K24,  K25,  K30,  K31,  K32,  K33,  K34,  K35, \
        K40,  K41,  K42,  K43,  K44,  K45,  K50,  K51,  K52,  K53,  K54,  K55, \
        K60,  K61,  K62,  K63,  K64,  K65,  K70,  K71,  K72,  K73,  K74,  K75, \
        K80,  K81,  K82,  K83,  K84,  K85,  K90,  K91,  K92,  K93,  K94,  K95  \
) { \
    { K01, K03, K05, K11, K13, K15 }, \
    { K00, K02, K04, K10, K12, K14 }, \
    { K20, K22, K24, K30, K32, K34 }, \
    { K21, K23, K25, K31, K33, K35 }, \
    { K41, K43, K45, K51, K53, K55 }, \
    { K40, K42, K44, K50, K52, K54 }, \
    { K60, K62, K64, K70, K72, K74 }, \
    { K61, K63, K65, K71, K73, K75 }, \
    { K81, K83, K85, K91, K93, K95 }, \
    { K80, K82, K84, K90, K92, K94 }  \
}

#define LAYOUT_ortho_5x12_1x2uC( \
        K00,  K01,  K02,  K03,  K04,  K05,  K10,  K11,  K12,  K13,  K14,  K15, \
        K20,  K21,  K22,  K23,  K24,  K25,  K30,  K31,  K32,  K33,  K34,  K35, \
        K40,  K41,  K42,  K43,  K44,  K45,  K50,  K51,  K52,  K53,  K54,  K55, \
        K60,  K61,  K62,  K63,  K64,  K65,  K70,  K71,  K72,  K73,  K74,  K75, \
        K80,  K81,  K82,  K83,  K84,     K85,     K91,  K92,  K93,  K94,  K95  \
) { \
    { K01, K03, K05, K11, K13, K15 }, \
    { K00, K02, K04, K10, K12, K14 }, \
    { K20, K22, K24, K30, K32, K34 }, \
    { K21, K23, K25, K31, K33, K35 }, \
    { K41, K43, K45, K51, K53, K55 }, \
    { K40, K42, K44, K50, K52, K54 }, \
    { K60, K62, K64, K70, K72, K74 }, \
    { K61, K63, K65, K71, K73, K75 }, \
    { K81, K83, K85, K91, K93, K95 }, \
    { K80, K82, K84, XXX, K92, K94 }  \
}
