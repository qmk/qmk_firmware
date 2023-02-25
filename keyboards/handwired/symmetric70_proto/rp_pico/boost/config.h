// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// clang-format off

#ifdef CANCEL_BOOST
#    define MATRIX_COL_PINS { GP28, GP27, GP26, GP22, GP21, GP20, GP19, GP18,  GP10, GP9, GP8, GP7, GP6, GP3, GP2, GP1 }
#    define MATRIX_ROW_PINS { GP11, GP12, GP13, GP14, GP15 }
#endif

 /* #define MATRIX_COL_PINS { GP28, GP27, GP26, GP22, GP21, GP20, GP19, GP18, GP10, GP9, GP8, GP7, GP6, GP3, GP2, GP1 } */
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (GP0, 0x1c7c07ceU, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10000000U, 0x01U), \
      (0, 0x8000000U, 0x02U), \
      (0, 0x4000000U, 0x04U), \
      (0, 0x400000U, 0x08U), \
      (0, 0x200000U, 0x10U), \
      (0, 0x100000U, 0x20U), \
      (0, 0x80000U, 0x40U), \
      (0, 0x40000U, 0x80U), \
      (0, 0x400U, 0x100U), \
      (0, 0x200U, 0x200U), \
      (0, 0x100U, 0x400U), \
      (0, 0x80U, 0x800U), \
      (0, 0x40U, 0x1000U), \
      (0, 0x08U, 0x2000U), \
      (0, 0x04U, 0x4000U), \
      (0, 0x02U, 0x8000U) )

 /* #define MATRIX_ROW_PINS { GP11, GP12, GP13, GP14, GP15 } */
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (GP0, 0xf800U, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x800U, 0x01U), \
      (0, 0x1000U, 0x02U), \
      (0, 0x2000U, 0x04U), \
      (0, 0x4000U, 0x08U), \
      (0, 0x8000U, 0x10U) )
