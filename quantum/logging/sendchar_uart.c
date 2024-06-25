// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "sendchar.h"
#include "uart.h"

#ifndef SENDCHAR_BAUD_RATE
#    define SENDCHAR_BAUD_RATE 9600
#endif

int8_t sendchar(uint8_t c) {
    static bool s_init = false;
    if (!s_init) {
        uart_init(SENDCHAR_BAUD_RATE);
        s_init = true;
    }

    uart_write(c);
    return 0;
}
