// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

/*
 * enable reactive animations
 */
#define RGB_MATRIX_KEYPRESSES

/*
 * I2C address is set by IS31FL3731 AD pin connected to ground
 */
#define IS31FL3731_I2C_ADDRESS_1 0b1110100

/*
 * The RP2040 has two I2C peripherals; I2C0 must be used with GPIO 4
 * and 5 which on the Keybow 2040 are wired up to the IS31FL3731.
 */
#define I2C_DRIVER I2CD0

/*
 * I2C1 here refers to the board's / QMK's first (and only) I2C
 * peripheral, not to the RP2040's second I2C peripheral.
 */
#define I2C1_SDA_PIN GP4
#define I2C1_SCL_PIN GP5
#define I2C1_CLOCK_SPEED 100000
