/* Copyright 2021 customMK
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

// If you are using I2C (e.g. for OLED), include this line
#define HAL_USE_I2C TRUE

// If you are using PWM (e.g. for WS2812, backlight, etc.) include this line
#define HAL_USE_PWM TRUE

// If you are using serial comms for split communications, include these lines
#define HAL_USE_SERIAL TRUE
#define SERIAL_BUFFERS_SIZE 256

// If you are using SPI (e.g. for FRAM, flash, etc.) include these lines
#define HAL_USE_SPI TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD
// This enables interrupt-driven mode
#define SPI_USE_WAIT TRUE

#include_next <halconf.h>