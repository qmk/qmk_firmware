// Copyright 2023 Alabahuy (@Alabahuy)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define I2C_DRIVER I2CD2
#define I2C1_SDA_PIN GP26
#define I2C1_SCL_PIN GP27

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
