/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/uart.h"

int getchar_timeout_us(uint32_t timeout_us) {
    absolute_time_t t = make_timeout_time_us(timeout_us);
    while (!uart_is_readable(uart_default)) {
        if (absolute_time_diff_us(t, get_absolute_time()) > 0) {
            return STDIO_NO_INPUT;
        }
        sleep_ms(1);
    }
    return uart_getc(uart_default);
}

void stdio_uart_init() {
    uart_init(uart_default, 0);
}