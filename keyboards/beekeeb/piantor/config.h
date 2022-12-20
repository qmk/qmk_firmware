// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

#define DIRECT_PINS { \
    { GP5, GP4, GP11, GP15, GP3, GP2}, \
    { GP22, GP20, GP10, GP14, GP9, GP8}, \
    { GP21, GP19, GP6, GP7, GP13, GP12}, \
    { GP17, GP18, GP16, NO_PIN, NO_PIN, NO_PIN} \
}

#define DIRECT_PINS_RIGHT { \
    { GP22, GP21, GP2, GP5, GP8, GP11}, \
    { GP20, GP19, GP3, GP6, GP9, GP12}, \
    { GP18, GP17, GP4, GP7, GP10, GP13}, \
    { GP15, GP14, GP16, NO_PIN, NO_PIN, NO_PIN} \
}

#define BOOTMAGIC_LITE_ROW    0
#define BOOTMAGIC_LITE_COLUMN 5
