/*
Copyright 2021 QMK

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

#include_next <board.h>

#ifdef STM32_LSECLK
#undef STM32_LSECLK
#endif // STM32_LSECLK
#define STM32_LSECLK 32768

#ifdef STM32_HSECLK
#undef STM32_HSECLK
#endif // STM32_HSECLK
#define STM32_HSECLK 8000000

#undef VAL_GPIOACRL
#define VAL_GPIOACRL 0x88888888

#undef VAL_GPIOAODR
#define VAL_GPIOAODR 0xFFFFFFFF

#undef VAL_GPIOCCRH
#define VAL_GPIOCCRH 0x88888888
