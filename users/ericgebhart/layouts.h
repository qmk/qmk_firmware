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

#include "core_keysets.h"
#include "mod_layer.h"
#include "edge_keys.h"

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
/*                                                                */
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

/* Actually, because of Bepo, each keyboard currently requires four of */
/* these macros. One for Qwerty, One for foreign layouts on bepo like */
/* dvorak and beakl on bepo instead of on Qwerty. Then another for the Bepo */
/* layout because unlike the rest of the layouts Bepo doesn't fit in */
/* 3x10. It wants 3x12. So there are potentially 4 macros per keyboard here. */
/* XXXX_base, XXXX_base_bepo, XXXX_base_bepo6, The 4th macro */
/* is XXXXX_transient and generally works for all other */
/* non base layers.                                       */
/* The base and transient versions are all that is necessary, if bepo is */
/*   not needed. */


/* All layouts are relatively simple to make. */
/* The ROW macros add a universal mod layer so that mods can be defined once */
/* and used everywhere. No matter the keymap or layer. this allows actual maps */
/* like dvorak, qwerty, colemak, beakl, etc., to be defined simply. */


/* Additional, more complicated layouts can be found here.*/
/* examples can be found in crkbd/keymaps/ericgebhart */
/* examples can be found in kinesis/keymaps/ericgebhart */
/* examples can be found in ergodox/keymaps/ericgebhart */
/* examples can be found in montsinger/rebound/rev4/keymaps/ericgebhart */



/********************************************************************/
/* xiudi/xd75  - Ortholinear 5x15  */
/********************************************************************/
/// These first two base layout templates take sets of 5 keys, left and right.
// Using 4 sets allows for changing the number row if you have one.
// if you never change the number row, then use 3 sets of left and right.
// and define the number row here.
#define LAYOUT_5x15_base(                                         \
                         K01, K02, K03, K04, K05,                 \
                         K06, K07, K08, K09, K0A,                 \
                         K11, K12, K13, K14, K15,                 \
                         K16, K17, K18, K19, K1A,                 \
                         K21, K22, K23, K24, K25,                 \
                         K26, K27, K28, K29, K2A,                 \
                         K31, K32, K33, K34, K35,                 \
                         K36, K37, K38, K39, K3A)                 \
  LVARG_5x15(                                                     \
            ROW0_LEFT(K01, K02, K03, K04, K05), \
            ___3_MIDDLE_T___,                                           \
            ROW0_RIGHT(K06, K07, K08, K09, K0A),                        \
                                                                        \
            ROW1_LEFT(K11, K12, K13, K14, K15),                         \
            ___3_MIDDLE_1___,                                           \
            ROW1_RIGHT(K16, K17, K18, K19, K1A),                        \
                                                                        \
            ROW2_LEFT(K21, K22, K23, K24, K25),                         \
            ___3_MIDDLE_2___,                                           \
            ROW2_RIGHT(K26, K27, K28, K29, K2A),                        \
                                                                        \
            ROW3_LEFT(K31, K32, K33, K34, K35),                         \
            ___3_MIDDLE_3___,                                           \
            ROW3_RIGHT(K36, K37, K38, K39, K3A),                        \
            ___15_BOTTOM___                                             \
    )

#define LAYOUT_5x15_base_bepo(                                          \
                         K01, K02, K03, K04, K05,                       \
                         K06, K07, K08, K09, K0A,                       \
                         K11, K12, K13, K14, K15,                       \
                         K16, K17, K18, K19, K1A,                       \
                         K21, K22, K23, K24, K25,                   \
                         K26, K27, K28, K29, K2A,                   \
                         K31, K32, K33, K34, K35,                   \
                         K36, K37, K38, K39, K3A)                   \
  LVARG_5x15(                                                           \
             ROW0_LEFT_BP(K01, K02, K03, K04, K05),                   \
             ___3_MIDDLE_T___,                                          \
             ROW0_RIGHT_BP(K06, K07, K08, K09, K0A),                    \
                                                                        \
             ROW1_LEFT_BP(K11, K12, K13, K14, K15),                     \
             ___3_MIDDLE_1_BP___,                                       \
             ROW1_RIGHT_BP(K16, K17, K18, K19, K1A),                    \
                                                                        \
             ROW2_LEFT_BP(K21, K22, K23, K24, K25),                     \
             ___3_MIDDLE_2_BP___,                                       \
             ROW2_RIGHT_BP(K26, K27, K28, K29, K2A),                    \
                                                                        \
             ROW3_LEFT_BP(K31, K32, K33, K34, K35),                     \
             ___3_MIDDLE_3_BP___,                                       \
             ROW3_RIGHT_BP(K36, K37, K38, K39, K3A),                    \
             ___15_BOTTOM_BP___                                         \
                                                                        )

