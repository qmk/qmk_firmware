/* Copyright 2020 Nick Brassel (tzarc)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#define BOARD_OTG_NOVBUSSENS 1

#ifndef STM32_LSECLK
#    define STM32_LSECLK 32768U
#endif // STM32_LSECLK

#ifndef STM32_HSECLK
#    define STM32_HSECLK 25000000U
#endif // STM32_HSECLK

#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#endif

#ifdef WEAR_LEVELING_EMBEDDED_FLASH
#    ifndef WEAR_LEVELING_EFL_FIRST_SECTOR
#        ifdef BOOTLOADER_TINYUF2
#            define WEAR_LEVELING_EFL_FIRST_SECTOR 3
#        else
#            define WEAR_LEVELING_EFL_FIRST_SECTOR 1
#        endif
#    endif
#endif
