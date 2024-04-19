// Copyright 2024 x (@x)
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

#define SPLIT_CONNECTION_CHECK_TIMEOUT 500

#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.

#define SERIAL_USART_RX_PIN B7

// #define SERIAL_USART_PIN_SWAP      // Swap TX and RX pins if keyboard is master halve. (Only available on some MCUs)
// #define USART1_REMAP               // Remap USART TX and RX pins on STM32F103 MCUs, see table below.
// #define SERIAL_USART_TX_PAL_MODE 7

#define HAL_USE_SERIAL TRUE

#include_next <mcuconf.h>

#undef STM32_SERIAL_USE_USART3
#define STM32_SERIAL_USE_USART3 TRUE

#define SERIAL_USART_DRIVER SD3

//#define EE_HANDS
#define MASTER_RIGHT