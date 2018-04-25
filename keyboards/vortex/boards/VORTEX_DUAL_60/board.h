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
 * Setup for Vortex POK3R board.
 */

/*
 * Board identifier.
 */
#define BOARD_VORTEX_DUAL_60
#define BOARD_NAME                  "VORTEX_DUAL_60"

#define HT32F1655

#define FLASH_SIZE 0x20000

/*
 * I/O
 */

// outputs (rows are pulled low)
#define LINE_ROW1                   PAL_LINE(IOPORTD, 0)
#define LINE_ROW2                   PAL_LINE(IOPORTC, 5)
#define LINE_ROW3                   PAL_LINE(IOPORTA, 11)
#define LINE_ROW4                   PAL_LINE(IOPORTB, 3)
#define LINE_ROW5                   PAL_LINE(IOPORTA, 15)
#define LINE_ROW6                   PAL_LINE(IOPORTB, 4)
#define LINE_ROW7                   PAL_LINE(IOPORTB, 1)
#define LINE_ROW8                   PAL_LINE(IOPORTB, 5)
#define LINE_ROW9                   PAL_LINE(IOPORTC, 8)

// inputs (columns are sampled)
#define LINE_COL1                   PAL_LINE(IOPORTA, 3)
#define LINE_COL2                   PAL_LINE(IOPORTA, 4)
#define LINE_COL3                   PAL_LINE(IOPORTA, 5)
#define LINE_COL4                   PAL_LINE(IOPORTA, 6)
#define LINE_COL5                   PAL_LINE(IOPORTB, 11)
#define LINE_COL6                   PAL_LINE(IOPORTC, 13)
#define LINE_COL7                   PAL_LINE(IOPORTC, 14)
#define LINE_COL8                   PAL_LINE(IOPORTC, 15)

// USART (conflicts with LED matrix)
#define PAD_USART_TX                8

#define LINE_SEL1                   PAL_LINE(IOPORTA, 8)
#define LINE_SEL2                   PAL_LINE(IOPORTA, 9)

// SPI
#define LINE_SPI_SCK                PAL_LINE(IOPORTB, 7)
#define LINE_SPI_MOSI               PAL_LINE(IOPORTB, 8)
#define LINE_SPI_MISO               PAL_LINE(IOPORTB, 9)
#define LINE_SPI_CS                 PAL_LINE(IOPORTB, 10)

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
    K01, K02, K03, K04, K05, K06, K07, K08, K36, K37, K38, K39, K41, K40, /* 14 keys */ \
    K09, K10, K11, K12, K13, K14, K15, K16, K42, K43, K44, K45, K47,      /* 13 keys */ \
    K17, K18, K19, K20, K21, K22, K23, K24, K48, K49, K50, K51, K46, K52, /* 14 keys */ \
    K25, K63, K26, K27, K28, K29, K30, K31, K32, K54, K55, K56, K57, K58, /* 14 keys, 2 dnp */ \
    K33, K34, K35,                K53,                K59, K60, K61, K62, /* 8 keys */  \
                                                      S01, S02, S03, S04  /* dip switches */ \
) { \
    /*            COL1   COL2   COL3   COL4   COL5   COL6   COL7   COL8   */ \
    /* ROW1  */ { K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   }, \
    /* ROW2  */ { K33,   K34,   K35,   K36,   K37,   K38,   K39,   K40,   }, \
    /* ROW3  */ { K09,   K10,   K11,   K12,   K13,   K14,   K15,   K16,   }, \
    /* ROW4  */ { K63,   KC_NO, K41,   K42,   K43,   K44,   K45,   K46,   }, \
    /* ROW5  */ { K17,   K18,   K19,   K20,   K21,   K22,   K23,   K24,   }, \
    /* ROW6  */ { KC_NO, KC_NO, K47,   K48,   K49,   K50,   K51,   K52,   }, \
    /* ROW7  */ { K25,   K26,   K27,   K28,   K29,   K30,   K31,   K32,   }, \
    /* ROW8  */ { KC_NO, KC_NO, K53,   K54,   K55,   K56,   K57,   K58,   }, \
    /* ROW9  */ { S01,   S02,   S03,   K59,   K60,   K61,   S04,   K62,   }  \
}

#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e,   \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e,     \
      k30,    k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,     k3c,       \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,  KC_NO, \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#define LAYOUT_60_ansi_split_lshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e,   \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e,     \
     k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,     k3c,      \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,  KC_NO, \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#define LAYOUT_60_ansi_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e,   \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e,     \
     k30,    k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,   k3d,  \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30, KC_NO, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,  k3d, \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#define LAYOUT_60_ansi_split_lshift_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e,   \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e,     \
     k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,  k3d,  \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,   k3d,  \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#define LAYOUT_60_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
      k30,    k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,     k3c,       \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c  ,KC_NO, \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
    void uart_send(const char *str);
    void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
