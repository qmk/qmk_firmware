/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

.syntax unified
.cpu cortex-m0plus
.thumb

#include "pico/asm_helper.S"
#include "pico/bootrom.h"

__pre_init __aeabi_mem_init, 00001

.macro mem_section name
#if PICO_MEM_IN_RAM
.section RAM_SECTION_NAME(\name), "ax"
#else
.section SECTION_NAME(\name), "ax"
#endif
.endm

.equ MEMSET, 0
.equ MEMCPY, 4
.equ MEMSET4, 8
.equ MEMCPY4, 12
.equ MEM_FUNC_COUNT, 4

# NOTE: All code sections are placed in RAM (at the expense of some veneer cost for calls from flash) because
#       otherwise code using basic c division operators will require XIP flash access.

.section .data.aeabi_mem_funcs
.global aeabi_mem_funcs, aeabi_mem_funcs_end

.align 2
aeabi_mem_funcs:
    .word ROM_FUNC_MEMSET
    .word ROM_FUNC_MEMCPY
    .word ROM_FUNC_MEMSET4
    .word ROM_FUNC_MEMCPY44
aeabi_mem_funcs_end:

.section .text
regular_func __aeabi_mem_init
    ldr r0, =aeabi_mem_funcs
    movs r1, #MEM_FUNC_COUNT
    ldr r3, =rom_funcs_lookup
    bx r3

# lump them both together because likely both to be used, in which case doing so saves 1 word
# and it only costs 1 word if not

// Note from Run-time ABI for the ARM architecture 4.3.4:
// If there is an attached device with efficient memory copying or clearing operations
// (such as a DMA engine), its device supplement specifies whether it may be used in
// implementations of these functions and what effect such use has on the device’s state.

mem_section aeabi_memset_memcpy

wrapper_func __aeabi_memset
    // 2nd/3rd args are reversed
    eors r2, r1
    eors r1, r2
    eors r2, r1
    ldr r3, =aeabi_mem_funcs
    ldr r3, [r3, #MEMSET]
    bx r3

wrapper_func __aeabi_memset4
wrapper_func __aeabi_memset8
    // 2nd/3rd args are reversed
    eors r2, r1
    eors r1, r2
    eors r2, r1
    ldr r3, =aeabi_mem_funcs
    ldr r3, [r3, #MEMSET4]
    bx r3

wrapper_func __aeabi_memcpy4
wrapper_func __aeabi_memcpy8
    ldr r3, =aeabi_mem_funcs
    ldr r3, [r3, #MEMCPY4]
    bx r3

mem_section memset

wrapper_func memset
    ldr r3, =aeabi_mem_funcs
    ldr r3, [r3, #MEMSET]
    bx r3

mem_section memcpy
wrapper_func __aeabi_memcpy
wrapper_func memcpy
    ldr r3, =aeabi_mem_funcs
    ldr r3, [r3, #MEMCPY]
    bx r3

