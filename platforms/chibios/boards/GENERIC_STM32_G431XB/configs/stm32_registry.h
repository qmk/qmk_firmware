// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// TODO: Remove when STM32_FLASH_SECTORS_PER_BANK fixed upstream
#ifndef STM32_FLASH_SECTORS_PER_BANK
#    define STM32_FLASH_SECTORS_PER_BANK 64
#endif

#include_next <stm32_registry.h>

// TODO: Remove when STM32_FLASH_NUMBER_OF_BANKS fixed upstream
#undef STM32_FLASH_NUMBER_OF_BANKS
#define STM32_FLASH_NUMBER_OF_BANKS 1
