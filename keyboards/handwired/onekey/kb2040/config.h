// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define MATRIX_COL_PINS \
    { GP0, GP1, GP2, GP3, GP4, GP5 }
#define MATRIX_ROW_PINS \
    { GP6, GP7, GP8, GP9, GP27 }

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define RGB_DI_PIN GP27

// settings for the oled keyboard demo with Adafruit 0.91" OLED display on the Stemma QT port
#define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP12
#define I2C1_SCL_PIN GP13
