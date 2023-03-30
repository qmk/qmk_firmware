/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_STDIO_DRIVER_H
#define _PICO_STDIO_DRIVER_H

#include "pico/stdio.h"

struct stdio_driver {
    void (*out_chars)(const char *buf, int len);
    void (*out_flush)(void);
    int (*in_chars)(char *buf, int len);
    void (*set_chars_available_callback)(void (*fn)(void*), void *param);
    stdio_driver_t *next;
#if PICO_STDIO_ENABLE_CRLF_SUPPORT
    bool last_ended_with_cr;
    bool crlf_enabled;
#endif
};

#endif
