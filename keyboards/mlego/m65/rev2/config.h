/*
Copyright 2021-2022 Alin M Elena <alinm.elena@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define RGBLIGHT_LAYERS

#define EEPROM_PAGE_SIZE
#define FEE_PAGE_SIZE 0x800
#define FEE_PAGE_COUNT 4

#define FEE_MCU_FLASH_SIZE_IGNORE_CHECK
#define FEE_MCU_FLASH_SIZE                                \
    ({                                                    \
        uint16_t flash_size = *(uint16_t*)FLASHSIZE_BASE; \
        (flash_size <= 512) ? flash_size : 512;           \
    })
