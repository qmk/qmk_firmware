// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <board.h>

// Match the Shura's startup pin state in the generic board's PALConfig,
// before palInit() writes any GPIO registers. Keep every pin in AF0;
// only BOOT (PA9) has its input enabled, and BOOT and SWD have pull-ups.
#undef VAL_GPIOA_INER
#define VAL_GPIOA_INER (1U << 9)
#undef VAL_GPIOA_PUR
#define VAL_GPIOA_PUR ((1U << 9) | (1U << 12) | (1U << 13))
#undef VAL_GPIOA_AFCFGR0
#define VAL_GPIOA_AFCFGR0 0U
#undef VAL_GPIOA_AFCFGR1
#define VAL_GPIOA_AFCFGR1 0U

#undef VAL_GPIOB_INER
#define VAL_GPIOB_INER 0U
#undef VAL_GPIOB_PUR
#define VAL_GPIOB_PUR 0U
#undef VAL_GPIOB_AFCFGR0
#define VAL_GPIOB_AFCFGR0 0U
#undef VAL_GPIOB_AFCFGR1
#define VAL_GPIOB_AFCFGR1 0U

#undef VAL_GPIOC_INER
#define VAL_GPIOC_INER 0U
#undef VAL_GPIOC_PUR
#define VAL_GPIOC_PUR 0U
#undef VAL_GPIOC_AFCFGR0
#define VAL_GPIOC_AFCFGR0 0U
#undef VAL_GPIOC_AFCFGR1
#define VAL_GPIOC_AFCFGR1 0U

#undef VAL_GPIOD_INER
#define VAL_GPIOD_INER 0U
#undef VAL_GPIOD_PUR
#define VAL_GPIOD_PUR 0U
#undef VAL_GPIOD_AFCFGR0
#define VAL_GPIOD_AFCFGR0 0U
#undef VAL_GPIOD_AFCFGR1
#define VAL_GPIOD_AFCFGR1 0U

// Application region above the TEX bootloader: 0x3200 to 0x1FC00.
#define FLASH_SIZE (0x1FC00 - 0x3200)
