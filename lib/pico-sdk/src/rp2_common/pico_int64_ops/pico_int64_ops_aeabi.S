/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

.syntax unified
.cpu cortex-m0plus
.thumb

#include "pico/asm_helper.S"

.macro int64_section name
#if PICO_INT64_OPS_IN_RAM
.section RAM_SECTION_NAME(\name), "ax"
#else
.section SECTION_NAME(\name), "ax"
#endif
.endm

int64_section __aeabi_lmul

wrapper_func __aeabi_lmul
    muls   r1, r2
    muls   r3, r0
    adds   r1, r3
    mov    r12, r1
    lsrs   r1, r2, #16
    uxth   r3, r0
    muls   r3, r1
    push   {r4}
    lsrs   r4, r0, #16
    muls   r1, r4
    uxth   r2, r2
    uxth   r0, r0
    muls   r0, r2
    muls   r2, r4
    lsls   r4, r3, #16
    lsrs   r3, #16
    adds   r0, r4
    pop    {r4}
    adcs   r1, r3
    lsls   r3, r2, #16
    lsrs   r2, #16
    adds   r0, r3
    adcs   r1, r2
    add    r1, r12
    bx lr
