/* Copyright 2025 Colin Lam, Ploopy Corporation (contact@ploopy.co)
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

#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include "compiler_support.h"

// A deadzone for high-resolution scrolling. 12 was found to be a good value
// experimentally, balancing good responsiveness with low backlash.
#ifndef POINTING_DEVICE_AS5600_DEADZONE
#    define POINTING_DEVICE_AS5600_DEADZONE 12
#endif

// The speed divisor decreases the speed. 1 is base speed; 2 is divided by 2,
// 3 is divided by 3, and so forth. For best results, make sure that
// POINTING_DEVICE_AS5600_SPEED_DIV is an integer divisor of
// POINTING_DEVICE_AS5600_DEADZONE (i.e. 3 is an integer divisor of 12, but
// 5 is not).
#ifndef POINTING_DEVICE_AS5600_SPEED_DIV
#    define POINTING_DEVICE_AS5600_SPEED_DIV 2
#endif

STATIC_ASSERT(POINTING_DEVICE_AS5600_DEADZONE % POINTING_DEVICE_AS5600_SPEED_DIV == 0, "POINTING_DEVICE_AS5600_SPEED_DIV must be an integer divisor of POINTING_DEVICE_AS5600_DEADZONE");

// Scroll sensitivity, but only for MacOS.
// Lower numbers make the scroll more sensitive.
#ifndef POINTING_DEVICE_AS5600_TICK_COUNT
#    define POINTING_DEVICE_AS5600_TICK_COUNT 128
#endif

#ifndef POINTING_DEVICE_AS5600_I2C_TIMEOUT
#    define POINTING_DEVICE_AS5600_I2C_TIMEOUT 10
#endif

#define REG_ZMCO        0x00
#define REG_ZPOS        0x01
#define REG_MPOS        0x03
#define REG_MANG        0x05
#define REG_CONF        0x07
#define REG_RAWANGLE    0x0c
#define REG_ANGLE       0x0e
#define REG_STATUS      0x0b
#define REG_AGC         0x1a
#define REG_MAGNITUDE   0x1b
#define REG_BURN        0xff

void as5600_init(void);
uint16_t as5600_get_rawangle(void);
bool as5600_is_magnet_too_high(void);
bool as5600_is_magnet_too_low(void);
bool as5600_is_magnet_present(void);
