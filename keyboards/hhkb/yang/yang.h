/* Copyright 2021 Kan-Ru Chen <kanru@kanru.info>
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

#define LAYOUT_60_hhkb(                                                        \
    K31, K30, K00, K10, K11, K20, K21, K40, K41, K60, K61, K70, K71, K50, K51, \
    K32, K01, K02, K13, K12, K23, K22, K42, K43, K62, K63, K73, K72, K52,      \
    K33, K04, K03, K14, K15, K24, K25, K45, K44, K65, K64, K74, K53,           \
    K34, K05, K06, K07, K16, K17, K26, K46, K66, K76, K75, K55, K54,           \
         K35, K36,           K37,                K57, K56)                     \
                                                                               \
{                                                                              \
    { K00, K01, K02, K03, K04, K05, K06, K07   },                              \
    { K10, K11, K12, K13, K14, K15, K16, K17   },                              \
    { K20, K21, K22, K23, K24, K25, K26, KC_NO },                              \
    { K30, K31, K32, K33, K34, K35, K36, K37   },                              \
    { K40, K41, K42, K43, K44, K45, K46, KC_NO },                              \
    { K50, K51, K52, K53, K54, K55, K56, K57   },                              \
    { K60, K61, K62, K63, K64, K65, K66, KC_NO },                              \
    { K70, K71, K72, K73, K74, K75, K76, KC_NO }                               \
}
