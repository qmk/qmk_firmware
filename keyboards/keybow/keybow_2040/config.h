/* Copyright 2024 Sandy Macdonald (https://github.com/sandyjmacdonald)
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

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

// IS31FL3731 driver
#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define I2C_DRIVER I2CD0
#define I2C1_SCL_PIN GP5
#define I2C1_SDA_PIN GP4
#define I2C1_CLOCK_SPEED 100000

// RGB matrix
#define RGB_MATRIX_DEFAULT_ON true
#define RGB_MATRIX_LED_COUNT 16
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define RGB_MATRIX_DEFAULT_HUE 130
#define RGB_MATRIX_DEFAULT_SAT 255

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_SLEEP
#endif