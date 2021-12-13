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
//x
#define LAYOUT_all( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75, K66, K77, \
    K80, K90, K81, K82, K92, K84, K94, K85, K86, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, K82, XXX, K84, K85, K86, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}

//LAYOUT_60_ansi
//x
#define LAYOUT_60_ansi( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K66, \
    K80, K90, K81, K92, K94, K85, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, XXX, XXX, XXX }, \
    { K80, K81, XXX, XXX, XXX, K85, XXX, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
//LAYOUT_60_iso
//x
#define LAYOUT_60_iso(\
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K66, \
    K80, K90, K81, K92, K94, K85, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, XXX, XXX, XXX }, \
    { K80, K81, XXX, XXX, XXX, K85, XXX, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_split_bs
#define LAYOUT_60_ansi_split_bs( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K66, \
    K80, K90, K81, K92, K94, K85, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, XXX, XXX, XXX }, \
    { K80, K81, XXX, XXX, XXX, K85, XXX, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_split_spc
#define LAYOUT_60_ansi_split_spc( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K66, \
    K80, K90, K81, K82, K92, K84, K94, K85, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, XXX, XXX, XXX }, \
    { K80, K81, K82, XXX, K84, K85, XXX, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_split_bs_spc
#define LAYOUT_60_ansi_split_bs_spc( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K66, \
    K80, K90, K81, K82, K92, K84, K94, K85, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, XXX, XXX, XXX }, \
    { K80, K81, K82, XXX, K84, K85, XXX, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_7u_spc
#define LAYOUT_60_ansi_7u_spc( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K66, \
    K80, K90, K81, K92, K85, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, XXX, XXX, XXX }, \
    { K80, K81, XXX, XXX, XXX, K85, XXX, XXX }, \
    { K90, XXX, K92, XXX, XXX, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_split_7u_spc
#define LAYOUT_60_ansi_split_bs_7u_spc( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K66, \
    K80, K90, K81, K92, K85, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, XXX, XXX, XXX }, \
    { K80, K81, XXX, XXX, XXX, K85, XXX, XXX }, \
    { K90, XXX, K92, XXX, XXX, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_arrow_split_bs
#define LAYOUT_60_ansi_arrow_split_bs( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K75, K66, K77, \
    K80, K90, K81, K92, K94, K85, K86, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, XXX, K66, XXX }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, XXX, XXX, XXX, K85, K86, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_arrow_split_spc
#define LAYOUT_60_ansi_arrow_split_spc( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K75, K66, K77, \
    K80, K90, K81, K82, K92, K84, K94, K85, K86, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, XXX, K66, XXX }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, K82, XXX, K84, K85, K86, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_arrow_split_bs_spc
#define LAYOUT_60_ansi_arrow_split_bs_spc( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K75, K66, K77, \
    K80, K90, K81, K82, K92, K84, K94, K85, K86, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, XXX, K66, XXX }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, K82, XXX, K84, K85, K86, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_arrow_7u_spc
#define LAYOUT_60_ansi_arrow_7u_spc( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K75, K66, K77, \
    K80, K90, K81, K92, K85, K86, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, XXX, K66, XXX }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, XXX, XXX, XXX, K85, K86, XXX }, \
    { K90, XXX, K92, XXX, XXX, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_arrow
//x
#define LAYOUT_60_ansi_arrow( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K75, K66, K77, \
    K80, K90, K81, K92, K94, K85, K86, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, XXX, K66, XXX }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, XXX, XXX, XXX, K85, K86, XXX }, \
    { K90, XXX, K92, XXX, K94, K95, XXX, K97 }, \
}
//x
//LAYOUT_60_ansi_arrow_split_bs_7u_spc
#define LAYOUT_60_ansi_arrow_split_bs_7u_spc( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K75, K66, K77, \
    K80, K90, K81, K92, K85, K86, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, XXX, K66, XXX }, \
    { K70, K71, K72, K73, K74, K75, XXX, K77 }, \
    { K80, K81, XXX, XXX, XXX, K85, K86, XXX }, \
    { K90, XXX, K92, XXX, XXX, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_tsangan
#define LAYOUT_60_ansi_tsangan( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K66, K77, \
    K80, K90, K81, K92, K85, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, XXX, XXX, K77 }, \
    { K80, K81, XXX, XXX, XXX, K85, XXX, XXX }, \
    { K90, XXX, K92, XXX, XXX, K95, XXX, K97 }, \
}
//LAYOUT_60_ansi_tsangan_split_bs
#define LAYOUT_60_ansi_tsangan_split_bs( \
    K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K26, K17, \
    K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K36, K46, \
    K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55, K47, \
    K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K66, K77, \
    K80, K90, K81, K92, K85, K95, K97  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, XXX }, \
    { K10, K11, K12, K13, K14, K15, XXX, K17 }, \
    { K20, K21, K22, K23, K24, K25, K26, XXX }, \
    { K30, K31, K32, K33, K34, K35, K36, XXX }, \
    { K40, K41, K42, K43, K44, K45, K46, K47 }, \
    { K50, K51, K52, K53, K54, K55, XXX, XXX }, \
    { K60, K61, K62, K63, K64, K65, K66, XXX }, \
    { K70, K71, K72, K73, K74, XXX, XXX, K77 }, \
    { K80, K81, XXX, XXX, XXX, K85, XXX, XXX }, \
    { K90, XXX, K92, XXX, XXX, K95, XXX, K97 }, \
}
//LAYOUT_60_iso_tsangan
#define LAYOUT_60_iso_tsangan  LAYOUT_60_ansi_tsangan
//LAYOUT_60_iso_tsangan_split_bs
#define LAYOUT_60_iso_tsangan_split_bs  LAYOUT_60_ansi_tsangan_split_bs
