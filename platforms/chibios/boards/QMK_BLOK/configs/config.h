// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifndef I2C_DRIVER
#    define I2C_DRIVER I2CD0
#endif
#ifndef I2C1_SDA_PIN
#    define I2C1_SDA_PIN D1
#endif
#ifndef I2C1_SCL_PIN
#    define I2C1_SCL_PIN D0
#endif

#ifndef RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#endif
#ifndef RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#endif
