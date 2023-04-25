// Copyright 2023 Noah Beidelman (@noahbei)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* maybe need this
#define I2C1_OPMODE	OPMODE_I2C
#define I2C1_CLOCK_SPEED 100000
#define I2C1_DUTY_CYCLE	STD_DUTY_CYCLE
*/

#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B6
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PIN B7
#define I2C1_SDA_PAL_MODE 1

//#define MY_I2C_ADDRESS (0x18 << 1)

#define OLED_TIMEOUT 180000


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
