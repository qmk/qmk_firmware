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

#include "base_layers.h"
#include "mod_layer.h"
#include "edge_keys.h"
#include "thumbs.h"
#include QMK_KEYBOARD_H

#if (!defined(LAYOUT) && defined(KEYMAP))
#define LAYOUT KEYMAP
#endif

// every keyboard has it's Layout. We start there and make a var args
// out of it.

#define LVARG_ergodox(...)    LAYOUT_ergodox(__VA_ARGS__)
#define LVARG_edox(...)       LAYOUT_ergodox_pretty(__VA_ARGS__)
#define LAYOUT_VARG(...)      LAYOUT(__VA_ARGS__)
#define LAYOUT_PVARG(...)     LAYOUT_pretty(__VA_ARGS__)

#define LVARG_4x12(...)       LAYOUT_ortho_4x12(__VA_ARGS__)
#define LVARG_5x12(...)       LAYOUT_ortho_5x12(__VA_ARGS__)
#define LVARG_5x14(...)       LAYOUT_ortho_5x14(__VA_ARGS__)
#define LVARG_5x15(...)       LAYOUT_ortho_5x15(__VA_ARGS__)

#define Base_5x15(                                                \
                  K01, K02, K03, K04, K05,                        \
                  K06, K07, K08, K09, K0A,                        \
                  K11, K12, K13, K14, K15,                        \
                  K16, K17, K18, K19, K1A,                        \
                  K21, K22, K23, K24, K25,                        \
                  K26, K27, K28, K29, K2A,                        \
                  K31, K32, K33, K34, K35,                        \
                  K36, K37, K38, K39, K3A)                        \
  LVARG_5x15(                                                     \
             MOD_ROW(ROW0L)(K01, K02, K03, K04, K05),                   \
             MAP_CHUNK(___3_MIDDLE_T),                               \
             MOD_ROW(ROW0R)(K06, K07, K08, K09, K0A),                   \
                                                                        \
             MOD_ROW(ROW1L)(K11, K12, K13, K14, K15),                   \
             MAP_CHUNK(___3_MIDDLE_1),                                \
             MOD_ROW(ROW1R)(K16, K17, K18, K19, K1A),                   \
                                                                        \
             MOD_ROW(ROW2L)(K21, K22, K23, K24, K25),                   \
             MAP_CHUNK(___3_MIDDLE_2),                                \
             MOD_ROW(ROW2R)(K26, K27, K28, K29, K2A),                   \
                                                                        \
             MOD_ROW(ROW3L)(K31, K32, K33, K34, K35),                   \
             MAP_CHUNK(___3_MIDDLE_3),                                  \
             MOD_ROW(ROW3R)(K36, K37, K38, K39, K3A),                   \
             MAP_CHUNK(___15_BOTTOM)                                    \
                                                                  )

#define Base_5x15t6(                                                    \
                    K01, K02, K03, K04, K05, K06,                       \
                    K07, K08, K09, K0A, K0B, K0C,                       \
                    K11, K12, K13, K14, K15, K16,                       \
                    K17, K18, K19, K1A, K1B, K1C,                       \
                    K21, K22, K23, K24, K25, K26,                       \
                    K27, K28, K29, K2A, K2B, K2C,                       \
                    K31, K32, K33, K34, K35, K36,                       \
                    K37, K38, K39, K3A, K3B, K3C)                  \
  LVARG_5x15(                                                           \
             MOD_ROW(ROW0L)(K01, K02, K03, K04, K05, K06),              \
             MAP_CHUNK(___3_MIDDLE_T),                               \
             MOD_ROW(ROW0R)(K07, K08, K09, K0A, K0B, K0C),              \
             MOD_ROW(ROW1L)(K11, K12, K13, K14, K15, K16),              \
             MAP_CHUNK(___3_MIDDLE_1),                                  \
             MOD_ROW(ROW1R)(K17, K18, K19, K1A, K1B, K1C),              \
             MOD_ROW(ROW2L)(K21, K22, K23, K24, K25, K26),              \
             MAP_CHUNK(___3_MIDDLE_2),                                  \
             MOD_ROW(ROW2R)(K27, K28, K29, K2A, K2B, K2C),              \
             MOD_ROW(ROW3L)(K31, K32, K33, K34, K35, K36),              \
             MAP_CHUNK(___3_MIDDLE_3),                                  \
             MOD_ROW(ROW3R)(K37, K38, K39, K3A, K3B, K3C),              \
             MAP_CHUNK(___15_BOTTOM)                                    \
                                                                        )

// Makes 5 rows of 15. 3 columns transparent in the middle.
// Transparent outer pinky columns.
#define Transient_5x15(                                             \
                       K01, K02, K03, K04, K05,                     \
                       K07, K08, K09, K0A, K0B,                     \
                       K11, K12, K13, K14, K15,                     \
                       K17, K18, K19, K1A, K1B,                 \
                       K21, K22, K23, K24, K25,                     \
                       K27, K28, K29, K2A, K2B                     \
                                                              )    \
  LVARG_5x15(                                                      \
             ___15___,                                             \
             ___, K01, K02, K03, K04, K05,                         \
             ___3___,                                              \
             K07, K08, K09, K0A, K0B, ___,                         \
             ___, K11, K12, K13, K14, K15,                         \
             ___3___,                                              \
             K17, K18, K19, K1A, K1B, ___,                         \
             ___, K21, K22, K23, K24, K25,                         \
             ___3___,                                              \
             K27, K28, K29, K2A, K2B, ___,                         \
             MAP_CHUNK(___15_BOTTOM)                                    \
             )                                                  \

