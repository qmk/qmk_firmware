// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// clang-format off

#ifdef MATRIX_USE_OPENDRAIN_PULLUP
#    ifndef MATRIX_IO_DELAY_TYPE
#        define MATRIX_IO_DELAY_TYPE ADAPTIVE_TO_INPUT_WITH_TIME
#    endif
#    ifndef MATRIX_IO_DELAY
#        define MATRIX_IO_DELAY 6
#    endif
#endif

#ifdef CANCEL_BOOST
#    define PRODUCT      BASE_PRODUCT normal(non boost)
#    define MATRIX_COL_PINS { A2, A1, A0, B8, B13, B14, B15, B9, B0, B1, B2, B3, B4, B5, B6, B7 }
#    define MATRIX_ROW_PINS { A4, A5, A6, A7, A8 }
#else
#    define PRODUCT      BASE_PRODUCT boost
#endif

 /* #define MATRIX_COL_PINS { A2, A1, A0, B8, B13, B14, B15, B9, B0, B1, B2, B3, B4, B5, B6, B7 } */
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (A0, 0x07U, MCU_GPIO), \
      (B0, 0xe3ffU, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x04U, 0x01U), \
      (0, 0x02U, 0x02U), \
      (0, 0x01U, 0x04U), \
      (1, 0x100U, 0x08U), \
      (1, 0x2000U, 0x10U), \
      (1, 0x4000U, 0x20U), \
      (1, 0x8000U, 0x40U), \
      (1, 0x200U, 0x80U), \
      (1, 0x01U, 0x100U), \
      (1, 0x02U, 0x200U), \
      (1, 0x04U, 0x400U), \
      (1, 0x08U, 0x800U), \
      (1, 0x10U, 0x1000U), \
      (1, 0x20U, 0x2000U), \
      (1, 0x40U, 0x4000U), \
      (1, 0x80U, 0x8000U) )

 /* #define MATRIX_ROW_PINS { A4, A5, A6, A7, A8 } */
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (A0, 0x1f0U, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10U, 0x01U), \
      (0, 0x20U, 0x02U), \
      (0, 0x40U, 0x04U), \
      (0, 0x80U, 0x08U), \
      (0, 0x100U, 0x10U) )
