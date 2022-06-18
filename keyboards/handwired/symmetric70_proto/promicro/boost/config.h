// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define PRODUCT      BASE_PRODUCT boost

//#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
//#define MATRIX_COL_PINS { Fa4,Fb4,Fa5,Fb5, Fa6,Fb6,Fa7,Fb7,  Ba6,Bb6,Ba2,Bb2, Ba3,Bb3,Ba1,Bb1 }

#define MATRIX_MUL_SEL  {  0, 1, 0, 1,  0, 1, 0, 1,   1, 0, 1, 0,  1, 0, 1, 0 }
/* use 74HC157: quadruple 2-line to 1-line data selectors / multiplexers */
#define MATRIX_MUL_SELECT  B5 /* 74HC157 pin1:~A/B */

 /* #define MATRIX_COL_PINS { Fa4,Fb4,Fa5,Fb5, Fa6,Fb6,Fa7,Fb7, Ba6,Bb6,Ba2,Bb2, Ba3,Bb3,Ba1,Bb1 } */
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask> [, <dev>] ), ... ) */ \
    ( (F0, 0xf0, 0),   \
      (F0, 0xf0, 1),   \
      (B0, 0x4e, 0),   \
      (B0, 0x4e, 1) ), \
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (1, 0x10, 0x02), \
      (0, 0x20, 0x04), \
      (1, 0x20, 0x08), \
      (0, 0x40, 0x10), \
      (1, 0x40, 0x20), \
      (0, 0x80, 0x40), \
      (1, 0x80, 0x80), \
      (2, 0x40, 0x100), \
      (3, 0x40, 0x200), \
      (2, 0x04, 0x400), \
      (3, 0x04, 0x800), \
      (2, 0x08, 0x1000), \
      (3, 0x08, 0x2000), \
      (2, 0x02, 0x4000), \
      (3, 0x02, 0x8000) )

 /* #define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 } */
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask> [, <dev>] ), ... ) */ \
    ( (D0, 0x90), \
      (C0, 0x40), \
      (E0, 0x40), \
      (B0, 0x10) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (1, 0x40, 0x02), \
      (0, 0x80, 0x04), \
      (2, 0x40, 0x08), \
      (3, 0x10, 0x10) )