// Just for bepo because it's a 3x6 matrix on each side.
// So 3 pairs of 6 keys, left and right.
#define Layout_5x15_base_bepo6(                                         \
                               K01, K02, K03, K04, K05, K06,            \
                               K07, K08, K09, K0A, K0B, K0C,            \
                               K11, K12, K13, K14, K15, K16,            \
                               K17, K18, K19, K1A, K1B, K1C,            \
                               K21, K22, K23, K24, K25, K26,            \
                               K27, K28, K29, K2A, K2B, K2C             \
                                                   )                    \
     LVARG_5x15(                                                        \
                ___15_B_SYMB___,                                  \
                ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),            \
                ___3_MIDDLE_1_BP___,                                    \
                ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),           \
                                                                        \
                ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),            \
                ___3_MIDDLE_2___,                                       \
                ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),           \
                                                                        \
                ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),            \
                ___3_MIDDLE_3___,                                       \
                ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),           \
                ___15_BOTTOM_BP___                                      \
                                                                        )

     // 4  rows of 12. 3 columns transparent in the middle.
#define LAYOUT_5x15_transient(                                          \
                              K01, K02, K03, K04, K05, K06,             \
                              K07, K08, K09, K0A, K0B, K0C,           \
                              K11, K12, K13, K14, K15, K16,             \
                              K17, K18, K19, K1A, K1B, K1C,             \
                              K21, K22, K23, K24, K25, K26,             \
                              K27, K28, K29, K2A, K2B, K2C,             \
                              K31, K32, K33, K34, K35, K36,             \
                              K37, K38, K39, K3A, K3B, K3C              \
                                                                        ) \
     LVARG_5x15(                                                  \
                K01, K02, K03, K04, K05, K06,                           \
                ___3___,                                                \
                K07, K08, K09, K0A, K0B, K0C,                           \
                K11, K12, K13, K14, K15, K16,                           \
                ___3___,                                                \
                K17, K18, K19, K1A, K1B, K1C,                           \
                K21, K22, K23, K24, K25, K26,                           \
                ___3___,                                                \
                K27, K28, K29, K2A, K2B, K2C,                           \
                K31, K32, K33, K34, K35, K36,                           \
                ___3___,                                                \
                K37, K38, K39, K3A, K3B, K3C,                           \
                ___15___)                                               \

#define BASE_5x15(...)       LAYOUT_5x15_base(__VA_ARGS__)
#define BASE_5x15_bepo(...)  LAYOUT_5x15_base_bepo(__VA_ARGS__)
#define BASE_5x15_bepo6(...) LAYOUT_5x15_base_bepo6(__VA_ARGS__)
#define TRANSIENT_5x15(...)  LAYOUT_5x15_transient(__VA_ARGS__)

/********************************************************************/


