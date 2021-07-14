/* Copyright 2021 by Don Kjer
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

//#define DEBUG_EEPROM

#define FEE_FLASH_BASE FlashBuf

#ifdef FLASH_STM32_MOCK_LARGE
#    define FEE_MCU_FLASH_SIZE 64
#    define FEE_PAGE_SIZE 2048
#    define FEE_DENSITY_PAGES 16
#else
#    define FEE_MCU_FLASH_SIZE 1
#    define FEE_PAGE_SIZE 512
#    define FEE_DENSITY_PAGES 1
#endif

#define FLASH_SIZE (FEE_MCU_FLASH_SIZE * 1024)
extern uint8_t FlashBuf[FLASH_SIZE];
