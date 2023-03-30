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

wrapper_func __aeabi_fadd
wrapper_func __aeabi_fdiv
wrapper_func __aeabi_fmul
wrapper_func __aeabi_frsub
wrapper_func __aeabi_fsub
wrapper_func __aeabi_cfcmpeq
wrapper_func __aeabi_cfrcmple
wrapper_func __aeabi_cfcmple
wrapper_func __aeabi_fcmpeq
wrapper_func __aeabi_fcmplt
wrapper_func __aeabi_fcmple
wrapper_func __aeabi_fcmpge
wrapper_func __aeabi_fcmpgt
wrapper_func __aeabi_fcmpun
wrapper_func __aeabi_i2f
wrapper_func __aeabi_l2f
wrapper_func __aeabi_ui2f
wrapper_func __aeabi_ul2f
wrapper_func __aeabi_i2f
wrapper_func __aeabi_f2iz
wrapper_func __aeabi_f2lz
wrapper_func __aeabi_f2uiz
wrapper_func __aeabi_f2ulz
wrapper_func __aeabi_f2d
wrapper_func sqrtf
wrapper_func cosf
wrapper_func sinf
wrapper_func tanf
wrapper_func atan2f
wrapper_func expf
wrapper_func logf
wrapper_func ldexpf
wrapper_func copysignf
wrapper_func truncf
wrapper_func floorf
wrapper_func ceilf
wrapper_func roundf
wrapper_func sincosf
wrapper_func asinf
wrapper_func acosf
wrapper_func atanf
wrapper_func sinhf
wrapper_func coshf
wrapper_func tanhf
wrapper_func asinhf
wrapper_func acoshf
wrapper_func atanhf
wrapper_func exp2f
wrapper_func log2f
wrapper_func exp10f
wrapper_func log10f
wrapper_func powf
wrapper_func powintf
wrapper_func hypotf
wrapper_func cbrtf
wrapper_func fmodf
wrapper_func dremf
wrapper_func remainderf
wrapper_func remquof
wrapper_func expm1f
wrapper_func log1pf
wrapper_func fmaf
    push {lr}       // keep stack trace sane
    ldr r0, =str
    bl panic

str:
    .asciz "float support is disabled"