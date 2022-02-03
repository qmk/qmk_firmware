// Copyright 2021 Ll3macorn (@ll3macorn)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x3728
#define PRODUCT_ID      0x2949
#define DEVICE_VER      0x0001
#define MANUFACTURER    Ll3macorn
#define PRODUCT         BongoPad

/* bootmagic */
#define BOOTMAGIC_LITE_ROW 1
#define BOOTMAGIC_LITE_COLUMN 0

/* rgb underglow */
#define RGB_DI_PIN E6
#define RGBLED_NUM 6

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { F7, D7, C6, D4 }
#define MATRIX_COL_PINS { F4, F5, F6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* encoders */
#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { B3 }

/* misc */
#define LAYER_STATE_8BIT
#define NO_ACTION_TAPPING