/********************************************************************/

/********************************************************************/
/* viterbi  - Ortholinear 5x14  */
/********************************************************************/
#define Base_5x14(                                                 \
                  K01, K02, K03, K04, K05,                              \
                        K06, K07, K08, K09, K0A,                        \
                        K11, K12, K13, K14, K15,                        \
                        K16, K17, K18, K19, K1A,                        \
                        K21, K22, K23, K24, K25,                        \
                        K26, K27, K28, K29, K2A,                        \
                        K31, K32, K33, K34, K35,                        \
                        K36, K37, K38, K39, K3A)                        \
  LVARG_5x14(                                                           \
             MOD_ROW(ROW0L)(K01, K02, K03, K04, K05),                   \
             MAP_CHUNK(___2_MIDDLE_T),                                  \
             MOD_ROW(ROW0R)(K06, K07, K08, K09, K0A),                   \
                                                                       \
             MOD_ROW(ROW1L)(K11, K12, K13, K14, K15),                   \
             MAP_CHUNK(___2_MIDDLE_1),                                  \
             MOD_ROW(ROW1R)(K16, K17, K18, K19, K1A),                   \
                                                                        \
             MOD_ROW(ROW2L)(K21, K22, K23, K24, K25),                   \
             MAP_CHUNK(___2_MIDDLE_2),              \
             MOD_ROW(ROW2R)(K26, K27, K28, K29, K2A),                   \
                                                                        \
             MOD_ROW(ROW3L)(K31, K32, K33, K34, K35),                   \
             MAP_CHUNK(___2_MIDDLE_3),    \
             MOD_ROW(ROW3R)(K36, K37, K38, K39, K3A),                   \
             MAP_CHUNK(___14_BOTTOM)                                    \
                                                                        )

#define Base_5x14t6(                                    \
                    K01, K02, K03, K04, K05, K06,       \
                    K07, K08, K09, K0A, K0B, K0C,       \
                    K11, K12, K13, K14, K15, K16,       \
                    K17, K18, K19, K1A, K1B, K1C,       \
                    K21, K22, K23, K24, K25, K26,       \
                    K27, K28, K29, K2A, K2B, K2C,       \
                    K31, K32, K33, K34, K35, K36,       \
                    K37, K38, K39, K3A, K3B, K3C)       \
  LVARG_5x15(                                           \
    MOD_ROW(ROW0L)(K01, K02, K03, K04, K05, K06),         \
    MAP_CHUNK(___2_MIDDLE_T),                             \
    MOD_ROW(ROW0R)(K07, K08, K09, K0A, K0B, K0C),       \
    MOD_ROW(ROW1L)(K11, K12, K13, K14, K15, K16),       \
    MAP_CHUNK(___2_MIDDLE_1),                                           \
    MOD_ROW(ROW1R)(K17, K18, K19, K1A, K1B, K1C),       \
    MOD_ROW(ROW2L)(K21, K22, K23, K24, K25, K26),       \
    MAP_CHUNK(___2_MIDDLE_2),                           \
    MOD_ROW(ROW2R)(K27, K28, K29, K2A, K2B, K2C),       \
    MOD_ROW(ROW3L)(K31, K32, K33, K34, K35, K36),       \
    MAP_CHUNK(___2_MIDDLE_3),                                   \
    MOD_ROW(ROW3R)(K37, K38, K39, K3A, K3B, K3C),               \
    MAP_CHUNK(___14_BOTTOM)                                     \
                                                        )

// 4  rows of 12. 2 columns transparent in the middle.
#define Transient_5x14(                                            \
                       K01, K02, K03, K04, K05,                    \
                       K07, K08, K09, K0A, K0B,                    \
                       K11, K12, K13, K14, K15,                         \
                       K17, K18, K19, K1A, K1B,                         \
                       K21, K22, K23, K24, K25,                     \
                       K27, K28, K29, K2A, K2B                     \
                                                              )         \
  LVARG_5x14(                                                           \
             ___14___,                                                  \
             ___, K01, K02, K03, K04, K05,                              \
             ___2___,                                                   \
             K07, K08, K09, K0A, K0B, ___,                              \
                                                                        \
             ___, K11, K12, K13, K14, K15,                              \
             ___2___,                                                   \
             K17, K18, K19, K1A, K1B, ___,                              \
                                                                        \
             ___, K21, K22, K23, K24, K25,                              \
             ___2___,                                                   \
             K27, K28, K29, K2A, K2B, ___,                              \
             MAP_CHUNK(___14_BOTTOM)                                    \
                                                                        ) \

/********************************************************************/
/* Ortholinear 4x12  */
/********************************************************************/
#define LAYOUT_4x12_base(                                               \
                         K01, K02, K03, K04, K05,                       \
                         K06, K07, K08, K09, K0A,                       \
                         K11, K12, K13, K14, K15,                       \
                         K16, K17, K18, K19, K1A,                       \
                         K21, K22, K23, K24, K25,                       \
                         K26, K27, K28, K29, K2A                        \
                                                                        ) \
  LVARG_4x12(                                                     \
             MOD_CORE_3x5(K01, K02, K03, K04, K05,                \
                          K06, K07, K08, K09, K0A,                \
                          K11, K12, K13, K14, K15,                \
                          K16, K17, K18, K19, K1A,                \
                          K21, K22, K23, K24, K25,                \
                          K26, K27, K28, K29, K2A),               \
             ___12_BOTTOM___                                            \
                                                                  )

