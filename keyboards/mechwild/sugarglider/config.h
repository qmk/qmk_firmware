// Copyright 2022 Kyle McCreery
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6D77 // mw = "MechWild"
#define PRODUCT_ID      0x1710
#define DEVICE_VER      0x0001
#define MANUFACTURER    MechWild
#define PRODUCT         SugarGlider

/* Matrix COL and ROW definitions */
#define MATRIX_ROWS 9
#define MATRIX_COLS 6


/* status light pins */
#define LED_NUM_LOCK_PIN B12
#define LED_CAPS_LOCK_PIN B13
#define LED_SCROLL_LOCK_PIN B14
#define LED_PIN_ON_STATE 0