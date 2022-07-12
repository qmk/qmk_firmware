/* Copyright 2020 Nick Brassel (tzarc)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

/*
    The size used by the STM32 L0/L1 EEPROM driver.
*/
#ifndef STM32_ONBOARD_EEPROM_SIZE
#    ifdef VIA_ENABLE
#        define STM32_ONBOARD_EEPROM_SIZE 1024
#    else
#        include "eeconfig.h"
#        define STM32_ONBOARD_EEPROM_SIZE (((EECONFIG_SIZE + 3) / 4) * 4) // based off eeconfig's current usage, aligned to 4-byte sizes, to deal with LTO and EEPROM page sizing
#    endif
#endif

#if STM32_ONBOARD_EEPROM_SIZE > 128
#    pragma message("Please note: resetting EEPROM using an STM32L0/L1 device takes up to 1 second for every 1kB of internal EEPROM used.")
#endif
