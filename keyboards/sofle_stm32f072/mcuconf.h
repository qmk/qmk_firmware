/* Copyright 2020 Nick Brassel (tzarc)
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

#include_next <mcuconf.h>

// #undef STM32_HSE_ENABLED
// #define STM32_HSE_ENABLED FALSE

#undef STM32_I2C_USE_I2C2
#define STM32_I2C_USE_I2C2 TRUE

// TODO: check the real pin, which is connected as serial port between left keyboard and right keyboard.
//
#define SOFT_SERIAL_PIN D??

#define SELECT_SOFT_SERIAL_SPEED 1
/*
 *
 * 0: about 189kbps (Experimental only)
 * 1: about 137kbps (default)
 * 2: about 75kbps
 * 3: about 39kbps
 * 4: about 26kbps
 * 5: about 20kbps
 */
