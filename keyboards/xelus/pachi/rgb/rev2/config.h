/* Copyright 2023 Harrison Chan (Xelus)
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

// I2C setup
#define I2C1_SCL_PIN        B6
#define I2C1_SDA_PIN        B7
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4
#define I2C1_TIMINGR_PRESC  0U
#define I2C1_TIMINGR_SCLDEL 7U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH   45U
#define I2C1_TIMINGR_SCLL   149U

// I2C EEPROM
#define EEPROM_I2C_24LC64

// RGB Matrix defines
#define IS31FL3741_I2C_ADDRESS_1 IS31FL3741_I2C_ADDRESS_GND
#define IS31FL3741_LED_COUNT RGB_MATRIX_LED_COUNT // is31fl3741.h does not set this for custom driver

// VIA KB level
#define VIA_FIRMWARE_VERSION 1
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 17