// Just for bepo because it's a 3x6 matrix on each side.
// So 3 pairs of 6 keys, left and right.

// takes 3 makes 4  rows of 12.
#define LAYOUT_4x12_transient(                                          \
                              K01, K02, K03, K04, K05, K06,             \
                              K07, K08, K09, K0A, K0B, K0C,             \
                              K11, K12, K13, K14, K15, K16,             \
                              K17, K18, K19, K1A, K1B, K1C,             \
                              K21, K22, K23, K24, K25, K26,             \
                              K27, K28, K29, K2A, K2B, K2C              \
                                                                        ) \
  LVARG_4x12(                                                           \
             K01, K02, K03, K04, K05, K06,                              \
             K07, K08, K09, K0A, K0B, K0C,                              \
             K11, K12, K13, K14, K15, K16,                              \
             K17, K18, K19, K1A, K1B, K1C,                              \
             K21, K22, K23, K24, K25, K26,                              \
             K27, K28, K29, K2A, K2B, K2C,                              \
             ___12_BOTTOM___                                            \
             )                                                  \

/********************************************************************/
/* CRKBD  Corne or any other 3x5/6 with 3 thumbs on each side.      */
/*    The Corne has  3x6 matrix on both sides with 6 thumbs total   */
/* This Macro takes 2x3x5 and gives it pinkies, and thumbs.         */
/* Arg chunks are in the middle with the passthrough modifiers as   */
/* needed.  Sama Sama apres cette fois.                             */
/********************************************************************/

#define Base_3x6_3(                                                     \
                   K01, K02, K03, K04, K05,                             \
                   K06, K07, K08, K09, K0A,                             \
                   K11, K12, K13, K14, K15,                             \
                   K16, K17, K18, K19, K1A,                             \
                   K21, K22, K23, K24, K25,                             \
                   K26, K27, K28, K29, K2A)                             \
  LAYOUT_VARG(                                                          \
              MOD_CORE_3x5(K01, K02, K03, K04, K05,                     \
                           K06, K07, K08, K09, K0A,                     \
                           K11, K12, K13, K14, K15,                     \
                           K16, K17, K18, K19, K1A,                     \
                           K21, K22, K23, K24, K25,                     \
                           K26, K27, K28, K29, K2A),                    \
              ___6_ERGO_THUMBS___                                       \
                                                                        )

#define Base_3x6_3t6(                                                   \
                     K01, K02, K03, K04, K05, K06,                      \
                     K07, K08, K09, K0A, K0B, K0C,                      \
                     K11, K12, K13, K14, K15, K16,                      \
                     K17, K18, K19, K1A, K1B, K1C,                      \
                     K21, K22, K23, K24, K25, K26,                      \
                     K27, K28, K29, K2A, K2B, K2C)                      \
  LAYOUT_VARG(                                                          \
              MOD_CORE_3x6(                                             \
                           K01, K02, K03, K04, K05, K06,                \
                           K07, K08, K09, K0A, K0B, K0C,                \
                           K11, K12, K13, K14, K15, K16,                \
                           K17, K18, K19, K1A, K1B, K1C,                \
                           K21, K22, K23, K24, K25, K26,                \
                           K27, K28, K29, K2A, K2B, K2C),               \
              ___6_ERGO_THUMBS___                                       \
                                                        )

  // All we really need is to add the see through thumbs to the end.
#define Transient_3x6_3(                                                \
                        K01, K02, K03, K04, K05,                        \
                        K07, K08, K09, K0A, K0B,                        \
                        K11, K12, K13, K14, K15,                        \
                        K17, K18, K19, K1A, K1B,                        \
                        K21, K22, K23, K24, K25,                        \
                        K27, K28, K29, K2A, K2B                         \
                                                                        ) \
  LAYOUT_VARG(                                                          \
              ___, K01, K02, K03, K04, K05,                             \
              K07, K08, K09, K0A, K0B, ___,                             \
              ___, K11, K12, K13, K14, K15,                             \
              K17, K18, K19, K1A, K1B, ___,                             \
              ___, K21, K22, K23, K24, K25,                             \
              K27, K28, K29, K2A, K2B, ___,                             \
              ___6_ERGO_THUMBS___                                       \
                                                                        )

//___6_ERGO_THUMBS___

/********************************************************************/
/* Kinesis*/
/********************************************************************/
// A 4x6 on each side, with a 4 column fifth row, and 6 thumbs on
// each side.  - 4x6_4_6.
// Then a giant row up top, 9 keys on each side, for function keys.
#define Base_4x6_4_6(                                                   \
                     K01, K02, K03, K04, K05, \
                     K06, K07, K08, K09, K0A,                           \
                     K11, K12, K13, K14, K15,                           \
                     K16, K17, K18, K19, K1A,                           \
                     K21, K22, K23, K24, K25,                           \
                     K26, K27, K28, K29, K2A,                           \
                     K31, K32, K33, K34, K35,                           \
                     K36, K37, K38, K39, K3A                            \
                                                                        ) \
  LAYOUT_PVARG(                                                         \
               ___KINTFUNC_L___, ___KINTFUNC_R___, \
               MOD_CORE_4x5(K01, K02, K03, K04, K05,                    \
                            K06, K07, K08, K09, K0A,                    \
                            K11, K12, K13, K14, K15,                    \
                            K16, K17, K18, K19, K1A,                    \
                            K21, K22, K23, K24, K25,                    \
                            K26, K27, K28, K29, K2A,                    \
                            K31, K32, K33, K34, K35,                    \
                            K36, K37, K38, K39, K3A),                   \
               MAP_CHUNK(___4_BOTTOM_LEFT),                             \
               MAP_CHUNK(___4_BOTTOM_RIGHT),                            \
               MAP_CHUNK(___12_DOX_ALL_THUMBS)                          \
                                                                        )

