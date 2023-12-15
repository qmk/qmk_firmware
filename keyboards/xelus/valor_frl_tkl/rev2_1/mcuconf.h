/* Copyright 2022 QMK
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

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLP_VALUE
#undef STM32_PLLQ_VALUE
#undef STM32_PPRE1
#undef STM32_PPRE2

// 84MHz core
#define STM32_PLLM_VALUE    8
#define STM32_PLLN_VALUE    168
#define STM32_PLLP_VALUE    4
#define STM32_PLLQ_VALUE    7
#define STM32_PPRE1         STM32_PPRE1_DIV2
#define STM32_PPRE2         STM32_PPRE1_DIV1
