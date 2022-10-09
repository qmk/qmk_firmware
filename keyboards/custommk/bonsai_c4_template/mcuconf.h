/* Copyright 2022 customMK
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

// Used for underglow in example code
#undef STM32_PWM_USE_TIM1 //timer 1 channel 3
#define STM32_PWM_USE_TIM1 TRUE

// Used for backlight in examples
#undef STM32_PWM_USE_TIM3 //timer 3 channel 1
#define STM32_PWM_USE_TIM3 TRUE

// Used for FRAM and flash in example code
#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

// Used for Split comms in example code
#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE