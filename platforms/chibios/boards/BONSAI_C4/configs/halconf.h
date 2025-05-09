/* Copyright 2022 David Hoelscher, customMK
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

#ifndef HAL_USE_SPI
#    define HAL_USE_SPI TRUE
#endif

#ifndef HAL_USE_I2C
#    define HAL_USE_I2C TRUE
#endif

#ifdef SPLIT_KEYBOARD
#    ifndef HAL_USE_SERIAL
#        define HAL_USE_SERIAL TRUE
#    endif
#    ifndef SERIAL_BUFFERS_SIZE
#        define SERIAL_BUFFERS_SIZE 256
#    endif
#endif

#ifdef WS2812_PWM
#    ifndef HAL_USE_PWM
#        define HAL_USE_PWM TRUE
#    endif
#endif

#ifndef SPI_SELECT_MODE
#    define SPI_SELECT_MODE SPI_SELECT_MODE_PAD
#endif

#ifndef SPI_USE_WAIT
#    define SPI_USE_WAIT TRUE
#endif

#include_next <halconf.h>