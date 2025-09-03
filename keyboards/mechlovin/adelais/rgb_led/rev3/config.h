/*
Copyright 2021 Mechlovin' Studio

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

#define WS2812_SPI_DRIVER SPID1 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5

#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

#define IS31FL3741_I2C_ADDRESS_1 IS31FL3741_I2C_ADDRESS_SDA
