/* Copyright 2020 David Philip Barr <@davidphilipbarr>
 * Copyright 2021 @filterpaper
 * SPDX-License-Identifier: GPL-2.0+
 */

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xC88B
#define PRODUCT_ID      0x3388
#define DEVICE_VER      0x0003
#define MANUFACTURER    DPB
#define PRODUCT         Macro3

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 4

/* key matrix pins */
#define DIRECT_PINS { \
    { D7, C6, D4, D1 }, \
    { B1, B4, B5, B3 }  \
}

#define ENCODERS_PAD_A { D2, F7 }
#define ENCODERS_PAD_B { D3, F6 }

#define UNUSED_PINS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

