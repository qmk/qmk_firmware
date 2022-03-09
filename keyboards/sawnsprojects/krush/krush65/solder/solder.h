/* Copyright 2021 SawnsProjects
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

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐      ┌───────┐
 * │00 │10 │01 │11 │02 │12 │03 │13 │04 │14 │05 │15 │06 │26 │17 │07 │      │26     │ 2u Backspace
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤      └─┬─────┤
 * │20   │30 │21 │31 │22 │32 │23 │33 │24 │34 │25 │35 │36 │46   │37 │        │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤     ┌──┴┐47  │ ISO Enter
 * │40    │50 │41 │51 │42 │52 │43 │53 │44 │54 │45 │55 │47      │57 │     │46 │    │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤     └───┴────┘
 * │60      │70 │61 │71 │62 │72 │63 │73 │64 │74 │65 │75    │77 │67 │
 * ├────┬───┴┬──┴─┬─┴───┴──┬┴───┼───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │80  │90  │81  │82      │92  │93        │94  │85  │ │95 │97 │87 │ Split Spacebar
 * └────┴────┴────┴────────┴────┴──────────┴────┴────┘ └───┴───┴───┘
 * ┌────┬────┬────┬────────────────────────┬────┬────┐
 * │80  │90  │81  │92                      │94  │85  │ Standard
 * └────┴────┴────┴────────────────────────┴────┴────┘
 * ┌─────┬───┬─────┬───────────────────────────┬─────┐
 * │80   │90 │81   │92                         │85   │ Tsangan
 * └─────┴───┴─────┴───────────────────────────┴─────┘
 */

#define LAYOUT_65_ansi_blocker( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K07, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, K37, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55,      K47, K57, \
    K60,      K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75, K77, K67, \
    K80, K90, K81,                K92,           K94, K85,      K95, K97, K87  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, XXX, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, K37 }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, K57 }, \
    { K60, K61, K62, K63, K64, K65, XXX, K67 }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, XXX, XXX, XXX, K85, XXX, K87 }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
#define LAYOUT_65_ansi_blocker_split_bs( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, K07, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, K37, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55,      K47, K57, \
    K60,      K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75, K77, K67, \
    K80, K90, K81,                K92,           K94, K85,      K95, K97, K87  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, K37 }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, K57 }, \
    { K60, K61, K62, K63, K64, K65, XXX, K67 }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, XXX, XXX, XXX, K85, XXX, K87 }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
#define LAYOUT_65_ansi_blocker_split_bs_sp( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, K07, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, K37, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55,      K47, K57, \
    K60,      K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75, K77, K67, \
    K80, K90, K81,           K82, K92, K93,      K94, K85,      K95, K97, K87  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, K37 }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, K57 }, \
    { K60, K61, K62, K63, K64, K65, XXX, K67 }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, K82, XXX, XXX, K85, XXX, K87 }, \
    { K90, XXX, K92, K93, K94, K95, XXX, K97 }, \
}