#define Base_4x6_4_6t6(                                                 \
                       K01, K02, K03, K04, K05, K06,                    \
                       K07, K08, K09, K0A, K0B, K0C,                    \
                       K11, K12, K13, K14, K15, K16,                    \
                       K17, K18, K19, K1A, K1B, K1C,                    \
                       K21, K22, K23, K24, K25, K26,                    \
                       K27, K28, K29, K2A, K2B, K2C,                    \
                       K31, K32, K33, K34, K35, K36,                    \
                       K37, K38, K39, K3A, K3B, K3C)                    \
  LAYOUT_PVARG(                                                         \
               MOD_CORE_4x6(                                            \
                            K01, K02, K03, K04, K05, K06,              \
                            K07, K08, K09, K0A, K0B, K0C,              \
                            K11, K12, K13, K14, K15, K16,              \
                            K17, K18, K19, K1A, K1B, K1C,              \
                            K21, K22, K23, K24, K25, K26,              \
                            K27, K28, K29, K2A, K2B, K2C,             \
                            K31, K32, K33, K34, K35, K36,               \
                            K37, K38, K39, K3A, K3B, K3C),              \
                MAP_CHUNK(___4_BOTTOM_LEFT),                            \
                MAP_CHUNK(___4_BOTTOM_RIGHT),                           \
                MAP_CHUNK(___12_DOX_ALL_THUMBS)                         \
                                                                        )

#define Transient_4x6_4_6(                                         \
                          K01, K02, K03, K04, K05,                 \
                          K07, K08, K09, K0A, K0B,                 \
                          K11, K12, K13, K14, K15,                 \
                          K17, K18, K19, K1A, K1B,                 \
                          K21, K22, K23, K24, K25,                 \
                          K27, K28, K29, K2A, K2B                 \
                                                                       ) \
                LAYOUT_PVARG(                                           \
            ___12___, ___6___,                                                  \
            ___12___,                                                   \
            ___, K01, K02, K03, K04, K05,                               \
            K07, K08, K09, K0A, K0B, ___,                               \
            ___, K11, K12, K13, K14, K15,                               \
            K17, K18, K19, K1A, K1B, ___,                               \
            ___, K21, K22, K23, K24, K25,                               \
            K27, K28, K29, K2A, K2B, ___,                               \
            ___4___, ___4___,                                           \
            MAP_CHUNK(___12_DOX_ALL_THUMBS)                             \
                                                                        )

/* ___KINTFUNC_L___, ___KINTFUNC_R___,                      \ */

/********************************************************************/
/* Dactyl with 8 thumb keys*/
/********************************************************************/
// Basically an ergodox ez without the 3 pairs of middle keys.
// electrically 7 columns in the 5th row. 6 in the rest.
// Left, right, bottom, and thumbs all stay the same.

#define Base_4x6_5_8(                                                   \
                     K01, K02, K03, K04, K05,                           \
                     K06, K07, K08, K09, K0A,                           \
                     K11, K12, K13, K14, K15,                           \
                     K16, K17, K18, K19, K1A,                           \
                     K21, K22, K23, K24, K25,                           \
                     K26, K27, K28, K29, K2A,                           \
                     K31, K32, K33, K34, K35,                           \
                     K36, K37, K38, K39, K3A                            \
                                                                      ) \
  LAYOUT_PVARG(                                                         \
  MOD_CORE_4x5(K01, K02, K03, K04, K05,                           \
               K06, K07, K08, K09, K0A,                           \
               K11, K12, K13, K14, K15,                           \
               K16, K17, K18, K19, K1A,                           \
               K21, K22, K23, K24, K25,                           \
               K26, K27, K28, K29, K2A,                           \
               K31, K32, K33, K34, K35,                           \
               K36, K37, K38, K39, K3A                            \
               ),                                                       \
  MAP_CHUNK(___5_BOTTOM_LEFT), MAP_CHUNK(___5_BOTTOM_RIGHT),            \
  MAP_CHUNK(___16_ALL_THUMBSa)                                          \
                                                                        )

#define Base_4x6_5_8t6(                                                 \
                       K01, K02, K03, K04, K05, K06,                    \
                       K07, K08, K09, K0A, K0B, K0C,                    \
                       K11, K12, K13, K14, K15, K16,                    \
                       K17, K18, K19, K1A, K1B, K1C,                    \
                       K21, K22, K23, K24, K25, K26,                    \
                       K27, K28, K29, K2A, K2B, K2C,                    \
                       K31, K32, K33, K34, K35, K36,                    \
                       K37, K38, K39, K3A, K3B, K3C)                    \
  LAYOUT_PVARG(                                                         \
               MOD_CORE_4x6(                                            \
                            K01, K02, K03, K04, K05, K06,               \
                            K07, K08, K09, K0A, K0B, K0C,               \
                            K11, K12, K13, K14, K15, K16,               \
                            K17, K18, K19, K1A, K1B, K1C,               \
                            K21, K22, K23, K24, K25, K26,               \
                            K27, K28, K29, K2A, K2B, K2C,               \
                            K31, K32, K33, K34, K35, K36,               \
                            K37, K38, K39, K3A, K3B, K3C),              \
               MAP_CHUNK(___5_BOTTOM_LEFT), MAP_CHUNK(___5_BOTTOM_RIGHT), \
               MAP_CHUNK(___16_ALL_THUMBSa)                             \
                                                                        )

