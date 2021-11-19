/* Copyright 2021 jurassic73
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys minus blanks in the matrix.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix which includes blanks in the wired out matrix.
 */
#define LAYOUT( \
    K04,      K05, K06, K07, K08, K09,        K60, K61, K62, K63, K64, K65, K66,   K67, K68, K69, \
    K24, K14, K15, K16, K17, K18, K19,        K70, K71, K72, K73, K74, K75, K76,   K77, K78, K79, \
    K34, K25, K26, K27, K28, K29,        K39, K90, K80, K81, K82, K83, K84, K85,   K86, K87, K88, \
    K89, K44, K35, K36, K37, K38,        K49, KA0, K91, K92, K93, K94,      K95,                  \
    K96,      K54, K45, K46, K47, K48,        K59, KB0, KA1, KA2, KA3,      KA4,        KA6,      \
    KA8, K55, K56, K57,           K58,        KB1,           KB3, KB4, KB5, KB6,   KB7, KB8, KB9  \
    ) \
    { \
      { XXX, XXX, XXX, XXX, K04, K05, K06, K07, K08, K09 }, \
      { XXX, XXX, XXX, XXX, K14, K15, K16, K17, K18, K19 }, \
      { XXX, XXX, XXX, XXX, K24, K25, K26, K27, K28, K29 }, \
      { XXX, XXX, XXX, XXX, K34, K35, K36, K37, K38, K39 }, \
      { XXX, XXX, XXX, XXX, K44, K45, K46, K47, K48, K49 }, \
      { XXX, XXX, XXX, XXX, K54, K55, K56, K57, K58, K59 }, \
      { K60, K61, K62, K63, K64, K65, K66, K67, K68, K69 }, \
      { K70, K71, K72, K73, K74, K75, K76, K77, K78, K79 }, \
      { K80, K81, K82, K83, K84, K85, K86, K87, K88, K89 }, \
      { K90, K91, K92, K93, K94, K95, K96, XXX, XXX, XXX }, \
      { KA0, KA1, KA2, KA3, KA4, XXX, KA6, XXX, KA8, XXX }, \
      { KB0, KB1, XXX, KB3, KB4, KB5, KB6, KB7, KB8, KB9 }  \
}
