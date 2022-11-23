// Copyright 2022 KeyboardDweebs (@doesntfazer)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U


#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP1
#define SERIAL_USART_RX_PIN GP0

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define SERIAL_PIO_USE_PIO0

// #define SERIAL_USART_PIN_SWAP

#define DIRECT_PINS {{GP6,  GP5,  GP4,    GP3,    GP2}, \
                     {GP11, GP10, GP9,    GP8,    GP7}, \
                     {GP15, GP14, GP13,   GP12,   GP16}, \
                     {GP17, GP18, NO_PIN, NO_PIN, NO_PIN}}

#define DIRECT_PINS_RIGHT {{GP2, GP3, GP4, GP5, GP6}, \
                           {GP7, GP8, GP9, GP10, GP11}, \
                           {GP16, GP12, GP13, GP14, GP15}, \
                           {GP18, GP17, NO_PIN, NO_PIN, NO_PIN}}
