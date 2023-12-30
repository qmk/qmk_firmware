/* Copyright 2018-2021 Harrison Chan (@Xelus)
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

#include_next <board.h>

#undef STM32L432xx

// Pretend that we're an L443xx as the ChibiOS definitions for L4x2/L4x3 mistakenly don't enable GPIOH, I2C2, or SPI2.
// Until ChibiOS upstream is fixed, this should be kept at L443, as nothing in QMK currently utilises the crypto peripheral on the L443.
#define STM32L443xx