// so far no need for mods on the transient layers.
// switching to 3x5 transients. 10 column defines.
// I like 3x10 maps even on big keyboards.
# define Transient_4x6_5_8(                                             \
                           K01, K02, K03, K04, K05,                     \
                           K06, K07, K08, K09, K0A,                     \
                           K11, K12, K13, K14, K15,                     \
                           K16, K17, K18, K19, K1A,                \
                           K21, K22, K23, K24, K25,                 \
                           K26, K27, K28, K29, K2A                 \
                                                                        ) \
  LAYOUT_PVARG(                                                         \
               ___6___, ___6___,                                        \
               ___, K01, K02, K03, K04, K05,                            \
               K06, K07, K08, K09, K0A, ___,                       \
               ___, K11, K12, K13, K14, K15,                            \
               K16, K17, K18, K19, K1A, ___,                       \
               ___, K21, K22, K23, K24, K25,                            \
               K26, K27, K28, K29, K2A, ___,                       \
               ___5___, ___5___,                                        \
               MAP_CHUNK(___16_ALL_THUMBSa)                          \
                                                                        )

/********************************************************************/
/* Ergodox EZ                                                       */
/********************************************************************/
// This one is is set up to pass in the number row.
// Beakl and bepo both change the number row.
// Left, middle, right, bottom, and thumbs all stay the same.
#define Base_dox(                                                       \
                 K01, K02, K03, K04, K05,                               \
                 K06, K07, K08, K09, K0A,                               \
                 K11, K12, K13, K14, K15,                               \
                 K16, K17, K18, K19, K1A,                               \
                 K21, K22, K23, K24, K25,                               \
                 K26, K27, K28, K29, K2A,                               \
                 K31, K32, K33, K34, K35,                               \
                 K36, K37, K38, K39, K3A                                \
                                                                        ) \
  LVARG_edox(                                                           \
             MOD_ROW(ROW0L)(K01, K02, K03, K04, K05),                   \
               MAP_CHUNK(___2_MIDDLE_1),                                \
               MOD_ROW(ROW0R)(K06, K07, K08, K09, K0A),                 \
                                                                        \
             MOD_ROW(ROW1L)(K11, K12, K13, K14, K15),                   \
               MAP_CHUNK(___2_MIDDLE_2),                                \
               MOD_ROW(ROW1R)(K16, K17, K18, K19, K1A),                 \
                                                                        \
             MOD_ROW(ROW2L)(K21, K22, K23, K24, K25),                   \
             MOD_ROW(ROW2R)(K26, K27, K28, K29, K2A),                   \
                                                                        \
             MOD_ROW(ROW3L)(K31, K32, K33, K34, K35),                   \
             MAP_CHUNK(___2_MIDDLE_3),                                  \
             MOD_ROW(ROW3R)(K36, K37, K38, K39, K3A),                   \
             MAP_CHUNK(___5_BOTTOM_LEFT), MAP_CHUNK(___5_BOTTOM_RIGHT), \
             MAP_CHUNK(___12_DOX_ALL_THUMBS)                           \
                                                                        )

#define Base_doxt6(                                                     \
                   K01, K02, K03, K04, K05, K06, \
                   K07, K08, K09, K0A, K0B, K0C,                        \
                   K11, K12, K13, K14, K15, K16,                        \
                   K17, K18, K19, K1A, K1B, K1C,                        \
                   K21, K22, K23, K24, K25, K26,                        \
                   K27, K28, K29, K2A, K2B, K2C,                        \
                   K31, K32, K33, K34, K35, K36,                        \
                   K37, K38, K39, K3A, K3B, K3C)                        \
  LVARG_edox(MOD_ROW(ROW0L)(K01, K02, K03, K04, K05, K06),              \
             MAP_CHUNK(___2_MIDDLE_1),                                  \
             MOD_ROW(ROW0R)(K07, K08, K09, K0A, K0B, K0C),              \
             MOD_ROW(ROW1L)(K11, K12, K13, K14, K15, K16),              \
             MAP_CHUNK(___2_MIDDLE_2),                                  \
             MOD_ROW(ROW1R)(K17, K18, K19, K1A, K1B, K1C),              \
             MOD_ROW(ROW2L)(K21, K22, K23, K24, K25, K26),              \
             MOD_ROW(ROW2R)(K27, K28, K29, K2A, K2B, K2C),              \
             MOD_ROW(ROW3L)(K31, K32, K33, K34, K35, K36),              \
             MAP_CHUNK(___2_MIDDLE_3),                                  \
             MOD_ROW(ROW3R)(K37, K38, K39, K3A, K3B, K3C),              \
             MAP_CHUNK(___5_BOTTOM_LEFT),                              \
             MAP_CHUNK(___5_BOTTOM_RIGHT),                             \
             MAP_CHUNK(___12_DOX_ALL_THUMBS))

#define Transient_dox(                                                  \
                      K01, K02, K03, K04, K05,                          \
                      K07, K08, K09, K0A, K0B,                          \
                      K11, K12, K13, K14, K15,                          \
                      K17, K18, K19, K1A, K1B,                          \
                      K21, K22, K23, K24, K25,                          \
                      K27, K28, K29, K2A, K2B)                          \
  LVARG_edox(                                                           \
             ___14___,                                                  \
             ___, K01, K02, K03, K04, K05,                              \
             ___2___,                                                   \
             K07, K08, K09, K0A, K0B, ___,                              \
             ___, K11, K12, K13, K14, K15,                              \
             K17, K18, K19, K1A, K1B, ___,                              \
             ___, K21, K22, K23, K24, K25,                              \
             ___2___,                                                   \
             K27, K28, K29, K2A, K2B, ___,                              \
             ___5___, ___5___,                                          \
             MAP_CHUNK(___12_DOX_ALL_THUMBS)                            \
                                                                        )

