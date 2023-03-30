/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _PICO_STDIO_H
#define _PICO_STDIO_H

typedef struct stdio_driver stdio_driver_t;

#define STDIO_ERROR -1
#define STDIO_NO_INPUT -2

static inline void stdio_usb_init() {}
void stdio_uart_init();
static inline void stdio_init_all() { stdio_uart_init(); }
static inline void stdio_filter_driver(stdio_driver_t *driver) {}
static inline void stdio_set_translate_crlf(stdio_driver_t *driver, bool enabled) {}
static inline bool stdio_usb_connected(void) { return true; }
int getchar_timeout_us(uint32_t timeout_us);
#define puts_raw puts
#define putchar_raw putchar

#endif
