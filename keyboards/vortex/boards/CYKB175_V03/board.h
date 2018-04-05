/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef BOARD_H
#define BOARD_H

/*
 * Setup for Vortex Core board.
 */

/*
 * Board identifier.
 */
#define BOARD_CYKB175_V03
#define BOARD_NAME                  "CYKB175_V03"

#define HT32F1654

/*
 * I/O
 */

// outputs
#define LINE_COL1                   PAL_LINE(IOPORTA, 9)
#define LINE_COL2                   PAL_LINE(IOPORTA, 11)
#define LINE_COL3                   PAL_LINE(IOPORTB, 11)
#define LINE_COL4                   PAL_LINE(IOPORTD, 0)
#define LINE_COL5                   PAL_LINE(IOPORTB, 10)
#define LINE_COL6                   PAL_LINE(IOPORTA, 4)
#define LINE_COL7                   PAL_LINE(IOPORTA, 1)
#define LINE_COL8                   PAL_LINE(IOPORTA, 3)

// inputs
#define LINE_ROW1                   PAL_LINE(IOPORTA, 6)
#define LINE_ROW2                   PAL_LINE(IOPORTA, 7)
#define LINE_ROW3                   PAL_LINE(IOPORTC, 13)
#define LINE_ROW4                   PAL_LINE(IOPORTC, 11)
#define LINE_ROW5                   PAL_LINE(IOPORTC, 14)
#define LINE_ROW6                   PAL_LINE(IOPORTC, 15)
#define LINE_ROW7                   PAL_LINE(IOPORTC, 9)
#define LINE_ROW8                   PAL_LINE(IOPORTA, 5)

#define PAD_SPI_SCK                 7
#define PAD_SPI_MOSI                8
#define PAD_SPI_MISO                9
#define LINE_SPICS                  PAL_LINE(IOPORTB, 6)

#define LINE_TPPWR                  PAL_LINE(IOPORTA, 10)   // !
#define LINE_BLPWM                  PAL_LINE(IOPORTA, 14)   // !
#define LINE_BLEN                   PAL_LINE(IOPORTA, 15)   // !
#define LINE_PB0                    PAL_LINE(IOPORTB, 0)    // !
#define LINE_LED65                  PAL_LINE(IOPORTB, 1)    // !
#define LINE_TPREQ                  PAL_LINE(IOPORTC, 11)   // !

/*
 * Matrix map
 */

#define KEYMAP( \
    K62, K49, K63, K50, K64, K51, K65, K52, K66, K53, K67, K32, K55, /* 13 keys */ \
     K36,  K25, K37, K26, K38, K27, K39, K28, K40, K29, K41,   K43,  /* 12 keys */ \
     K12,   K17, K13, K18, K14, K19, K15, K20, K16, K30, K06, K110,  /* 12 keys */ \
     K59, K73, K112, K46,    K35,     K111,      K21, K11, K23, K31  /* 10 keys */ \
) { \
    /*           COL1   COL2   COL3   COL4   COL5   COL6   COL7   COL8   */ \
    /* ROW1 */ { K67,   K66,   K65,   K64,   K63,   K62,   KC_NO, KC_NO, }, \
    /* ROW2 */ { K31,   K53,   K52,   K51,   K50,   K49,   KC_NO, KC_NO, }, \
    /* ROW3 */ { K32,   K29,   K28,   K27,   K26,   K25,   KC_NO, KC_NO, }, \
    /* ROW4 */ { K41,   K40,   K39,   K38,   K37,   K36,   KC_NO, KC_NO, }, \
    /* ROW5 */ { K21,   K16,   K15,   K14,   K13,   K12,   KC_NO, KC_NO, }, \
    /* ROW6 */ { K06,   K30,   K20,   K19,   K18,   K17,   KC_NO, KC_NO, }, \
    /* ROW7 */ { K55,   K43,   K110,  K112,  KC_NO, K35,   K111,  KC_NO, }, \
    /* ROW8 */ { K73,   K59,   K46,   KC_NO, KC_NO, K11,   KC_NO, K23,   }  \
}

#define LAYOUT_core( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a,   k1b,     \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      \
     k30, k31, k32, k33,    k34,     k35,      k36, k37, k38, k39       \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a,   k1b,     \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,      \
     k30, k31, k32, k33,    k34,     k35,      k36, k37, k38, k39       \
)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
    void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