#define LVARG_rebound(...)    LAYOUT_all(__VA_ARGS__)
#define Base_rebound(                                                   \
                     K01, K02, K03, K04, K05,                           \
                     K06, K07, K08, K09, K0A,                           \
                     K11, K12, K13, K14, K15,                           \
                     K16, K17, K18, K19, K1A,                           \
                     K21, K22, K23, K24, K25,                           \
                     K26, K27, K28, K29, K2A                            \
                                                                        ) \
  LVARG_rebound(                                                        \
                MOD_ROW(ROW1L)(K01, K02, K03, K04, K05),                \
                MOD_ROW(ROW1R)(K06, K07, K08, K09, K0A),                \
                                                                        \
                MOD_ROW(ROW2L)(K11, K12, K13, K14, K15),                \
                KC_CCCV,                                                \
                MOD_ROW(ROW2R)(K16, K17, K18, K19, K1A),                \
                                                                        \
                MOD_ROW(ROW3L)(K21, K22, K23, K24, K25),                \
                MO_ADJUST,                                              \
                MOD_ROW(ROW3R)(K26, K27, K28, K29, K2A),                \
                MAP_CHUNK(___13_BOTTOM)                                 \
                                                                        )

#define Base_reboundt6(                                                 \
                       K01, K02, K03, K04, K05, K06,                    \
                       K07, K08, K09, K0A, K0B, K0C,                    \
                       K11, K12, K13, K14, K15, K16,                    \
                       K17, K18, K19, K1A, K1B, K1C,                    \
                       K21, K22, K23, K24, K25, K26,                    \
                       K27, K28, K29, K2A, K2B, K2C                     \
                                                                        ) \
  LVARG_rebound(                                                        \
                MOD_ROW(ROW1L)(K01, K02, K03, K04, K05, K06),           \
                MOD_ROW(ROW1R)(K07, K08, K09, K0A, K0B, K0C),           \
                MOD_ROW(ROW2L)(K11, K12, K13, K14, K15, K16),           \
                KC_CCCV,                                                \
                MOD_ROW(ROW2R)(K17, K18, K19, K1A, K1B, K1C),           \
                MOD_ROW(ROW3L)(K21, K22, K23, K24, K25, K26),           \
                MO_ADJUST,                                              \
                MOD_ROW(ROW3R)(K27, K28, K29, K2A, K2B, K2C),              \
                MAP_CHUNK(___13_BOTTOM)                                 \
                                                                        )

#define Rebound_transient(                                              \
                          K01, K02, K03, K04, K05,                      \
                          K07, K08, K09, K0A, K0B,                      \
                          K11, K12, K13, K14, K15,                      \
                          K17, K18, K19, K1A, K1B,                      \
                          K21, K22, K23, K24, K25,                      \
                          K27, K28, K29, K2A, K2B                       \
                                                                       ) \
  LVARG_rebound(                                                        \
                ___, K01, K02, K03, K04, K05,                           \
                K07, K08, K09, K0A, K0B, ___,                           \
                ___, K11, K12, K13, K14, K15,                           \
                ___,                                                    \
                K17, K18, K19, K1A, K1B, ___,                           \
                ___, K21, K22, K23, K24, K25,                           \
                ___,                                                    \
                K27, K28, K29, K2A, K2B, ___,                           \
                MAP_CHUNK(___13_BOTTOM)                            \
                                                                        )

/********************************************************************/
/* Kyria  or any other 3x5/6 with 4 keys in the middle of the last  */
/* Row. Followed by 5 thumb keys on each side. 7 thumb keys total.  */
/********************************************************************/
#define Base_2x6_8_5(                                                   \
                     K01, K02, K03, K04, K05, \
                     K06, K07, K08, K09, K0A,                           \
                     K11, K12, K13, K14, K15,                           \
                     K16, K17, K18, K19, K1A,                           \
                     K21, K22, K23, K24, K25,                           \
                     K26, K27, K28, K29, K2A)                           \
  LAYOUT_VARG(                                                          \
              MOD_ROW(ROW1L)(K01, K02, K03, K04, K05),                  \
              MOD_ROW(ROW1R)(K06, K07, K08, K09, K0A),                  \
                                                                        \
              MOD_ROW(ROW2L)(K11, K12, K13, K14, K15),                  \
              MOD_ROW(ROW2R)(K16, K17, K18, K19, K1A),                  \
                                                                        \
              MOD_ROW(ROW3L)(K21, K22, K23, K24, K25),                  \
              MAP_CHUNK(___4_THUMBS),                                   \
              MOD_ROW(ROW3R)(K26, K27, K28, K29, K2A),                  \
              MAP_CHUNK(___10_ERGO_THUMBS)                              \
                                                                        )

