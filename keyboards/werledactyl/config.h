// Copyright 2024 TheWerle (@TheWerle)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
#define MASTER_LEFT

/* disable action features */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP7
#define SERIAL_USART_RX_PIN GP8
#define SERIAL_USART_PIN_SWAP

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
