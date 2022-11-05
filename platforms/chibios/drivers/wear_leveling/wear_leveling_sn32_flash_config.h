// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Work out the page size to use
#ifndef WEAR_LEVELING_SN32_PAGE_SIZE
#    if defined(QMK_MCU_SERIES_SN32F240B)
#        define WEAR_LEVELING_SN32_PAGE_SIZE 64
#    elif defined(QMK_MCU_SERIES_SN32F260)
#        define WEAR_LEVELING_SN32_PAGE_SIZE 64
#    endif
#endif

// Number of pages we have
#ifndef WEAR_LEVELING_SN32_EMULATION_TOTAL_PAGE
#    if defined(QMK_MCU_SERIES_SN32F240B)
#        define WEAR_LEVELING_SN32_EMULATION_TOTAL_PAGE 1024
#    elif defined(QMK_MCU_SERIES_SN32F260)
#        define WEAR_LEVELING_SN32_EMULATION_TOTAL_PAGE 480
#    endif
#endif

// The number of pages to use
#ifndef WEAR_LEVELING_SN32_EMULATION_PAGE_COUNT
#    if defined(QMK_MCU_SERIES_SN32F240B)
#        define WEAR_LEVELING_SN32_EMULATION_PAGE_COUNT 23
#    elif defined(QMK_MCU_SERIES_SN32F260)
#        define WEAR_LEVELING_SN32_EMULATION_PAGE_COUNT 23
#    endif
#endif

// The origin of the emulated eeprom
#ifndef WEAR_LEVELING_SN32_EMULATION_BASE_PAGE_ADDRESS
#    define WEAR_LEVELING_SN32_EMULATION_BASE_PAGE_ADDRESS ((uint32_t)(WEAR_LEVELING_SN32_PAGE_SIZE * WEAR_LEVELING_SN32_EMULATION_TOTAL_PAGE - ((WEAR_LEVELING_SN32_EMULATION_PAGE_COUNT + 1) * WEAR_LEVELING_SN32_PAGE_SIZE)))
#endif

// 4-byte writes
#ifndef BACKING_STORE_WRITE_SIZE
#    define BACKING_STORE_WRITE_SIZE 4
#endif

// The amount of space to use for the entire set of emulation
#ifndef WEAR_LEVELING_BACKING_SIZE
#    define WEAR_LEVELING_BACKING_SIZE ((WEAR_LEVELING_SN32_EMULATION_PAGE_COUNT)*WEAR_LEVELING_SN32_PAGE_SIZE)
#endif

// The logical amount of eeprom available
#ifndef WEAR_LEVELING_LOGICAL_SIZE
#    define WEAR_LEVELING_LOGICAL_SIZE ((WEAR_LEVELING_BACKING_SIZE) / 2)
#endif
