// Copyright 2025 Jose M Zelezarof (git@zelezarof.ca)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

/* https://docs.qmk.fm/drivers/serial#usart-full-duplex */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_PIN_SWAP

/* https://docs.qmk.fm/features/split_keyboard#handedness-by-eeprom */
#define EE_HANDS

/* https://docs.qmk.fm/tap_hold#tapping-term */
#define TAPPING_TERM 250

/* https://docs.qmk.fm/tap_hold#flow-tap */
#define FLOW_TAP_TERM 150

/* https://docs.qmk.fm/tap_hold#chordal-hold */
#define CHORDAL_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

/* https://docs.qmk.fm/platformdev_rp2040#double-tap */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