/********************************************************************/
/* viterbi  - Ortholinear 5x14  */
/********************************************************************/
#define LAYOUT_5x14_base(                                               \
                         K01, K02, K03, K04, K05,                       \
                         K06, K07, K08, K09, K0A,                       \
                         K11, K12, K13, K14, K15,                       \
                         K16, K17, K18, K19, K1A,                       \
                         K21, K22, K23, K24, K25,                       \
                         K26, K27, K28, K29, K2A,                       \
                         K31, K32, K33, K34, K35,                       \
                         K36, K37, K38, K39, K3A)                       \
  LVARG_5x14(                                                           \
             ROW0_LEFT(K01, K02, K03, K04, K05),                        \
             ___2_MIDDLE_T___,                                          \
             ROW0_RIGHT(K06, K07, K08, K09, K0A),                       \
                                                                        \
             ROW1_LEFT(K11, K12, K13, K14, K15),                        \
             ___2_MIDDLE_1___,                                          \
             ROW1_RIGHT(K16, K17, K18, K19, K1A),                       \
                                                                        \
             ROW2_LEFT(K21, K22, K23, K24, K25),                        \
             ___2_MIDDLE_2___,                                          \
             ROW2_RIGHT(K26, K27, K28, K29, K2A),                       \
                                                                        \
             ROW3_LEFT(K31, K32, K33, K34, K35),                        \
             ___2_MIDDLE_3___,                                          \
             ROW3_RIGHT(K36, K37, K38, K39, K3A),                       \
             ___14_BOTTOM___                                            \
                                                                        )

#define LAYOUT_5x14_base_bepo(                                          \
                              K01, K02, K03, K04, K05,                  \
                              K06, K07, K08, K09, K0A,                  \
                              K11, K12, K13, K14, K15,                  \
                              K16, K17, K18, K19, K1A,                  \
                              K21, K22, K23, K24, K25,                  \
                              K26, K27, K28, K29, K2A,                  \
                              K31, K32, K33, K34, K35,                  \
                              K36, K37, K38, K39, K3A)                  \
  LVARG_5x14(                                                           \
            ROW0_LEFT_BP(K01, K02, K03, K04, K05),                      \
            ___2_MIDDLE_T___,                                           \
            ROW0_RIGHT_BP(K06, K07, K08, K09, K0A),                     \
                                                                        \
            ROW1_LEFT_BP(K11, K12, K13, K14, K15),                      \
            ___2_MIDDLE_1_BP___,                                        \
            ROW1_RIGHT_BP(K16, K17, K18, K19, K1A),                     \
                                                                        \
            ROW2_LEFT_BP(K21, K22, K23, K24, K25),                      \
            ___2_MIDDLE_2_BP___,                                        \
            ROW2_RIGHT_BP(K26, K27, K28, K29, K2A),                     \
                                                                        \
            ROW3_LEFT_BP(K31, K32, K33, K34, K35),                      \
            ___2_MIDDLE_3_BP___,                                        \
            ROW3_RIGHT_BP(K36, K37, K38, K39, K3A),                     \
            ___14_BOTTOM_BP___                                          \
    )

  // Just for bepo because it's a 3x6 matrix on each side.
// So 3 pairs of 6 keys, left and right.
#define LAYOUT_5x14_base_bepo6(                                 \
                               K01, K02, K03, K04, K05, K06,    \
                               K07, K08, K09, K0A, K0B, K0C,    \
                               K11, K12, K13, K14, K15, K16,    \
                               K17, K18, K19, K1A, K1B, K1C,        \
                               K21, K22, K23, K24, K25, K26,        \
                               K27, K28, K29, K2A, K2B, K2C             \
                                                   )                    \
  LVARG_5x14(                                                           \
             ___14_B_SYMB___,                                           \
             ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),               \
             ___2_MIDDLE_1_BP___,                                       \
             ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),              \
                                                                        \
             ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),               \
             ___2_MIDDLE_2___,                                          \
             ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),              \
                                                                        \
             ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),               \
             ___2_MIDDLE_3___,                                          \
             ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),              \
             ___14_BOTTOM_BP___                                         \
                                                                        )

