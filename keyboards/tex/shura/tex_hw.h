// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#if !defined(_FROM_ASM_)
#    include <stdint.h>
#endif

// The TEX bootloader at 0x0000 starts its USB updater (04D9:1532) when this word in
// the reserved top of SRAM holds IAP_MAGIC_VALUE after a reset.
#define IAP_MAGIC_ADDR 0x20003FFCU
#define IAP_MAGIC_VALUE 0x55AAFAF5U
#define TEX_WDT_RELOAD() (*(volatile uint32_t *)0x40068000U = 0x5FA00001U)

#define TEX_ENTER_IAP()                                         \
    do {                                                        \
        *(volatile uint32_t *)IAP_MAGIC_ADDR = IAP_MAGIC_VALUE; \
        __asm volatile("dsb" ::: "memory");                     \
        *(volatile uint32_t *)0xE000ED0CU = 0x05FA0004U;        \
        __asm volatile("dsb" ::: "memory");                     \
        for (;;) {                                              \
        }                                                       \
    } while (0)
