/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

.syntax unified
.cpu cortex-m0plus
.thumb

// All unhandled USER IRQs fall through to here
.global __unhandled_user_irq
.thumb_func
__unhandled_user_irq:
    mrs  r0, ipsr
    subs r0, #16