/* Copyright 2023 Viktus Design LLC
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

#define LAYOUT_all( \
    K10, K11, K01, K02, K12, K13, K03, K04, K14, K15, K05, K06, \
    K30, K31, K21, K22, K32, K33, K23, K24, K34, K35, K25, K26, \
    K50, K51, K41, K42, K52, K53, K43, K44, K54, K55, K45, K46, \
         K71, K61, K62, K72, K73, K63, K64, K74, K75            \
) \
{ \
    { ___, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, ___ }, \
    { ___, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, ___ }, \
    { ___, K41, K42, K43, K44, K45, K46 }, \
    { K50, K51, K52, K53, K54, K55, ___ }, \
    { ___, K61, K62, K63, K64, ___, ___ }, \
    { ___, K71, K72, K73, K74, K75, ___ }  \
},

#define LAYOUT_dual175u( \
    K10, K11, K01, K02, K12, K13, K03, K04, K14, K15, K05, K06, \
    K30, K31, K21, K22, K32, K33, K23, K24, K34, K35, K25, K26, \
    K50, K51, K41, K42, K52, K53, K43, K44, K54, K55, K45, K46, \
         K71, K61, K62,   K72,       K63,   K64, K74, K75       \
) \
{ \
    { ___, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, ___ }, \
    { ___, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, ___ }, \
    { ___, K41, K42, K43, K44, K45, K46 }, \
    { K50, K51, K52, K53, K54, K55, ___ }, \
    { ___, K61, K62, K63, K64, ___, ___ }, \
    { ___, K71, K72, ___, K74, K75, ___ }  \
},

#define LAYOUT_275_225u( \
    K10, K11, K01, K02, K12, K13, K03, K04, K14, K15, K05, K06, \
    K30, K31, K21, K22, K32, K33, K23, K24, K34, K35, K25, K26, \
    K50, K51, K41, K42, K52, K53, K43, K44, K54, K55, K45, K46, \
         K71, K61,           K72, K63,           K74, K75       \
) \
{ \
    { ___, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, ___ }, \
    { ___, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, ___ }, \
    { ___, K41, K42, K43, K44, K45, K46 }, \
    { K50, K51, K52, K53, K54, K55, ___ }, \
    { ___, K61, ___, K63, ___, ___, ___ }, \
    { ___, K71, K72, ___, K74, K75, ___ }  \
},

#define LAYOUT_dual3u( \
    K10, K11, K01, K02, K12, K13, K03, K04, K14, K15, K05, K06, \
    K30, K31, K21, K22, K32, K33, K23, K24, K34, K35, K25, K26, \
    K50, K51, K41, K42, K52, K53, K43, K44, K54, K55, K45, K46, \
         K71, K61,           K72, K63,           K74, K75       \
) \
{ \
    { ___, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, ___ }, \
    { ___, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, ___ }, \
    { ___, K41, K42, K43, K44, K45, K46 }, \
    { K50, K51, K52, K53, K54, K55, ___ }, \
    { ___, K61, ___, K63, ___, ___, ___ }, \
    { ___, K71, K72, ___, K74, K75, ___ }  \
},

#define LAYOUT_6u( \
    K10, K11, K01, K02, K12, K13, K03, K04, K14, K15, K05, K06, \
    K30, K31, K21, K22, K32, K33, K23, K24, K34, K35, K25, K26, \
    K50, K51, K41, K42, K52, K53, K43, K44, K54, K55, K45, K46, \
         K71, K61,             K73,              K74, K75       \
) \
{ \
    { ___, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, ___ }, \
    { ___, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, ___ }, \
    { ___, K41, K42, K43, K44, K45, K46 }, \
    { K50, K51, K52, K53, K54, K55, ___ }, \
    { ___, K61, ___, ___, ___, ___, ___ }, \
    { ___, K71, ___, K73, K74, K75, ___ }  \
},

#define LAYOUT_7u( \
    K10, K11, K01, K02, K12, K13, K03, K04, K14, K15, K05, K06, \
    K30, K31, K21, K22, K32, K33, K23, K24, K34, K35, K25, K26, \
    K50, K51, K41, K42, K52, K53, K43, K44, K54, K55, K45, K46, \
         K71,                K73,                K75            \
) \
{ \
    { ___, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, ___ }, \
    { ___, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, ___ }, \
    { ___, K41, K42, K43, K44, K45, K46 }, \
    { K50, K51, K52, K53, K54, K55, ___ }, \
    { ___, ___, ___, ___, ___, ___, ___ }, \
    { ___, K71, ___, K73, ___, K75, ___ }  \
},

#define LAYOUT_10u( \
    K10, K11, K01, K02, K12, K13, K03, K04, K14, K15, K05, K06, \
    K30, K31, K21, K22, K32, K33, K23, K24, K34, K35, K25, K26, \
    K50, K51, K41, K42, K52, K53, K43, K44, K54, K55, K45, K46, \
                             K73                                \
) \
{ \
    { ___, K01, K02, K03, K04, K05, K06 }, \
    { K10, K11, K12, K13, K14, K15, ___ }, \
    { ___, K21, K22, K23, K24, K25, K26 }, \
    { K30, K31, K32, K33, K34, K35, ___ }, \
    { ___, K41, K42, K43, K44, K45, K46 }, \
    { K50, K51, K52, K53, K54, K55, ___ }, \
    { ___, ___, ___, ___, ___, ___, ___ }, \
    { ___, ___, ___, K73, ___, ___, ___ }  \
},
