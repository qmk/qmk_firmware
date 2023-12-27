/*
Copyright 2023 Mechlovin'

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

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 00 AD <-> GND
// 01 AD <-> SCL
// 10 AD <-> SDA
// 11 AD <-> VCC
// ADDR represents A1:A0 of the 7-bit address.
// The result is: 0b11101(ADDR)
#define LED_DRIVER_ADDR_1 IS31FL3731_I2C_ADDRESS_SDA
#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN B10
#define I2C1_SDA_PIN B11
#define LED_DRIVER_COUNT 1
#define LED_MATRIX_LED_COUNT 114
#define LED_MATRIX_KEYPRESSES // reacts to keypresses
#define LED_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define LED_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects

#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

#define WEAR_LEVELING_BACKING_SIZE 4096
#define WEAR_LEVELING_LOGICAL_SIZE 2048
