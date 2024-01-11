/* Copyright 2023 Cipulot
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
#include_next "stm32_registry.h"

/* This config is wrong in ChibiOS upstream. */
#undef STM32_FLASH_NUMBER_OF_BANKS
#define STM32_FLASH_NUMBER_OF_BANKS 1

/* This config is wrong in ChibiOS upstream. */
#undef STM32_FLASH_SECTORS_PER_BANK
#define STM32_FLASH_SECTORS_PER_BANK 64
