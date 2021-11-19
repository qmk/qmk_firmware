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

#if !defined(FEE_PAGE_SIZE) || !defined(FEE_PAGE_COUNT)
#    if defined(STM32F103xB) || defined(STM32F042x6) || defined(GD32VF103C8) || defined(GD32VF103CB)
#        ifndef FEE_PAGE_SIZE
#            define FEE_PAGE_SIZE 0x400  // Page size = 1KByte
#        endif
#        ifndef FEE_PAGE_COUNT
#            define FEE_PAGE_COUNT 2  // How many pages are used
#        endif
#    elif defined(STM32F103xE) || defined(STM32F303xC) || defined(STM32F072xB) || defined(STM32F070xB)
#        ifndef FEE_PAGE_SIZE
#            define FEE_PAGE_SIZE 0x800  // Page size = 2KByte
#        endif
#        ifndef FEE_PAGE_COUNT
#            define FEE_PAGE_COUNT 4  // How many pages are used
#        endif
#    elif defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F405xG) || defined(STM32F411xE)
#        ifndef FEE_PAGE_SIZE
#            define FEE_PAGE_SIZE 0x4000  // Page size = 16KByte
#        endif
#        ifndef FEE_PAGE_COUNT
#            define FEE_PAGE_COUNT 1  // How many pages are used
#        endif
#    endif
#endif

#if !defined(FEE_MCU_FLASH_SIZE)
#    if defined(STM32F042x6)
#        define FEE_MCU_FLASH_SIZE 32  // Size in Kb
#    elif defined(GD32VF103C8)
#        define FEE_MCU_FLASH_SIZE 64  // Size in Kb
#    elif defined(STM32F103xB) || defined(STM32F072xB) || defined(STM32F070xB) || defined(GD32VF103CB)
#        define FEE_MCU_FLASH_SIZE 128  // Size in Kb
#    elif defined(STM32F303xC) || defined(STM32F401xC)
#        define FEE_MCU_FLASH_SIZE 256  // Size in Kb
#    elif defined(STM32F103xE) || defined(STM32F401xE) || defined(STM32F411xE)
#        define FEE_MCU_FLASH_SIZE 512  // Size in Kb
#    elif defined(STM32F405xG)
#        define FEE_MCU_FLASH_SIZE 1024  // Size in Kb
#    endif
#endif

/* Start of the emulated eeprom */
#if !defined(FEE_PAGE_BASE_ADDRESS)
#    if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F405xG) || defined(STM32F411xE)
#        ifndef FEE_PAGE_BASE_ADDRESS
#            define FEE_PAGE_BASE_ADDRESS 0x08004000  // bodge to force 2nd 16k page
#        endif
#    else
#        ifndef FEE_FLASH_BASE
#            define FEE_FLASH_BASE 0x8000000
#        endif
/* Default to end of flash */
#        define FEE_PAGE_BASE_ADDRESS ((uintptr_t)(FEE_FLASH_BASE) + FEE_MCU_FLASH_SIZE * 1024 - (FEE_PAGE_COUNT * FEE_PAGE_SIZE))
#    endif
#endif
