// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef CANCEL_BOOST
#    define PRODUCT      BASE_PRODUCT cancel boost
#    define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#    define MATRIX_COL_PINS { F4,F4,F5,F5, F6,F6,F7,F7,  B6,B6,B2,B2, B3,B3,B1,B1 }
#    define MATRIX_MUL_SEL  {  0, 1, 0, 1,  0, 1, 0, 1,   1, 0, 1, 0,  1, 0, 1, 0 }
/* use 74HC157: quadruple 2-line to 1-line data selectors / multiplexers */
#    define MATRIX_MUL_SELECT  B5 /* 74HC157 pin1:~A/B */
#else
#    define PRODUCT      BASE_PRODUCT boost
#endif

#define MATRIX_EXTENSION_74HC157 B5 /* 74HC157 pin1:~A/B */

// clang-format off

#define EXTENDED_MATRIX_ROW_PINS \
        (MCU_GPIO, D0, 4), \
        (MCU_GPIO, C0, 6), \
        (MCU_GPIO, D0, 7), \
        (MCU_GPIO, E0, 6), \
        (MCU_GPIO, B0, 4)
#define EXTENDED_MATRIX_COL_PINS \
        (MCU_GPIO_74HC157_A, F0, 4), \
        (MCU_GPIO_74HC157_B, F0, 4), \
        (MCU_GPIO_74HC157_A, F0, 5), \
        (MCU_GPIO_74HC157_B, F0, 5), \
        (MCU_GPIO_74HC157_A, F0, 6), \
        (MCU_GPIO_74HC157_B, F0, 6), \
        (MCU_GPIO_74HC157_A, F0, 7), \
        (MCU_GPIO_74HC157_B, F0, 7), \
        (MCU_GPIO_74HC157_B, B0, 6), \
        (MCU_GPIO_74HC157_A, B0, 6), \
        (MCU_GPIO_74HC157_B, B0, 2), \
        (MCU_GPIO_74HC157_A, B0, 2), \
        (MCU_GPIO_74HC157_B, B0, 3), \
        (MCU_GPIO_74HC157_A, B0, 3), \
        (MCU_GPIO_74HC157_B, B0, 1), \
        (MCU_GPIO_74HC157_A, B0, 1)

 /* #define EXTENDED_MATRIX_COL_PINS (MCU_GPIO_74HC157_A, F0, 4), (MCU_GPIO_74HC157_B, F0, 4), (MCU_GPIO_74HC157_A, F0, 5), (MCU_GPIO_74HC157_B, F0, 5), (MCU_GPIO_74HC157_A, F0, 6), (MCU_GPIO_74HC157_B, F0, 6), (MCU_GPIO_74HC157_A, F0, 7), (MCU_GPIO_74HC157_B, F0, 7), (MCU_GPIO_74HC157_B, B0, 6), (MCU_GPIO_74HC157_A, B0, 6), (MCU_GPIO_74HC157_B, B0, 2), (MCU_GPIO_74HC157_A, B0, 2), (MCU_GPIO_74HC157_B, B0, 3), (MCU_GPIO_74HC157_A, B0, 3), (MCU_GPIO_74HC157_B, B0, 1), (MCU_GPIO_74HC157_A, B0, 1) */
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (F0, 0xf0, MCU_GPIO_74HC157_A), \
      (F0, 0xf0, MCU_GPIO_74HC157_B), \
      (B0, 0x4e, MCU_GPIO_74HC157_B), \
      (B0, 0x4e, MCU_GPIO_74HC157_A) ),\
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

 /* #define EXTENDED_MATRIX_ROW_PINS (MCU_GPIO, D0, 4), (MCU_GPIO, C0, 6), (MCU_GPIO, D0, 7), (MCU_GPIO, E0, 6), (MCU_GPIO, B0, 4) */
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (D0, 0x90, MCU_GPIO), \
      (C0, 0x40, MCU_GPIO), \
      (E0, 0x40, MCU_GPIO), \
      (B0, 0x10, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (1, 0x40, 0x02), \
      (0, 0x80, 0x04), \
      (2, 0x40, 0x08), \
      (3, 0x10, 0x10) )

