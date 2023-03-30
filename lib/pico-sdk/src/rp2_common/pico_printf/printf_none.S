/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/asm_helper.S"
#include "pico/bootrom/sf_table.h"

.syntax unified
.cpu cortex-m0plus
.thumb

wrapper_func sprintf
wrapper_func snprintf
wrapper_func vsnprintf
regular_func printf_none_assert
    push {lr}       // keep stack trace sane
    ldr r0, =str
    bl panic

str:
    .asciz "printf support is disabled"