// 4  rows of 12. 2 columns transparent in the middle.
#define LAYOUT_5x14_transient(                                          \
                              K01, K02, K03, K04, K05, K06,             \
                              K07, K08, K09, K0A, K0B, K0C,             \
                              K11, K12, K13, K14, K15, K16,             \
                              K17, K18, K19, K1A, K1B, K1C,             \
                              K21, K22, K23, K24, K25, K26,             \
                              K27, K28, K29, K2A, K2B, K2C,             \
                              K31, K32, K33, K34, K35, K36,             \
                              K37, K38, K39, K3A, K3B, K3C              \
                                                                        ) \
  LVARG_5x14(                                                           \
             K01, K02, K03, K04, K05, K06,                              \
             ___2___,                                                   \
             K07, K08, K09, K0A, K0B, K0C,                              \
             K11, K12, K13, K14, K15, K16,                              \
             ___2___,                                                   \
             K17, K18, K19, K1A, K1B, K1C,                              \
             K21, K22, K23, K24, K25, K26,                              \
             ___2___,                                                   \
             K27, K28, K29, K2A, K2B, K2C,                              \
             K31, K32, K33, K34, K35, K36,                              \
             ___2___,                                                   \
             K37, K38, K39, K3A, K3B, K3C,                              \
             ___14___                                                   \
                                                                        ) \

#define BASE_5x14(...)       LAYOUT_5x14_base(__VA_ARGS__)
#define BASE_5x14_bepo(...)  LAYOUT_5x14_base_bepo(__VA_ARGS__)
#define BASE_5x14_bepo6(...) LAYOUT_5x14_base_bepo6(__VA_ARGS__)
#define TRANSIENT_5x14(...)  LAYOUT_5x14_transient(__VA_ARGS__)

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
             ROW1_LEFT(K01, K02, K03, K04, K05),                  \
             ROW1_RIGHT(K06, K07, K08, K09, K0A),                 \
                                                                  \
             ROW2_LEFT(K11, K12, K13, K14, K15),                  \
             ROW2_RIGHT(K16, K17, K18, K19, K1A),                 \
                                                                  \
             ROW3_LEFT(K21, K22, K23, K24, K25),                  \
             ROW3_RIGHT(K26, K27, K28, K29, K2A),                 \
                                                                        \
             ___12_BOTTOM___                                            \
                                                                  )

#define LAYOUT_4x12_base_bepo(                                          \
                              K01, K02, K03, K04, K05,                  \
                              K06, K07, K08, K09, K0A,                  \
                              K11, K12, K13, K14, K15,                  \
                              K16, K17, K18, K19, K1A,                  \
                              K21, K22, K23, K24, K25,                  \
                              K26, K27, K28, K29, K2A                  \
                                                                        ) \
     LVARG_4x12(                                                  \
                ROW1_LEFT_BP(K01, K02, K03, K04, K05),              \
                ROW1_RIGHT_BP(K06, K07, K08, K09, K0A),             \
                                                                    \
                ROW2_LEFT_BP(K11, K12, K13, K14, K15),              \
                ROW2_RIGHT_BP(K16, K17, K18, K19, K1A),             \
                                                                        \
                ROW3_LEFT_BP(K21, K22, K23, K24, K25),                    \
                ROW3_RIGHT_BP(K26, K27, K28, K29, K2A),                 \
                                                                        \
                ___12_BOTTOM_BP___                                      \
                                                                  )

     // Just for bepo because it's a 3x6 matrix on each side.
     // So 3 pairs of 6 keys, left and right.
#define Layout_4x12_base_bepo6(                                 \
                               K01, K02, K03, K04, K05, K06,    \
                               K07, K08, K09, K0A, K0B, K0C,    \
                               K11, K12, K13, K14, K15, K16,           \
                               K17, K18, K19, K1A, K1B, K1C,           \
                               K21, K22, K23, K24, K25, K26,           \
                               K27, K28, K29, K2A, K2B, K2C             \
                                                                           ) \
     LVARG_4x12(                                                        \
                ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),            \
                ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),           \
                                                                        \
                ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),            \
                ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),           \
                                                                        \
                ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),            \
                ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),           \
                ___12_BOTTOM_BP___                                      \
                                                                        )

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
             ___12___)                                                  \

#define BASE_4x12(...)       LAYOUT_4x12_base(__VA_ARGS__)
#define BASE_4x12_bepo(...)  LAYOUT_4x12_base_bepo(__VA_ARGS__)
#define BASE_4x12_bepo6(...) LAYOUT_4x12_base_bepo6(__VA_ARGS__)
#define TRANSIENT_4x12(...)  LAYOUT_4x12_transient(__VA_ARGS__)

