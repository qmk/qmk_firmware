// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifndef I2C_DRIVER
#    define I2C_DRIVER I2CD2
#endif
#ifndef I2C1_SDA_PIN
#    define I2C1_SDA_PIN 2U
#endif
#ifndef I2C1_SCL_PIN
#    define I2C1_SCL_PIN 3U
#endif

#ifndef RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#endif
#ifndef RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#endif
