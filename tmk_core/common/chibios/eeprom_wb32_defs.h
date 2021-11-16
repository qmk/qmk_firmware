/*
    Copyright (C) 2021 Westberry Technology (ChangZhou) Corp., Ltd

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once

#include <hal.h>

#if !defined(FEE_PAGE_SIZE) || !defined(FEE_PAGE_COUNT)
#    if defined(WB32F3G71x9) || defined(WB32F3G71xB) || defined(WB32F3G71xC)
#        ifndef FEE_PAGE_SIZE
#            define FEE_PAGE_SIZE (uint16_t)0x100  // Page size = 256Byte
#        endif
#        ifndef FEE_PAGE_COUNT
#            define FEE_PAGE_COUNT 4  // How many pages are used
#        endif
#    endif
#endif

#if !defined(FEE_MCU_FLASH_SIZE)
#    if defined(WB32F3G71x9)
#        define FEE_MCU_FLASH_SIZE 96  // Size in Kb
#    elif defined(WB32F3G71xB)
#        define FEE_MCU_FLASH_SIZE 128  // Size in Kb
#    elif defined(WB32F3G71xC)
#        define FEE_MCU_FLASH_SIZE 256  // Size in Kb
#    endif
#endif

/* Start of the emulated eeprom */
#if !defined(FEE_PAGE_BASE_ADDRESS)
#    if defined(WB32F3G71x9) || defined(WB32F3G71xB) || defined(WB32F3G71xC)
#        ifndef FEE_PAGE_BASE_ADDRESS
#            define FEE_PAGE_BASE_ADDRESS ((uint32_t)(0x8000000 + FEE_MCU_FLASH_SIZE * 1024 - FEE_PAGE_COUNT * FEE_PAGE_SIZE))  // bodge to force 2nd 16k page
#        endif
#        ifndef FEE_DENSITY_BYTES
#            define FEE_DENSITY_BYTES (FEE_PAGE_SIZE * FEE_PAGE_COUNT - 1)
#        endif
#        ifndef WB32_FLASH_BASE
#            define WB32_FLASH_BASE 0x8000000
#        endif
#    endif
#endif
