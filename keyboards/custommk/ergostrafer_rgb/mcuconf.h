/* Copyright 2024 customMK
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

// Used for audio
#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE

// Used for FRAM
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

// Used for RGB matrix
#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE