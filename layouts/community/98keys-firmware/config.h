// Copyright 2022 Supermagnum (@Supermagnum)
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
#define SPLIT_HAND_PIN GPIO26
#define SPLIT_HAND_PIN_LOW_IS_LEFT
#define USE_I2C
#define SPLIT_LED_STATE_ENABLE
#define DEBOUNCE 5
/SDA pin is GPIO0 , SLC pin is GPIO1
#define I2C1_SCL_PIN GPIO1
#define I2C1_SDA_PIN GPIO0
