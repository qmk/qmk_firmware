// Copyright 2022 ShandonCodes (@ShandonCodes)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x7877
#define PRODUCT_ID   0x0003
#define DEVICE_VER   0x0001
#define MANUFACTURER ShandonCodes
#define PRODUCT      Mino_Plus

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS {B9, B8, A2, A1, A0}
#define MATRIX_COL_PINS {B4, B3, A15, A10, A8, B14, B12, B10, A5, A4, A3, B0, A7, C15, B5}

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

