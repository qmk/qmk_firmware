//===-- call_apsr.S - Helpers for ARM EABI floating point tests -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements helpers for ARM EABI floating point tests for the
// compiler_rt library.
//
//===-

.syntax unified
.cpu cortex-m0plus
.thumb

.align 2

.global call_apsr_f
.type call_apsr_f,%function
.thumb_func
call_apsr_f:
    push {lr}
    blx r2
    mrs r0, apsr
    pop {pc}

.global call_apsr_d
.type call_apsr_d,%function
.thumb_func
call_apsr_d:
    push {r4, lr}
    ldr r4, [sp, #8]
    blx r4
    mrs r0, apsr
    pop {r4, pc}
