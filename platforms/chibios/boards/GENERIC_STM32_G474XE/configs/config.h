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

#ifndef STM32_BOOTLOADER_DUAL_BANK
#    define STM32_BOOTLOADER_DUAL_BANK FALSE
#endif

// To Enter bootloader from `RESET` keycode, you'll need to dedicate a GPIO to
// charge an RC network on the BOOT0 pin.
// See the QMK Discord's #hardware channel pins for an example circuit.
// Insert these two lines into your keyboard's `config.h` file.
// In the case below, PB7 is selected to charge.
#if 0
#define STM32_BOOTLOADER_DUAL_BANK TRUE
#define STM32_BOOTLOADER_DUAL_BANK_GPIO B7
#endif