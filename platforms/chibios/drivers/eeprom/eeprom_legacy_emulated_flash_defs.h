/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <hal.h>

#define __PRINT_MACRO(x) #x
#define PRINT_MARCO(x) #x"=" __PRINT_MACRO(x)

#if !defined(FEE_PAGE_SIZE) || !defined(FEE_PAGE_COUNT)
#    if defined(STM32F103xB) || defined(STM32F042x6) || defined(GD32VF103C8) || defined(GD32VF103CB)
#        ifndef FEE_PAGE_SIZE
#            define FEE_PAGE_SIZE 0x400 // Page size = 1KByte
#        endif
#        ifndef FEE_PAGE_COUNT
#            define FEE_PAGE_COUNT 2 // How many pages are used
#        endif
#    elif defined(STM32F103xE) || defined(STM32F303xC) || defined(STM32F303xE) || defined(STM32F072xB) || defined(STM32F070xB) || defined(STM32L432xx)
#        ifndef FEE_PAGE_SIZE
#            define FEE_PAGE_SIZE 0x800 // Page size = 2KByte
#        endif
#        ifndef FEE_PAGE_COUNT
#            define FEE_PAGE_COUNT 4 // How many pages are used
#        endif
#    elif defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F405xG) || defined(STM32F411xE)
#        ifndef FEE_PAGE_SIZE
#            define FEE_PAGE_SIZE 0x4000 // Page size = 16KByte
#        endif
#        ifndef FEE_PAGE_COUNT
#            define FEE_PAGE_COUNT 1 // How many pages are used
#        endif
#    endif
#endif

#if !defined(FEE_MCU_FLASH_SIZE)
#    if defined(STM32F042x6)
#        define FEE_MCU_FLASH_SIZE 32 // Size in Kb
#    elif defined(GD32VF103C8)
#        define FEE_MCU_FLASH_SIZE 64 // Size in Kb
#    elif defined(STM32F103xB) || defined(STM32F072xB) || defined(STM32F070xB) || defined(GD32VF103CB) || defined(STM32L432xx)
#        define FEE_MCU_FLASH_SIZE 128 // Size in Kb
#    elif defined(STM32F303xC) || defined(STM32F401xC)
#        define FEE_MCU_FLASH_SIZE 256 // Size in Kb
#    elif defined(STM32F103xE) || defined(STM32F303xE) || defined(STM32F401xE) || defined(STM32F411xE)
#        define FEE_MCU_FLASH_SIZE 512 // Size in Kb
#    elif defined(STM32F405xG)
#        define FEE_MCU_FLASH_SIZE 1024 // Size in Kb
#    endif
#endif

/* Start of the emulated eeprom */
#if !defined(FEE_PAGE_BASE_ADDRESS)
#    if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F405xG) || defined(STM32F411xE)
#        ifndef FEE_PAGE_BASE_ADDRESS
#            define FEE_PAGE_BASE_ADDRESS 0x08004000 // bodge to force 2nd 16k page
#        endif
#    else
#        ifndef FEE_FLASH_BASE
#            define FEE_FLASH_BASE 0x8000000
#        endif
/* Default to end of flash */
#        define FEE_PAGE_BASE_ADDRESS ((uintptr_t)(FEE_FLASH_BASE) + FEE_MCU_FLASH_SIZE * 1024 - (FEE_PAGE_COUNT * FEE_PAGE_SIZE))
#    endif
#endif

/* Addressable range 16KByte: 0 <-> (0x1FFF << 1) */
#define FEE_ADDRESS_MAX_SIZE 0x4000

/* Size of combined compacted eeprom and write log pages */
#define FEE_DENSITY_MAX_SIZE (FEE_PAGE_COUNT * FEE_PAGE_SIZE)

#ifndef FEE_MCU_FLASH_SIZE_IGNORE_CHECK /* *TODO: Get rid of this check */
#    if FEE_DENSITY_MAX_SIZE > (FEE_MCU_FLASH_SIZE * 1024)
#        pragma message STR(FEE_DENSITY_MAX_SIZE) " > " STR(FEE_MCU_FLASH_SIZE * 1024)
#        error emulated eeprom: FEE_DENSITY_MAX_SIZE is greater than available flash size
#    endif
#endif

/* Size of emulated eeprom */
#ifdef FEE_DENSITY_BYTES
#    if (FEE_DENSITY_BYTES > FEE_DENSITY_MAX_SIZE)
#        pragma message STR(FEE_DENSITY_BYTES) " > " STR(FEE_DENSITY_MAX_SIZE)
#        error emulated eeprom: FEE_DENSITY_BYTES exceeds FEE_DENSITY_MAX_SIZE
#    endif
#    if (FEE_DENSITY_BYTES == FEE_DENSITY_MAX_SIZE)
#        pragma message STR(FEE_DENSITY_BYTES) " == " STR(FEE_DENSITY_MAX_SIZE)
#        warning emulated eeprom: FEE_DENSITY_BYTES leaves no room for a write log.  This will greatly increase the flash wear rate!
#    endif
#    if FEE_DENSITY_BYTES > FEE_ADDRESS_MAX_SIZE
#        pragma message STR(FEE_DENSITY_BYTES) " > " STR(FEE_ADDRESS_MAX_SIZE)
#        error emulated eeprom: FEE_DENSITY_BYTES is greater than FEE_ADDRESS_MAX_SIZE allows
#    endif
#    if ((FEE_DENSITY_BYTES) % 2) == 1
#        error emulated eeprom: FEE_DENSITY_BYTES must be even
#    endif
#else
/* Default to half of allocated space used for emulated eeprom, half for write log */
#    define FEE_DENSITY_BYTES (FEE_PAGE_COUNT * FEE_PAGE_SIZE / 2)
#endif

/* Size of write log */
#ifdef FEE_WRITE_LOG_BYTES
#    if ((FEE_DENSITY_BYTES + FEE_WRITE_LOG_BYTES) > FEE_DENSITY_MAX_SIZE)
#        pragma message STR(FEE_DENSITY_BYTES) " + " STR(FEE_WRITE_LOG_BYTES) " > " STR(FEE_DENSITY_MAX_SIZE)
#        error emulated eeprom: FEE_WRITE_LOG_BYTES exceeds remaining FEE_DENSITY_MAX_SIZE
#    endif
#    if ((FEE_WRITE_LOG_BYTES) % 2) == 1
#        error emulated eeprom: FEE_WRITE_LOG_BYTES must be even
#    endif
#else
/* Default to use all remaining space */
#    define FEE_WRITE_LOG_BYTES (FEE_PAGE_COUNT * FEE_PAGE_SIZE - FEE_DENSITY_BYTES)
#endif

/* Start of the emulated eeprom compacted flash area */
#define FEE_COMPACTED_BASE_ADDRESS FEE_PAGE_BASE_ADDRESS
/* End of the emulated eeprom compacted flash area */
#define FEE_COMPACTED_LAST_ADDRESS (FEE_COMPACTED_BASE_ADDRESS + FEE_DENSITY_BYTES)
/* Start of the emulated eeprom write log */
#define FEE_WRITE_LOG_BASE_ADDRESS FEE_COMPACTED_LAST_ADDRESS
/* End of the emulated eeprom write log */
#define FEE_WRITE_LOG_LAST_ADDRESS (FEE_WRITE_LOG_BASE_ADDRESS + FEE_WRITE_LOG_BYTES)

#if defined(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR) && (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR >= FEE_DENSITY_BYTES)
#    error emulated eeprom: DYNAMIC_KEYMAP_EEPROM_MAX_ADDR is greater than the FEE_DENSITY_BYTES available
#endif
