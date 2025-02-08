// Copyright 2025 inetd404 (@inetd404)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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

#define OLED_IC OLED_IC_SD1306
#define I2C_DRIVER I2CD1
#define OLED_DISPLAY_128X64
#define OLED_BRIGHTNESS 255 // Optional: sets brightness (0-255)
#define OLED_DISPLAY_ADDRESS 0x3D
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3
#define HAL_USE_I2C TRUE

