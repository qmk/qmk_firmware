// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifndef __ASSEMBLER__
#    include <hal.h>
#endif

// 2-byte writes
#ifndef BACKING_STORE_WRITE_SIZE
// These need to match EFL's XXXXXX_FLASH_LINE_SIZE, see associated code in `lib/chibios/os/hal/ports/**/hal_efl_lld.c`,
// or associated `stm32_registry.h` for the MCU in question (or equivalent for the family).
#    if defined(GD32VF103)
#        define BACKING_STORE_WRITE_SIZE 2 // from hal_efl_lld.c
#    elif defined(NUC123SD4AN0)            //  defined(MCU_?????)
#        ifndef NUC123_EFL_IMPLEMENTATION_TESTING
#            error "This configuration currently results in a broken build."
#        endif                             // NUC123_EFL_IMPLEMENTATION_TESTING
#        define BACKING_STORE_WRITE_SIZE 4 // from hal_efl_lld.c
#    elif defined(MCU_STM32)               //  defined(MCU_?????)
#        if defined(STM32_FLASH_LINE_SIZE)
#            define BACKING_STORE_WRITE_SIZE (STM32_FLASH_LINE_SIZE)
#        else // defined(STM32_FLASH_LINE_SIZE)
#            if defined(STM32F0XX)
#                error "ChibiOS hasn't defined a specific STM32_FLASH_LINE_SIZE, but should've." // normally defined in stm32_registry.h, should be set by STM32_FLASH_LINE_SIZE
#            elif defined(STM32F1XX)
#                define BACKING_STORE_WRITE_SIZE 2 // from hal_efl_lld.c
#            elif defined(STM32F3XX)
#                define BACKING_STORE_WRITE_SIZE 2 // from hal_efl_lld.c
#            elif defined(STM32F4XX)
#                define BACKING_STORE_WRITE_SIZE (1 << STM32_FLASH_PSIZE) // from hal_efl_lld.c
#            elif defined(STM32L4XX)
#                define BACKING_STORE_WRITE_SIZE 8 // from hal_efl_lld.c
#            elif defined(STM32G0XX)
#                define BACKING_STORE_WRITE_SIZE 8 // from hal_efl_lld.c
#            elif defined(STM32G4XX)
#                error "ChibiOS hasn't defined a specific STM32_FLASH_LINE_SIZE, but should've." // normally defined in stm32_registry.h, should be set by STM32_FLASH_LINE_SIZE
#            endif // defined(STM32??XX)
#        endif     // defined(STM32_FLASH_LINE_SIZE)
#    endif         // defined(MCU_?????)
#endif

// 16kB space allocated
#ifndef WEAR_LEVELING_BACKING_SIZE
#    define WEAR_LEVELING_BACKING_SIZE 16384
#endif // WEAR_LEVELING_BACKING_SIZE

// 4kB logical EEPROM
#ifndef WEAR_LEVELING_LOGICAL_SIZE
#    define WEAR_LEVELING_LOGICAL_SIZE 4096
#endif // WEAR_LEVELING_LOGICAL_SIZE