/********************************************************************/
/* CRKBD  Corne                                                     */
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
              ROW1_LEFT(K01, K02, K03, K04, K05),                       \
              ROW1_RIGHT(K06, K07, K08, K09, K0A),                      \
                                                                        \
              ROW2_LEFT(K11, K12, K13, K14, K15),                       \
              ROW2_RIGHT(K16, K17, K18, K19, K1A),                      \
                                                                        \
              ROW3_LEFT(K21, K22, K23, K24, K25),                       \
              ROW3_RIGHT(K26, K27, K28, K29, K2A),                      \
              ___6_ERGO_THUMBS___                                       \
                                                                        )

// So we can have different transient layers for symbols and numbers on bepo.
// for layouts like dvorak on bepo.
#define Base_bepo_3x6_3(                                                \
                        K01, K02, K03, K04, K05,                        \
                        K06, K07, K08, K09, K0A,                        \
                        K11, K12, K13, K14, K15,                        \
                        K16, K17, K18, K19, K1A,                        \
                        K21, K22, K23, K24, K25,                        \
                        K26, K27, K28, K29, K2A                         \
                                                                        ) \
  LAYOUT_VARG(                                                          \
              ROW1_LEFT_BP(K01, K02, K03, K04, K05),                    \
              ROW1_RIGHT_BP(K06, K07, K08, K09, K0A),                   \
                                                                        \
              ROW2_LEFT_BP(K11, K12, K13, K14, K15),                    \
              ROW2_RIGHT_BP(K16, K17, K18, K19, K1A),                   \
                                                                        \
              ROW3_LEFT_BP(K21, K22, K23, K24, K25),                    \
              ROW3_RIGHT_BP(K26, K27, K28, K29, K2A),                   \
              ___6_ERGO_THUMBS_BP___                                    \
                                                                        )

// No room for pinkies.
// Just for bepo because it's a 3x6 matrix on each side.
// So 3 pairs of 6 keys, And we lose our left and right.
// Except it keeps the layer toggles along with the keycode
// on the bottom.
#define Base_bepo6_3x6_3(                                               \
                         K01, K02, K03, K04, K05, K06,                  \
                         K07, K08, K09, K0A, K0B, K0C,                  \
                         K11, K12, K13, K14, K15, K16,                  \
                         K17, K18, K19, K1A, K1B, K1C,                  \
                         K21, K22, K23, K24, K25, K26,                  \
                         K27, K28, K29, K2A, K2B, K2C                   \
                                                                        ) \
  LAYOUT_VARG(                                                          \
              ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),              \
              ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),             \
                                                                        \
              ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),              \
              ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),             \
                                                                        \
              ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),              \
              ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),             \
              ___6_ERGO_THUMBS_BP___                                    \
                                                                        )

// All we really need is to add the see through thumbs to the end.
#define Transient6_3x6_3(                                               \
                         K01, K02, K03, K04, K05, K06,                  \
                         K07, K08, K09, K0A, K0B, K0C,                  \
                         K11, K12, K13, K14, K15, K16,                  \
                         K17, K18, K19, K1A, K1B, K1C,                  \
                         K21, K22, K23, K24, K25, K26,                  \
                         K27, K28, K29, K2A, K2B, K2C                   \
                                                                        ) \
  LAYOUT_VARG(                                                          \
              K01, K02, K03, K04, K05, K06,                             \
              K07, K08, K09, K0A, K0B, K0C,                             \
              K11, K12, K13, K14, K15, K16,                             \
              K17, K18, K19, K1A, K1B, K1C,                             \
              K21, K22, K23, K24, K25, K26,                             \
              K27, K28, K29, K2A, K2B, K2C,                             \
              ___6___)

