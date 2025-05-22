// Copyright 2024 QMK Collaborators (@qmk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND

#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP4
#define I2C1_SCL_PIN GP5
#define I2C1_CLOCK_SPEED 100000

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_SLEEP
#endif
