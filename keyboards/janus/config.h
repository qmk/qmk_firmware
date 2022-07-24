// Copyright 2022 Steven Karrmann (@skarrmann)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER Steven Karrmann
#define PRODUCT      Janus

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS { GP26, GP27, GP28, GP29 }
#define MATRIX_COL_PINS { GP6, GP7, GP2, GP4, GP3 }
#define UNUSED_PINS { }

/* serial communication */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1