#define Base_2x6_8_5t6(                                                \
                       K01, K02, K03, K04, K05, K06,                    \
                       K07, K08, K09, K0A, K0B, K0C,                    \
                       K11, K12, K13, K14, K15, K16,                    \
                       K17, K18, K19, K1A, K1B, K1C,                    \
                       K21, K22, K23, K24, K25, K26,                    \
                       K27, K28, K29, K2A, K2B, K2C)                    \
  LAYOUT_VARG(                                                          \
              MOD_ROW(ROW1L)(K01, K02, K03, K04, K05, K06),            \
              MOD_ROW(ROW1R)(K07, K08, K09, K0A, K0B, K0C),            \
              MOD_ROW(ROW2L)(K11, K12, K13, K14, K15, K16),            \
              MOD_ROW(ROW2R)(K17, K18, K19, K1A, K1B, K1C),            \
              MOD_ROW(ROW3L)(K21, K22, K23, K24, K25, K26),            \
              MAP_CHUNK(___4_THUMBS),                                   \
              MOD_ROW(ROW3R)(K27, K28, K29, K2A, K2B, K2C),             \
              MAP_CHUNK(___10_ERGO_THUMBS)                              \
              )

// All we really need is to add the see through thumbs to the end.
#define Transient_2x6_8_5(                                              \
                          K01, K02, K03, K04, K05,                      \
                          K07, K08, K09, K0A, K0B,                      \
                          K11, K12, K13, K14, K15,                      \
                          K17, K18, K19, K1A, K1B,                      \
                          K21, K22, K23, K24, K25,                      \
                          K27, K28, K29, K2A, K2B                       \
                                                                        ) \
  LAYOUT_VARG(                                                          \
              ___, K01, K02, K03, K04, K05,                             \
              K07, K08, K09, K0A, K0B, ___,                             \
              ___, K11, K12, K13, K14, K15,                             \
              K17, K18, K19, K1A, K1B, ___,                             \
              ___, K21, K22, K23, K24, K25,                             \
              ___4___,                                                \
              K27, K28, K29, K2A, K2B, ___,                           \
              MAP_CHUNK(___10_ERGO_THUMBS)                             \
                                                                        )

/********************************************************************/
/* Hummingbird 2+3x3+2 with 2 thumbs.  A 30.                        */
/********************************************************************/

// Some macros to help trim the incoming matrix down.

#define TAKE_FIRST_FOUR(K01, K02, K03, K04, K05) \
                         K01, K02, K03, K04
#define TFF(...) TAKE_FIRST_FOUR(__VA_ARGS__)

#define TAKE_LAST_FOUR(K01, K02, K03, K04, K05) \
                         K02, K03, K04, K05
#define TLF(...) TAKE_LAST_FOUR(__VA_ARGS__)

// 4 out of 6.
#define TAKE_MIDDLE_FOUR(K01, K02, K03, K04, K05, K06) \
                         K02, K03, K04, K05
#define TMF(...) TAKE_MIDDLE_FOUR(__VA_ARGS__)

// 3 from 5.
#define TAKE_MIDDLE_THREE(K01, K02, K03, K04, K05) \
                         K02, K03, K04
#define TMT(...) TAKE_MIDDLE_THREE(__VA_ARGS__)

// Take a 3x10 and trim it down to fit.
// drop the bottom corners of each hand.
// so inner index and bottom pinky are dropped/lost.

// Take the middle thumbs out of the Ergo 6.

#define Base_2_3x3_2_2(                                                   \
                     K01, K02, K03, K04, K05, \
                     K06, K07, K08, K09, K0A,                           \
                     K11, K12, K13, K14, K15,                           \
                     K16, K17, K18, K19, K1A,                           \
                     K21, K22, K23, K24, K25,                           \
                     K26, K27, K28, K29, K2A)                           \
  LAYOUT_VARG(                                                          \
              MOD_ROW(ROW1L)(K01, K02, K03, K04, K05),                  \
              MOD_ROW(ROW1R)(K06, K07, K08, K09, K0A),                  \
                                                                        \
              MOD_ROW(ROW2L)(K11, K12, K13, K14, K15),                  \
              MOD_ROW(ROW2R)(K16, K17, K18, K19, K1A),                  \
                                                                        \
              TMT(MOD_ROW(ROW3L)(K21, K22, K23, K24, K25)), \
              TMT(MOD_ROW(ROW3R)(K26, K27, K28, K29, K2A)),  \
              MAP_CHUNK(___4_ERGO_THUMBS)             \
                                                                        )

#define Transient_2_3x3_2_2(                                              \
                          K01, K02, K03, K04, K05,                      \
                          K07, K08, K09, K0A, K0B,                      \
                          K11, K12, K13, K14, K15,                      \
                          K17, K18, K19, K1A, K1B,                      \
                          K21, K22, K23, K24, K25,                      \
                          K27, K28, K29, K2A, K2B                       \
                                                                        ) \
  LAYOUT_VARG(                                                          \
              K01, K02, K03, K04, K05,                                 \
              K07, K08, K09, K0A, K0B,                                 \
              K11, K12, K13, K14, K15,                                 \
              K17, K18, K19, K1A, K1B,                                 \
                   K22, K23, K24,                                      \
                   K28, K29, K2A,                                      \
              MAP_CHUNK(___4_ERGO_THUMBS)            \
                                                                        )

// Take a 3x10 and trim it down to fit.
// drop the bottom corners of each hand.
// so inner index and bottom pinky are dropped/lost.

// Take the middle thumbs out of the Ergo 6.

#define Base_3x5_2(                                                   \
                     K01, K02, K03, K04, K05, \
                     K06, K07, K08, K09, K0A,                           \
                     K11, K12, K13, K14, K15,                           \
                     K16, K17, K18, K19, K1A,                           \
                     K21, K22, K23, K24, K25,                           \
                     K26, K27, K28, K29, K2A)                           \
  LAYOUT_VARG(                                                          \
              MOD_ROW(ROW1L)(K01, K02, K03, K04, K05),                  \
              MOD_ROW(ROW1R)(K06, K07, K08, K09, K0A),                  \
                                                                        \
              MOD_ROW(ROW2L)(K11, K12, K13, K14, K15),                  \
              MOD_ROW(ROW2R)(K16, K17, K18, K19, K1A),                  \
                                                                        \
              MOD_ROW(ROW3L)(K21, K22, K23, K24, K25), \
              MOD_ROW(ROW3R)(K26, K27, K28, K29, K2A),  \
              MAP_CHUNK(___4_ERGO_THUMBS)             \
                                                                        )

#define Transient_3x5_2(                                              \
                          K01, K02, K03, K04, K05,                      \
                          K07, K08, K09, K0A, K0B,                      \
                          K11, K12, K13, K14, K15,                      \
                          K17, K18, K19, K1A, K1B,                      \
                          K21, K22, K23, K24, K25,                      \
                          K27, K28, K29, K2A, K2B                       \
                                                                        ) \
  LAYOUT_VARG(                                                          \
              K01, K02, K03, K04, K05,                                 \
              K07, K08, K09, K0A, K0B,                                 \
              K11, K12, K13, K14, K15,                                 \
              K17, K18, K19, K1A, K1B,                                 \
              K21, K22, K23, K24, K25,                                 \
              K27, K28, K29, K2A, K2B,                                 \
              MAP_CHUNK(___4_ERGO_THUMBS)            \
                                                                        )

// Take a 3x10 and rearrange it and fill in to fit.

// Left to right.
// top row,
// home Row
// bottom row
// east west fillers.
// thumbs.
#define SVALBOARD_LAYOUT_PRETTY(                           \
                     K01, K02, K03, K04, K05,              \
                     K06, K07, K08, K09, K0A,              \
\
                     K11, K12, K13, K14, K15,              \
                     K16, K17, K18, K19, K1A,              \
\
                     K21, K22, K23, K24, K25,              \
                     K26, K27, K28, K29, K2A,              \
\
                     EW1, EW2, EW3, EW4, EW5,              \
                     EW6, EW7, EW8, EW9, EWA,              \
\
                     TH1, TH2, TH3, TH4, TH5, TH6,         \
                     TH7, TH8, TH9, THA, THB, THC          \
                                                           )\
  LAYOUT( \
             /*Center   North  East   South    West*/  \
        /*index*/ K17,  K07,   EW6,   K27,     K16,  \
        /*R2*/    K18,  K08,   EW7,   K28,     K06,  \
        /*R3*/    K19,  K09,   EW8,   K29,     K26,  \
        /*pinky*/ K1A,  K0A,   EW9,   K2A,     EWA,  \
  \
        /*index*/ K14,  K04,   K15,   K24,     EW5,  \
        /*L2*/    K13,  K03,   K05,   K23,     EW4,  \
        /*L3*/    K12,  K02,   K25,   K22,     EW3,  \
        /*pinky*/ K11,  K01,   EW2,   K21,     EW1,  \
  \
        /*      Down Inner Upper   Outer Upper  Outer Lower  Pushthrough*/  \
        /*RT*/ THB,  TH9,  THC,    TH7,         THA,         TH8,  \
        /*LT*/ TH5,  TH1,  TH4,    TH3,         TH6,         TH2  \
    )

// Take a 3x10 and trim it down to fit.
// drop the bottom corners of each hand.
// so inner index and bottom pinky are dropped/lost.

// Take the middle thumbs out of the Ergo 6.

#define Base_5x4_6(                                                   \
                     K01, K02, K03, K04, K05, \
                     K06, K07, K08, K09, K0A,                           \
                     K11, K12, K13, K14, K15,                           \
                     K16, K17, K18, K19, K1A,                           \
                     K21, K22, K23, K24, K25,                           \
                     K26, K27, K28, K29, K2A)                           \
  LAYOUT_VARG(                                                          \
              MOD_ROW(ROW1L)(K01, K02, K03, K04, K05),                  \
              MOD_ROW(ROW1R)(K06, K07, K08, K09, K0A),                  \
                                                                        \
              MOD_ROW(ROW2L)(K11, K12, K13, K14, K15),                  \
              MOD_ROW(ROW2R)(K16, K17, K18, K19, K1A),                  \
                                                                        \
              MOD_ROW(ROW3L)(K21, K22, K23, K24, K25), \
              MOD_ROW(ROW3R)(K26, K27, K28, K29, K2A),  \
                                                                         \
              SVALBOARD_EAST_WEST_FILLER,                              \
              MAP_CHUNK(___SVALBOARD_THUMBS) \
                                                                        )

#define Transient_5x4_6(                                              \
                          K01, K02, K03, K04, K05,                      \
                          K07, K08, K09, K0A, K0B,                      \
                          K11, K12, K13, K14, K15,                      \
                          K17, K18, K19, K1A, K1B,                      \
                          K21, K22, K23, K24, K25,                      \
                          K27, K28, K29, K2A, K2B                       \
                                                                        ) \
  LAYOUT_VARG(                                                          \
              K01, K02, K03, K04, K05,                                 \
              K07, K08, K09, K0A, K0B,                                 \
              K11, K12, K13, K14, K15,                                 \
              K17, K18, K19, K1A, K1B,                                 \
              K21, K22, K23, K24, K24,                                 \
              K27, K28, K29, K2A, K2B,                                     \
              SVALBOARD_EAST_WEST_FILLER,   \
              MAP_CHUNK(___SVALBOARD_THUMBS) \
                                                                        )
