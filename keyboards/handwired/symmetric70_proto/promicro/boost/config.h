// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef CANCEL_BOOST
#    define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#    define MATRIX_COL_PINS { F4,F4,F5,F5, F6,F6,F7,F7,  B6,B6,B2,B2, B3,B3,B1,B1 }
#    define MATRIX_MUL_SEL  {  0, 1, 0, 1,  0, 1, 0, 1,   1, 0, 1, 0,  1, 0, 1, 0 }
/* use 74HC157: quadruple 2-line to 1-line data selectors / multiplexers */
#    define MATRIX_MUL_SELECT  B5 /* 74HC157 pin1:~A/B */
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
    ( (F0, 0xf0U, MCU_GPIO_74HC157_A), \
      (F0, 0xf0U, MCU_GPIO_74HC157_B), \
      (B0, 0x4eU, MCU_GPIO_74HC157_B), \
      (B0, 0x4eU, MCU_GPIO_74HC157_A) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10U, 0x01U), \
      (1, 0x10U, 0x02U), \
      (0, 0x20U, 0x04U), \
      (1, 0x20U, 0x08U), \
      (0, 0x40U, 0x10U), \
      (1, 0x40U, 0x20U), \
      (0, 0x80U, 0x40U), \
      (1, 0x80U, 0x80U), \
      (2, 0x40U, 0x100U), \
      (3, 0x40U, 0x200U), \
      (2, 0x04U, 0x400U), \
      (3, 0x04U, 0x800U), \
      (2, 0x08U, 0x1000U), \
      (3, 0x08U, 0x2000U), \
      (2, 0x02U, 0x4000U), \
      (3, 0x02U, 0x8000U) )

 /* #define EXTENDED_MATRIX_ROW_PINS (MCU_GPIO, D0, 4), (MCU_GPIO, C0, 6), (MCU_GPIO, D0, 7), (MCU_GPIO, E0, 6), (MCU_GPIO, B0, 4) */
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (D0, 0x90U, MCU_GPIO), \
      (C0, 0x40U, MCU_GPIO), \
      (E0, 0x40U, MCU_GPIO), \
      (B0, 0x10U, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10U, 0x01U), \
      (1, 0x40U, 0x02U), \
      (0, 0x80U, 0x04U), \
      (2, 0x40U, 0x08U), \
      (3, 0x10U, 0x10U) )

