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

    wrapper_func __aeabi_dadd
    wrapper_func __aeabi_ddiv
    wrapper_func __aeabi_dmul
    wrapper_func __aeabi_drsub
    wrapper_func __aeabi_dsub
    wrapper_func __aeabi_cdcmpeq
    wrapper_func __aeabi_cdrcmple
    wrapper_func __aeabi_cdcmple
    wrapper_func __aeabi_dcmpeq
    wrapper_func __aeabi_dcmplt
    wrapper_func __aeabi_dcmple
    wrapper_func __aeabi_dcmpge
    wrapper_func __aeabi_dcmpgt
    wrapper_func __aeabi_dcmpun
    wrapper_func __aeabi_i2d
    wrapper_func __aeabi_l2d
    wrapper_func __aeabi_ui2d
    wrapper_func __aeabi_ul2d
    wrapper_func __aeabi_d2iz
    wrapper_func __aeabi_d2lz
    wrapper_func __aeabi_d2uiz
    wrapper_func __aeabi_d2ulz
    wrapper_func __aeabi_d2f
    wrapper_func sqrt
    wrapper_func cos
    wrapper_func sin
    wrapper_func tan
    wrapper_func atan2
    wrapper_func exp
    wrapper_func log

    wrapper_func ldexp
    wrapper_func copysign
    wrapper_func trunc
    wrapper_func floor
    wrapper_func ceil
    wrapper_func round
    wrapper_func sincos
    wrapper_func asin
    wrapper_func acos
    wrapper_func atan
    wrapper_func sinh
    wrapper_func cosh
    wrapper_func tanh
    wrapper_func asinh
    wrapper_func acosh
    wrapper_func atanh
    wrapper_func exp2
    wrapper_func log2
    wrapper_func exp10
    wrapper_func log10
    wrapper_func pow
    wrapper_func powint
    wrapper_func hypot
    wrapper_func cbrt
    wrapper_func fmod
    wrapper_func drem
    wrapper_func remainder
    wrapper_func remquo
    wrapper_func expm1
    wrapper_func log1p
    wrapper_func fma

    push {lr}       // keep stack trace sane
    ldr r0, =str
    bl panic

str:
    .asciz "double support is disabled"