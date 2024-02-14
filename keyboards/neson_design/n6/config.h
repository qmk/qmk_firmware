/**
 * config.h
 *
    Copyright 2021 astro

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

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT


#define DRIVER_1_LED_TOTAL 32
#define DRIVER_2_LED_TOTAL 32
#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define IS31FL3731_I2C_ADDRESS_2 IS31FL3731_I2C_ADDRESS_VCC
#define IS31FL3731_LED_COUNT (DRIVER_1_LED_TOTAL+DRIVER_2_LED_TOTAL)
