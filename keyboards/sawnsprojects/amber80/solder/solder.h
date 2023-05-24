/* Copyright 2022 SawnsProjects
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

#define XXX KC_NO

#define LAYOUT_all( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K16, K17, K08, K18, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36, K27, K37, K28, K38, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46, K56, K57, K48, K58, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75, K76, \
    K80, K90, K81, K91, K82, K92, K83, K93, K84, K94, K85, K95, K86, K96, K88, \
    KA0, KB0, KA1, KB3, KA6, KB6, KA7, KB7, KA8, KB8  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX, K08 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28 }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38 }, \
    { K40, K41, K42, K43, K44, K45, K46, XXX, K48 }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58 }, \
    { K60, K61, K62, K63, K64, K65, XXX, XXX, XXX }, \
    { K70, K71, K72, K73, K74, K75, K76, XXX, XXX }, \
    { K80, K81, K82, K83, K84, K85, K86, XXX, K88 }, \
    { K90, K91, K92, K93, K94, K95, K96, XXX, XXX }, \
    { KA0, KA1, XXX, XXX, XXX, XXX, KA6, KA7, KA8 }, \
    { KB0, XXX, XXX, KB3, XXX, XXX, KB6, KB7, KB8 }, \
}