//---------------------------------------------------------
//  3x5
#define Base_3x5_3(                                                     \
                   K01, K02, K03, K04, K05,                             \
                   K06, K07, K08, K09, K0A,                             \
                   K11, K12, K13, K14, K15,                             \
                   K16, K17, K18, K19, K1A,                             \
                   K21, K22, K23, K24, K25,                             \
                   K26, K27, K28, K29, K2A)                             \
  LAYOUT_VARG(                                                          \
              ROW1_LEFT5(K01, K02, K03, K04, K05),                      \
              ROW1_RIGHT5(K06, K07, K08, K09, K0A),                     \
                                                                        \
              ROW2_LEFT5(K11, K12, K13, K14, K15),                      \
              ROW2_RIGHT5(K16, K17, K18, K19, K1A),                     \
                                                                        \
              ROW3_LEFT5(K21, K22, K23, K24, K25),                      \
              ROW3_RIGHT5(K26, K27, K28, K29, K2A),                     \
              ___6_ERGO_THUMBS___                                       \
                                                                        )

// So we can have different transient layers for symbols and numbers on bepo.
// for layouts like dvorak on bepo.
#define Base_bepo_3x5_3(                                                \
                        K01, K02, K03, K04, K05,                        \
                        K06, K07, K08, K09, K0A,                        \
                        K11, K12, K13, K14, K15,                        \
                        K16, K17, K18, K19, K1A,                        \
                        K21, K22, K23, K24, K25,                        \
                        K26, K27, K28, K29, K2A                         \
                                                                        ) \
  LAYOUT_VARG(                                                          \
              ROW1_LEFT5_BP(K01, K02, K03, K04, K05),                   \
              ROW1_RIGHT5_BP(K06, K07, K08, K09, K0A),                  \
                                                                        \
              ROW2_LEFT5_BP(K11, K12, K13, K14, K15),                   \
              ROW2_RIGHT5_BP(K16, K17, K18, K19, K1A),                  \
                                                                        \
              ROW3_LEFT5_BP(K21, K22, K23, K24, K25),                   \
              ROW3_RIGHT5_BP(K26, K27, K28, K29, K2A),                  \
              ___6_ERGO_THUMBS_BP___                                    \
                                                                        )

// All we really need is to add the see through thumbs to the end.
#define Transient5_3x5_3(                                               \
                         K01, K02, K03, K04, K05,                       \
                         K07, K08, K09, K0A, K0B,                       \
                         K11, K12, K13, K14, K15,                       \
                         K17, K18, K19, K1A, K1B,                       \
                         K21, K22, K23, K24, K25,                       \
                         K27, K28, K29, K2A, K2B                        \
                                                                    )   \
  LAYOUT_VARG(                                                          \
              K01, K02, K03, K04, K05,                               \
              K07, K08, K09, K0A, K0B,                              \
              K11, K12, K13, K14, K15,                              \
              K17, K18, K19, K1A, K1B,                              \
              K21, K22, K23, K24, K25,                              \
              K27, K28, K29, K2A, K2B,                          \
              ___6___)

/********************************************************************/
/* Kinesis*/
/********************************************************************/
// Basically an ergodox ez without the 3 pairs of middle keys.
// Left, right, bottom, and thumbs all stay the same.
#define Base_4x6_4_6(                                                   \
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
               ___KINTFUNC_L___, ___KINTFUNC_R___,                      \
               ROW0_LEFT(K01, K02, K03, K04, K05),                      \
               ROW0_RIGHT(K06, K07, K08, K09, K0A),                     \
                                                                        \
               ROW1_LEFT(K11, K12, K13, K14, K15),                      \
               ROW1_RIGHT(K16, K17, K18, K19, K1A),                     \
                                                                        \
               ROW2_LEFT(K21, K22, K23, K24, K25),                      \
               ROW2_RIGHT(K26, K27, K28, K29, K2A),                     \
                                                                        \
               ROW3_LEFT(K31, K32, K33, K34, K35),                      \
               ROW3_RIGHT(K36, K37, K38, K39, K3A),                     \
               ___4_BOTTOM_LEFT___, ___4_BOTTOM_RIGHT___,               \
               ___12_DOX_ALL_THUMBS___                                  \
                                                                        )

