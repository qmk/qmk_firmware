#pragma once

/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// define our rows for the mod layer
// takes 5 keycodes, adds mods, and left and right edge keys.
// So we get keycodes in groups of 6.
//
// #define LANG_IS BEPO // to get Bepo substititions for keys and LTs.
// #define NO_EDGE_COL  // for 5 column keyboards with no sixth column.
//
// wrap layers that have alternates for other locales with LANG_N
// this will change the name, from _SYMB to _SYMB_BP as needed.
//
// Home Row mods and other things like that go here.

#include "keycodes.h"
#include "alt_mods.h"
#include "hrm_sacg.h"
#include "hrm_gacs.h"
#include "hrm_gacs_miryoku.h"
#include "hrm_gasc.h"
#include "hrs_nav.h"
#include "trns_mods.h"

// redefined by the map as needed.
//#base_cols_in_out 5_6 // 5, 5_6, 6
// MOD_ROW
// variants.
// input 5 get six, left and right language specific outer edge keys.

// no edge keys.
// input 5 get 5 with mods applied.

// input 6 get 6 with mods applied.

// base cols in out.  5, 5_6, 6.
// input column count, output column count, if different.

#define CONCATENATER(a, ...) a ## __VA_ARGS__
#define CATR(a, ...) CONCATENATER(a, __VA_ARGS__)
#define CONCATENATER2(a, ...) a ## __VA_ARGS__
#define CATR2(a, ...) CONCATENATER2(a, __VA_ARGS__)
#define CONCATENATER3(a, ...) a ## __VA_ARGS__
#define CATR3(a, ...) CONCATENATER3(a, __VA_ARGS__)

// mod layer name construction. add new layer extensions here.
// TRNS, ALT, HRM_GACS, HRM_SCAG, HRM_GASC, MIRYOKU_HRM_GASC
#define MOD_EXT CATR3(MODS_ARE, _MOD)
#define TRNS_MOD _trns
#define HRM_SCAG_MOD _hrm_scag
#define HRM_GACS_MOD _hrm_gacs
#define HRM_GASC_MOD _hrm_gasc
#define MIRYOKU_HRM_GACS_MOD _miryoku_hrm_gacs
#define ALT_MOD _alt
#define HRS_NAV_MOD _hrs_nav

// MOD_COL_NAME(ROW0L) -- > ROW0L_5, ROW0L_6, ROW0L_5_6
#define MOD_COL_NAME(NAME) CATR2(CATR(NAME, _), BASE_COLS_IN_OUT)
// MOD_ROW(ROW0L) -- > ROW0L_5_alt, ROW0L_6_alt, ROW0L_5_6_alt
#define MOD_ROW(NAME) CATR3(MOD_COL_NAME(NAME), MOD_EXT)

// change the columns in/out according to the map and the keyboard.
//#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6


// These make it easier to create base layer layouts.
// They take 3x10, or 3x12 and make a 3x12 with mods.
// this isnt always useful, sometimes rows need to be
// specified explicitly in the layout. ie. layouts with
// extra keys in the middle.


#define MOD_CORE_3x5(                           \
                     K01, K02, K03, K04, K05,   \
                     K06, K07, K08, K09, K0A,   \
                     K11, K12, K13, K14, K15,   \
                     K16, K17, K18, K19, K1A,   \
                     K21, K22, K23, K24, K25,   \
                     K26, K27, K28, K29, K2A)   \
  MOD_ROW(ROW1L)(K01, K02, K03, K04, K05),      \
    MOD_ROW(ROW1R)(K06, K07, K08, K09, K0A),     \
    MOD_ROW(ROW2L)(K11, K12, K13, K14, K15),     \
    MOD_ROW(ROW2R)(K16, K17, K18, K19, K1A),     \
    MOD_ROW(ROW3L)(K21, K22, K23, K24, K25),     \
    MOD_ROW(ROW3R)(K26, K27, K28, K29, K2A)


#define MOD_CORE_3x6(K01, K02, K03, K04, K05, K06,      \
                     K07, K08, K09, K0A, K0B, K0C,      \
                     K11, K12, K13, K14, K15, K16,      \
                     K17, K18, K19, K1A, K1B, K1C,      \
                     K21, K22, K23, K24, K25, K26,      \
                     K27, K28, K29, K2A, K2B, K2C)      \
  MOD_ROW(ROW1L)(K01, K02, K03, K04, K05, K06),         \
    MOD_ROW(ROW1R)(K07, K08, K09, K0A, K0B, K0C),       \
    MOD_ROW(ROW2L)(K11, K12, K13, K14, K15, K16),       \
    MOD_ROW(ROW2R)(K17, K18, K19, K1A, K1B, K1C),       \
    MOD_ROW(ROW3L)(K21, K22, K23, K24, K25, K26),       \
    MOD_ROW(ROW3R)(K27, K28, K29, K2A, K2B, K2C)


/// 4 rows for keyboards with number rows.
#define MOD_CORE_4x5(                                   \
                     K01, K02, K03, K04, K05,           \
                     K06, K07, K08, K09, K0A,           \
                     K11, K12, K13, K14, K15,           \
                     K16, K17, K18, K19, K1A,           \
                     K21, K22, K23, K24, K25,           \
                     K26, K27, K28, K29, K2A,           \
                     K31, K32, K33, K34, K35,           \
                     K36, K37, K38, K39, K3A)           \
  MOD_ROW(ROW0L)(K01, K02, K03, K04, K05),                              \
    MOD_ROW(ROW0R)(K06, K07, K08, K09, K0A),                            \
    MOD_CORE_3x5(K11, K12, K13, K14, K15,                               \
                 K16, K17, K18, K19, K1A,                               \
                 K21, K22, K23, K24, K25,                               \
                 K26, K27, K28, K29, K2A,                               \
                 K31, K32, K33, K34, K35,                               \
                 K36, K37, K38, K39, K3A)



#define MOD_CORE_4x6(K01, K02, K03, K04, K05, K06,                      \
                     K07, K08, K09, K0A, K0B, K0C,                      \
                     K11, K12, K13, K14, K15, K16,                      \
                     K17, K18, K19, K1A, K1B, K1C,                      \
                     K21, K22, K23, K24, K25, K26,                      \
                     K27, K28, K29, K2A, K2B, K2C,                      \
                     K31, K32, K33, K34, K35, K36,                      \
                     K37, K38, K39, K3A, K3B, K3C                       \
                     )                                                  \
    MOD_ROW(ROW0L)(K01, K02, K03, K04, K05, K06),                       \
      MOD_ROW(ROW0R)(K07, K08, K09, K0A, K0B, K0C),                     \
      MOD_CORE_3x6(K11, K12, K13, K14, K15, K16,                        \
                   K17, K18, K19, K1A, K1B, K1C,                        \
                   K21, K22, K23, K24, K25, K26,                        \
                   K27, K28, K29, K2A, K2B, K2C,                        \
                   K31, K32, K33, K34, K35, K36,                        \
                   K37, K38, K39, K3A, K3B, K3C)
