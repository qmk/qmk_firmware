// Copyright 2025 Jose M Zelezarof (git@zelezarof.ca)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

/* https://docs.qmk.fm/drivers/serial#usart-full-duplex */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_PIN_SWAP

/* https://docs.qmk.fm/platformdev_rp2040#double-tap */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
