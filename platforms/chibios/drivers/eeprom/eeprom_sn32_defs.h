/* Copyright 2021 SonixQMK
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

#if !defined(FEE_PAGE_SIZE) || !defined(FEE_TOTAL_PAGES) || !defined(FEE_DENSITY_PAGES)
#    if defined(SN32F240B)
#        ifndef FEE_PAGE_SIZE
#            define FEE_PAGE_SIZE (uint16_t)0x0040 // Page size = 64bytes
#        endif
#        ifndef FEE_TOTAL_PAGES
#            define FEE_TOTAL_PAGES 1024 // How many pages are available
#        endif
#        ifndef FEE_DENSITY_PAGES
#            define FEE_DENSITY_PAGES 23 // How many pages are used as EEPROM
#        endif
#    elif defined(SN32F260)
#        ifndef FEE_PAGE_SIZE
#            define FEE_PAGE_SIZE (uint16_t)0x0040 // Page size = 64bytes
#        endif
#        ifndef FEE_TOTAL_PAGES
#            define FEE_TOTAL_PAGES 480 // How many pages are available
#        endif
#        ifndef FEE_DENSITY_PAGES
#            define FEE_DENSITY_PAGES 23 // How many pages are used as EEPROM
#        endif
#    endif
#endif

#if !defined(FEE_MCU_FLASH_SIZE)
#    if defined(SN32F240B)
#        define FEE_MCU_FLASH_SIZE 64 // Size in Kb
#    elif defined(SN32F260)
#        define FEE_MCU_FLASH_SIZE 30 // Size in Kb
#    endif
#endif

/* Start of the emulated eeprom */
#if !defined(FEE_PAGE_BASE_ADDRESS)
#    if defined(SN32F240B) || defined(SN32F260)
#        ifndef FEE_PAGE_BASE_ADDRESS
#            define FEE_PAGE_BASE_ADDRESS ((uint32_t)(FEE_PAGE_SIZE * FEE_TOTAL_PAGES - ((FEE_DENSITY_PAGES + 1) * FEE_PAGE_SIZE))) // Guard the last page
#        endif
#    endif
#endif
