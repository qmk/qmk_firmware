/* Copyright 2020 QMK
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

#include_next <halconf.h>

#undef HAL_USE_I2C
#define HAL_USE_I2C TRUE

#undef HAL_USE_UART
#define HAL_USE_UART TRUE
#undef UART_USE_WAIT
#define UART_USE_WAIT TRUE

#undef STM32_UART_USE_USART1
#define STM32_UART_USE_USART1 TRUE

#ifdef JOYSTICK_ENABLE
#    undef HAL_USE_ADC
#    define HAL_USE_ADC TRUE
#    undef STM32_ADC_USE_ADC1
#    define STM32_ADC_USE_ADC1 TRUE
#endif

#undef HAL_USE_SPI
#define HAL_USE_SPI TRUE
#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD

#undef PAL_USE_CALLBACKS
#define PAL_USE_CALLBACKS TRUE
