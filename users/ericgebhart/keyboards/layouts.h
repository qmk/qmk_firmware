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

/******************************************************************/
/* This is where I put my Keyboard layouts.                       */
/* The mod layer can be modified in mod_layer.h                   */
/* can be applied here. The physical shape of the keyboard is     */
/* also accounted for here. This makes it very simple to add a    */
/* new keyboard and reuse all of my layouts and layers            */
/*                                                                */
/* With all of that in hand, we then create a LAYOUT wrapper      */
/* macro that takes a list of keys, to create a keyboard matrix   */
/* that fits the keyboard. Simple.                                */
/*                                                                */
/* The thumb keys, the bottom rows, etc.                          */
/*                                                                */
/* An attempt has been made to adapt the kinesis and ergodox      */
/* Thumb keys to the rectangular shapes of the xd75, viterbi,     */
/* and rebound.                                                   */
/******************************************************************/

/******************************************************************/
/* * The XD75 is a 5x15 Ortholinear matrix which means it has 3   */
/*       keys inbetween the usual left and right hand keys        */
/* * The Viterbi is a split 5x14 Ortholinear with 2 middle keys.  */
/* * The Ergodox is a split 5x14 Ortholinear with 2 middle keys,  */
/*       thumbkeys. It is missing middle keys on (home) row 3.    */
/* * The Corne is a split 3x12 with 6 thumb keys. It has no       */
/*       extra middle keys                                        */
/* * The Kinesis is 4x6 + 4 and 6 thumb keys.                     */
/* * My Dactyl is 4x6 + 5 and 8 thumb keys.                     */
/******************************************************************/


/******************************************************************/
/*   In all cases these keyboards are defined in a matrix which is */
/*   a set of rows. Maybe like so, or not.                         */
/*                                                                 */
/*   -------------------------|------------------------ */
/*   | Left0 | Numbers L | mid|dle0 | numbers R | Right0 | */
/*   | Left1 | keys0-5   | mid|dle1 | Keys6-10  | Right1 | */
/*   | Left2 | keys11-15 | mid|dle2 | Keys16-20 | Right2 | */
/*   | Left3 | keys20-25 | mid|dle3 | Keys25-30 | Right3 | */
/*   | Row5L                  |                    Row5R | */
/*   |               ThumbsL  | ThumbsR                  | */
/*   -------------------------|------------------------ */

/* Generally speaking, the keys on the right and left don't change. */
/* Neither does the bottom row or the thumbs. Frequently the numbers */
/* row is identical across layers. Mostly, we want our Base layers to */
/* be predctable.                                                     */


// Since our quirky block definitions are basically a list of comma separated
// arguments, we need a wrapper in order for these definitions to be
// expanded before being used as arguments to the LAYOUT_xxx macro.
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

/*
  | Left | Numbers L | middle | numbers R | Right |
  | Left | keys0-5   | middle | Keys6-10  | Right |
  | Left | keys11-15 | middle | Keys16-20 | Right |
  | Left | keys20-25 | middle | Keys25-30 | Right |
  |Row5L                                  Row5R   |
  |ThumbsL                                ThumbsR |
*/

/* Assuming that left, midddle, right, row5, and thumbs stay the same, */
/* numbers, no numbers, numbers never change, whatever.                */
/*   we can have a layout macro that takes a nice rectangle of keys.   */


/*Some keyboards need number rows, some don't. there is a setting for that */
/* the keymap will give number rows if BASE_NUMBER_ROW is defined.*/
/* in that case, the layout should take 4 rows of 10. */
/* If all the layouts you might ever want would have the same top row,*/
/* Then it could be defined like that here, and it could take 3x10.*/
/* All layouts are relatively simple to make. */
/* The ROW macros add a universal mod layer so that mods can be defined once */
/* and used everywhere. No matter the keymap or layer. this allows actual maps */
/* like dvorak, qwerty, colemak, beakl, etc., to be defined simply. */


/* Additional, usage examples can be found in keyboards.*/
/* crkbd/keymaps/ericgebhart */
/* kinesis/keymaps/ericgebhart */
/* ergodox_ez/keymaps/ericgebhart */
/* keebio/viterbi/keymaps/ericgebhart */
/* xiudi/xd75/keymaps/ericgebhart */
/* montsinger/rebound/rev4/keymaps/ericgebhart */



/********************************************************************/
/* xiudi/xd75  - Ortholinear 5x15  */
/********************************************************************/
/// These first two base layout templates take sets of 5 keys, left and right.
// Using 4 sets allows for changing the number row if you have one.
// if you never change the number row, then use 3 sets of left and right.
// and define the number row here.
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

// 4  rows of 12. 3 columns transparent in the middle.
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

/* This keyboard is a split, 4x6 + a row of 5 and a thumb cluster of 8. */
/* So We need Base_4x6_5_8 As a layout template to add mods, and fill */
/* out the perimeter keys of the keyboard. Perimeter keys being the */
/* number row, outside pinky keys, the 5th row, and thumbs. */

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


/********************************************************************/
/* Rebound 4 rows, 1x12, 3x13  */
/********************************************************************/
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
