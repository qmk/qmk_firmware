// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// clang-format off

#ifndef CANCEL_BOOST
// ignore symmetric70_proto/proton_c/proton_c.c:matrix_output_unselect_delay()
#    define MATRIX_IO_DELAY_DEFAULT
#endif

#ifdef CANCEL_BOOST
#    define PRODUCT      BASE_PRODUCT cancel boost
#    define MATRIX_COL_PINS { A2, A1, A0, B8, B13, B14, B15, B9, B0, B1, B2, B3, B4, B5, B6, B7 }
#    define MATRIX_ROW_PINS { A4, A5, A6, A7, A8 }
#else
#    define PRODUCT      BASE_PRODUCT boost
#endif

 /* #define MATRIX_COL_PINS { A2, A1, A0, B8, B13, B14, B15, B9, B0, B1, B2, B3, B4, B5, B6, B7 } */
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (A0, 0x07, MCU_GPIO),                           \
      (B0, 0xe3ff, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x04, 0x01), \
      (0, 0x02, 0x02), \
      (0, 0x01, 0x04), \
      (1, 0x100, 0x08), \
      (1, 0x2000, 0x10), \
      (1, 0x4000, 0x20), \
      (1, 0x8000, 0x40), \
      (1, 0x200, 0x80), \
      (1, 0x01, 0x100), \
      (1, 0x02, 0x200), \
      (1, 0x04, 0x400), \
      (1, 0x08, 0x800), \
      (1, 0x10, 0x1000), \
      (1, 0x20, 0x2000), \
      (1, 0x40, 0x4000), \
      (1, 0x80, 0x8000) )

 /* #define MATRIX_ROW_PINS { A4, A5, A6, A7, A8 } */
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (A0, 0x1f0, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (0, 0x20, 0x02), \
      (0, 0x40, 0x04), \
      (0, 0x80, 0x08), \
      (0, 0x100, 0x10) )