#define Base_bepo_4x6_4_6(                                              \
                          K01, K02, K03, K04, K05,                      \
                          K06, K07, K08, K09, K0A,                      \
                          K11, K12, K13, K14, K15,                      \
                          K16, K17, K18, K19, K1A,                      \
                          K21, K22, K23, K24, K25,                      \
                          K26, K27, K28, K29, K2A,                      \
                          K31, K32, K33, K34, K35,                      \
                          K36, K37, K38, K39, K3A                       \
                                                                       ) \
  LAYOUT_PVARG(                                                         \
               ___KINTFUNC_L___, ___KINTFUNC_R___,                      \
               ROW0_LEFT(K01, K02, K03, K04, K05),                      \
               ROW0_RIGHT(K06, K07, K08, K09, K0A),                     \
                                                                        \
               ROW1_LEFT(K11, K12, K13, K14, K15),                      \
               ROW1_RIGHT(K16, K17, K18, K19, K1A),                     \
                                                                        \
               ROW2_LEFT(K21, K22, K23, K24, K25),                      \
               ROW2_RIGHT(K26, K27, K28, K29, K2A),                     \
                                                                        \
               ROW3_LEFT(K31, K32, K33, K34, K35),                      \
               ROW3_RIGHT(K36, K37, K38, K39, K3A),                     \
               ___4_BOTTOM_LEFT___, ___4_BOTTOM_RIGHT___,               \
               ___12_DOX_ALL_THUMBS_BP___                               \
                                                                        )


// So 3 pairs of 6 keys, left and right.
#define Base_bepo6_4x6_4_6(                                             \
                           K01, K02, K03, K04, K05, K06,                \
                           K07, K08, K09, K0A, K0B, K0C,                \
                           K11, K12, K13, K14, K15, K16,                \
                           K17, K18, K19, K1A, K1B, K1C,                \
                           K21, K22, K23, K24, K25, K26,                \
                           K27, K28, K29, K2A, K2B, K2C                 \
                                                                   )    \
  LAYOUT_PVARG(                                                         \
               ___KINTFUNC_L___, ___KINTFUNC_R___,                      \
               ___6SYMBOL_BEPO_L___,                                    \
               ___6SYMBOL_BEPO_R___,                                    \
               ROW1_LEFT_BP6(K01, K02, K03, K04, K05, K06),             \
               ROW1_RIGHT_BP6(K07, K08, K09, K0A, K0B, K0C),            \
                                                                        \
               ROW2_LEFT_BP6(K11, K12, K13, K14, K15, K16),             \
               ROW2_RIGHT_BP6(K17, K18, K19, K1A, K1B, K1C),            \
                                                                        \
               ROW3_LEFT_BP6(K21, K22, K23, K24, K25, K26),             \
               ROW3_RIGHT_BP6(K27, K28, K29, K2A, K2B, K2C),            \
               ___4_BOTTOM_LEFT_BP___, ___4_BOTTOM_RIGHT_BP___,         \
               ___12_DOX_ALL_THUMBS_BP___                               \
                                                                        )

#define Transient6_4x6_4_6(                                             \
                           K01, K02, K03, K04, K05, K06,                \
                           K07, K08, K09, K0A, K0B, K0C,                \
                           K11, K12, K13, K14, K15, K16,                \
                           K17, K18, K19, K1A, K1B, K1C,                \
                           K21, K22, K23, K24, K25, K26,                \
                           K27, K28, K29, K2A, K2B, K2C,                \
                           K31, K32, K33, K34, K35, K36,                \
                           K37, K38, K39, K3A, K3B, K3C                 \
                                                                        ) \
  LAYOUT_PVARG(                                                         \
               ___KINTFUNC_L___, ___KINTFUNC_R___,                      \
               K01, K02, K03, K04, K05, K06,                            \
               K07, K08, K09, K0A, K0B, K0C,                            \
               K11, K12, K13, K14, K15, K16,                            \
               K17, K18, K19, K1A, K1B, K1C,                            \
               K21, K22, K23, K24, K25, K26,                            \
               K27, K28, K29, K2A, K2B, K2C,                            \
               K31, K32, K33, K34, K35, K36,                            \
               K37, K38, K39, K3A, K3B, K3C,                            \
               ___4___, ___4___,                                        \
               ___12___                                                 \
                                                                        )
