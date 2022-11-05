// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Work out the page size to use
#ifndef WEAR_LEVELING_LEGACY_EMULATION_PAGE_SIZE
#    if defined(QMK_MCU_STM32F042)
#        define WEAR_LEVELING_LEGACY_EMULATION_PAGE_SIZE 1024
#    elif defined(QMK_MCU_STM32F070) || defined(QMK_MCU_STM32F072)
#        define WEAR_LEVELING_LEGACY_EMULATION_PAGE_SIZE 2048
#    elif defined(QMK_MCU_STM32F401) || defined(QMK_MCU_STM32F411)
#        define WEAR_LEVELING_LEGACY_EMULATION_PAGE_SIZE 16384
#    endif
#endif

// Work out how much flash space we have
#ifndef WEAR_LEVELING_LEGACY_EMULATION_FLASH_SIZE
#    define WEAR_LEVELING_LEGACY_EMULATION_FLASH_SIZE ((*(uint32_t *)FLASHSIZE_BASE) & 0xFFFFU) // in kB
#endif

// The base location of program memory
#ifndef WEAR_LEVELING_LEGACY_EMULATION_FLASH_BASE
#    define WEAR_LEVELING_LEGACY_EMULATION_FLASH_BASE 0x08000000
#endif

// The number of pages to use
#ifndef WEAR_LEVELING_LEGACY_EMULATION_PAGE_COUNT
#    if defined(QMK_MCU_STM32F042)
#        define WEAR_LEVELING_LEGACY_EMULATION_PAGE_COUNT 2
#    elif defined(QMK_MCU_STM32F070) || defined(QMK_MCU_STM32F072)
#        define WEAR_LEVELING_LEGACY_EMULATION_PAGE_COUNT 1
#    elif defined(QMK_MCU_STM32F401) || defined(QMK_MCU_STM32F411)
#        define WEAR_LEVELING_LEGACY_EMULATION_PAGE_COUNT 1
#    endif
#endif

// The origin of the emulated eeprom
#ifndef WEAR_LEVELING_LEGACY_EMULATION_BASE_PAGE_ADDRESS
#    if defined(QMK_MCU_STM32F042) || defined(QMK_MCU_STM32F070) || defined(QMK_MCU_STM32F072)
#        define WEAR_LEVELING_LEGACY_EMULATION_BASE_PAGE_ADDRESS ((uintptr_t)(WEAR_LEVELING_LEGACY_EMULATION_FLASH_BASE) + WEAR_LEVELING_LEGACY_EMULATION_FLASH_SIZE * 1024 - (WEAR_LEVELING_LEGACY_EMULATION_PAGE_COUNT * WEAR_LEVELING_LEGACY_EMULATION_PAGE_SIZE))
#    elif defined(QMK_MCU_STM32F401) || defined(QMK_MCU_STM32F411)
#        if defined(BOOTLOADER_STM32)
#            define WEAR_LEVELING_LEGACY_EMULATION_BASE_PAGE_ADDRESS (WEAR_LEVELING_LEGACY_EMULATION_FLASH_BASE + (1 * (WEAR_LEVELING_LEGACY_EMULATION_PAGE_SIZE))) // +16k
#        elif defined(BOOTLOADER_TINYUF2)
#            define WEAR_LEVELING_LEGACY_EMULATION_BASE_PAGE_ADDRESS (WEAR_LEVELING_LEGACY_EMULATION_FLASH_BASE + (3 * (WEAR_LEVELING_LEGACY_EMULATION_PAGE_SIZE))) // +48k
#        endif
#    endif
#endif

// 2-byte writes
#ifndef BACKING_STORE_WRITE_SIZE
#    define BACKING_STORE_WRITE_SIZE 2
#endif

// The amount of space to use for the entire set of emulation
#ifndef WEAR_LEVELING_BACKING_SIZE
#    if defined(QMK_MCU_STM32F042) || defined(QMK_MCU_STM32F070) || defined(QMK_MCU_STM32F072)
#        define WEAR_LEVELING_BACKING_SIZE 2048
#    elif defined(QMK_MCU_STM32F401) || defined(QMK_MCU_STM32F411)
#        define WEAR_LEVELING_BACKING_SIZE 16384
#    endif
#endif

// The logical amount of eeprom available
#ifndef WEAR_LEVELING_LOGICAL_SIZE
#    define WEAR_LEVELING_LOGICAL_SIZE 1024
#endif
