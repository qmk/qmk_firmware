/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#pragma once

#include "morpho.h"
#include "quantum.h"

// clang-format off
#define LAYOUT_split_6x7(                                               \
    L00, L01, L02, L03, L04, L05, L06, R00, R01, R02, R03, R04, R05, R06, \
    L10, L11, L12, L13, L14, L15, L16, R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, L26, R20, R21, R22, R23, R24, R25, R26, \
    L30, L31, L32, L33, L34, L35, L36, R30, R31, R32, R33, R34, R35, R36, \
    L40, L41, L42, L43, L44, L45, L46, R40, R41, R42, R43, R44, R45, R46, \
    L50, L51, L52, L53, L54, L55, L56, R50, R51, R52, R53, R54, R55, R56 \
                                                                        ) \
  {                                                                     \
    { L00, L01, L02, L03, L04, L05, L06 },                              \
    { L10, L11, L12, L13, L14, L15, L16 },                              \
    { L20, L21, L22, L23, L24, L25, L26 },                              \
    { L30, L31, L32, L33, L34, L35, L36 },                              \
    { L40, L41, L42, L43, L44, L45, L46 },                              \
    { L50, L51, L52, L53, L54, L55, L56 },                              \
    { R06, R05, R04, R03, R02, R01, R00 },                              \
    { R16, R15, R14, R13, R12, R11, R10 },                              \
    { R26, R25, R24, R23, R22, R21, R20 },                              \
    { R36, R35, R34, R33, R32, R31, R30 },                              \
    { R46, R45, R44, R43, R42, R41, R40 },                              \
    { R56, R55, R54, R53, R52, R51, R50 }                               \
  }

#define LAYOUT LAYOUT_split_6x7


#define LAYOUT_split_4x6_5_8(                                   \
                             L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
                             L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
                             L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
                             L30, L31, L32, L33, L34, L35, R30, R31, R32, R33, R34, R35, \
                             L40, L41, L42, L43, L44,      R40, R41, R42, R43, R44, \
                             L45, L46,                     R45, R46,    \
                             L50, L51, L52,                R50, R51, R52, \
                             L53, L54, L55,                R53, R54, R55 \
                                                                        ) \
  {                                                                     \
    { L00, L01, L02, L03, L04, L05, KC_NO },                            \
    { L10, L11, L12, L13, L14, L15, KC_NO },                          \
    { L20, L21, L22, L23, L24, L25, KC_NO },                          \
    { L30, L31, L32, L33, L34, L35, KC_NO },                          \
    { L40, L41, L42, L43, L44, L45, L46 },                            \
    { L50, L51, L52, L53, L54, L55, KC_NO },                          \
    { R05, R04, R03, R02, R01, R00, KC_NO },                   \
    { R15, R14, R13, R12, R11, R10, KC_NO },                         \
    { R25, R24, R23, R22, R21, R20, KC_NO },                         \
    { R35, R34, R33, R32, R31, R30 , KC_NO},                         \
    { R44, R43, R42, R41, R40, R46, R45},                            \
    { R55, R54, R53, R52, R51, R50, KC_NO }                          \
  }

// kinesis/dactyl
#define LAYOUT_split_4x6_5_6(                                           \
                             L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
                             L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
                             L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
                             L30, L31, L32, L33, L34, L35, R30, R31, R32, R33, R34, R35, \
                             L40, L41, L42, L43, L44,      R40, R41, R42, R43, R44, \
                             L50, L51, L52,                R50, R51, R52, \
                             L53, L54, L55,                R53, R54, R55 \
                                                                        ) \
  {                                                                     \
    { L00, L01, L02, L03, L04, L05, KC_NO },                            \
    { L10, L11, L12, L13, L14, L15, KC_NO },                            \
    { L20, L21, L22, L23, L24, L25, KC_NO },                            \
    { L30, L31, L32, L33, L34, L35, KC_NO },                            \
    { L40, L41, L42, L43, L44, L45, KC_NO },                            \
    { L50, L51, L52, L53, L54, L55, KC_NO },                            \
    { KC_NO, R05, R04, R03, R02, R01, R00 },                            \
    { KC_NO, R15, R14, R13, R12, R11, R10 },                            \
    { KC_NO, R25, R24, R23, R22, R21, R20 },                            \
    { KC_NO, R35, R34, R33, R32, R31, R30 },                            \
    { KC_NO, R45, R44, R43, R42, R41, R40 },                            \
    { KC_NO, R55, R54, R53, R52, R51, R50 }                             \
  }


// corne
#define LAYOUT_split_3x6_3(                                           \
    L00, L01, L02, L03, L04, L05,    R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,    R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,    R20, R21, R22, R23, R24, R25, \
    L30, L31, L32,                   R30, R31, R32               \
                                                                      ) \
  {                                                                     \
    { L00, L01, L02, L03, L04, L05 },                                   \
    { L10, L11, L12, L13, L14, L15 },                                   \
    { L20, L21, L22, L23, L24, L25 },                                   \
    { KC_NO, KC_NO, KC_NO, L30, L31, L32 },                             \
    { R05, R04, R03, R02, R01, R00 },                                   \
    { R15, R14, R13, R12, R11, R10 },                                   \
    { R25, R24, R23, R22, R21, R20 },                                   \
    { KC_NO, KC_NO, KC_NO, R32, R31, R30 }                              \
  }

#define LAYOUT_split_3x5_3(                                             \
    L00, L01, L02, L03, L04,           R00, R01, R02, R03, R04,         \
    L10, L11, L12, L13, L14,           R10, R11, R12, R13, R14,         \
    L20, L21, L22, L23, L24,           R20, R21, R22, R23, R24,         \
    L30, L31, L32, R30, R31, R32                                        \
                            )                                           \
  {                                                                     \
    { KC_NO, L00, L01, L02, L03, L04 },                                 \
    { KC_NO, L10, L11, L12, L13, L14 },                                 \
    { KC_NO, L20, L21, L22, L23, L24 },                                 \
    { KC_NO, KC_NO, KC_NO, L30, L31, L32 },                             \
    { KC_NO, R04, R03, R02, R01, R00 },                                 \
    { KC_NO, R14, R13, R12, R11, R10 },                                 \
    { KC_NO, R24, R23, R22, R21, R20 },                                 \
    { KC_NO, KC_NO, KC_NO, R32, R31, R30 }                              \
  }
