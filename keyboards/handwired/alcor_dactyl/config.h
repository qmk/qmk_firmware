// Copyright 2022 Ethan (@rocketstrong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

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

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP10
#define SERIAL_USART_RX_PIN GP9
#define RGB_DI_PIN GP16
#define DRIVER_LED_TOTAL 2
#define RGB_MATRIX_SPLIT { 1, 1 }
#define RGBLED_NUM 1
#define EE_HANDS
