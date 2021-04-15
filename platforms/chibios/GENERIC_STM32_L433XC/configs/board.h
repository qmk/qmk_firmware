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

#include_next "board.h"

#undef STM32L432xx

// Use L443xx define instead of L433xx since ChibiOS defines
// L433xx together with L432x, which does not activate the 
// GPIO H ports and does not enable I2C2 and SPI2
// Until the bug is fixed in ChibiOS, this should not change
#define STM32L443xx
