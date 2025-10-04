// Copyright 2025 Erik Peyronson @erikpeyronson
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define I2C_DRIVER I2CD1
#define OLED_IC OLED_IC_SH1106
#define OLED_COLUMN_OFFSET 2

#define OLED_DISPLAY_128X64
