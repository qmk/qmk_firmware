/* Copyright 2021 KDon<370490639@qq.com>
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

/*                                                                   ┌──┬──┐ ┌──┬──┐
 *                                                                   │00│20│ │60│80│
 *                                                                   └──┴──┘ └──┴──┘
 *                                                                    \─en1┘ └en2─/
 * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┐ ┌───┐ ┌───┐
 * │10 │   │01 │11 │02 │12 │ │03 │13 │04 │14 │ │05 │15 │16 │17 │ │57 │ │48 │ │40 │
 * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┘ └───┘ └───┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┬───┐
 * │30 │21 │31 │22 │32 │23 │33 │24 │34 │25 │35 │26 │36 │37     │ │39 │49 │4A │5A │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┼───┤
 * │50   │41 │51 │42 │52 │43 │53 │44 │54 │45 │55 │46 │56 │47   │ │59 │69 │6A │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┼───┼───┤   │
 * │70    │61 │71 │62 │72 │63 │73 │64 │74 │65 │75 │66 │77      │ │79 │89 │8A │7A │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘ ├───┼───┼───┼───┤
 * │90      │91 │82 │92 │83 │93 │84 │94 │85 │95 │86 │97    │┌───┐│99 │A9 │9A │   │
 * ├────┬───┼───┼───┼───┴───┴───┴───┴───┴───┴┬──┴─┬─┴──┬───┘│88 │└───┼───┼───┤   │
 * │B0  │A1 │B1 │B3 │B2                      │B5  │A7  │┌───┼───┼───┐│B9 │AA │BA │
 * └────┴───┴───┴───┴────────────────────────┴────┴────┘│B7 │A8 │B8 │└───┴───┴───┘
 *                                                      └───┴───┴───┘
 */

#define LAYOUT( \
    K10,   K01, K11, K02, K12,    K03, K13, K04, K14,   K05, K15, K16, K17,      K57,  K00,K48,K20,  K60,K40,K80, \
    K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36,   K37,      K39, K49, K4A, K5A, \
    K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K46, K56,   K47,      K59, K69, K6A,      \
    K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75, K66,      K77,        K79, K89, K8A, K7A, \
    K90, K91, K82, K92, K83, K93, K84, K94, K85, K95, K86,      K97,      K88,   K99, KA9, K9A,      \
    KB0, KA1, KB1, KB3,              KB2,             KB5,   KA7,    KB7, KA8, KB8,   KB9, KAA, KBA  \
) { \
  { K00,  K01,  K02,  K03,  K04,  K05,  XXX,  XXX,  XXX,  XXX,  XXX }, \
  { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  XXX,  XXX,  XXX }, \
  { K20,  K21,  K22,  K23,  K24,  K25,  K26,  XXX,  XXX,  XXX,  XXX }, \
  { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  XXX,  K39,  XXX }, \
  { K40,  K41,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A }, \
  { K50,  K51,  K52,  K53,  K54,  K55,  K56,  K57,  XXX,  K59,  K5A }, \
  { K60,  K61,  K62,  K63,  K64,  K65,  K66,  XXX,  XXX,  K69,  K6A }, \
  { K70,  K71,  K72,  K73,  K74,  K75,  XXX,  K77,  XXX,  K79,  K7A }, \
  { K80,  XXX,  K82,  K83,  K84,  K85,  K86,  XXX,  K88,  K89,  K8A }, \
  { K90,  K91,  K92,  K93,  K94,  K95,  XXX,  K97,  XXX,  K99,  K9A }, \
  { XXX,  KA1,  XXX,  XXX,  XXX,  XXX,  XXX,  KA7,  KA8,  KA9,  KAA }, \
  { KB0,  KB1,  KB2,  KB3,  XXX,  KB5,  XXX,  KB7,  KB8,  KB9,  KBA }  \
}
